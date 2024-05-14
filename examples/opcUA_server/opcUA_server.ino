/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include "PortentaEthernet.h"
#include "Arduino_open62541.h"

/**************************************************************************************
 * GLUE CODE
 **************************************************************************************/

extern "C"
{
  int gethostname(char *str, size_t len) {
    String ip = Ethernet.localIP().toString();
    memset(str, 0, len);
    memcpy(str, ip.c_str(), ip.length());
    return 0;
  }

  UA_StatusCode registerFakeInterrupt(UA_InterruptManager *im, uintptr_t interruptHandle, const UA_KeyValueMap *params,  UA_InterruptCallback callback, void *interruptContext) {
    return UA_STATUSCODE_GOOD;
  }
  void deregisterFakeInterrupt(UA_InterruptManager *im, uintptr_t interruptHandle) {
    return;
  }
  UA_StatusCode startFakeInterruptManager(UA_EventSource *es) {
    return UA_STATUSCODE_GOOD;
  }
  void stopFakeInterruptManager(UA_EventSource *es) {
    return;
  }
  UA_StatusCode freeFakeInterruptManager(UA_EventSource *es) {
    return UA_STATUSCODE_GOOD;
  }

  UA_InterruptManager *UA_InterruptManager_new_POSIX(const UA_String eventSourceName) {
    static UA_InterruptManager im;
    static UA_String name = UA_String_fromChars("fakeES");
    im.eventSource.eventSourceType = UA_EVENTSOURCETYPE_INTERRUPTMANAGER;
    UA_String_copy(&eventSourceName, &name);
    im.eventSource.start = startFakeInterruptManager;
    im.eventSource.stop = stopFakeInterruptManager;
    im.eventSource.free = freeFakeInterruptManager;
    im.registerInterrupt = registerFakeInterrupt;
    im.deregisterInterrupt = deregisterFakeInterrupt;
    return &im;
  }

  UA_ConnectionManager *UA_ConnectionManager_new_POSIX_UDP(const UA_String eventSourceName) {
    return nullptr;
  }
}

/**************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************/

/* Create a server listening on port 4840 (default) */
UA_Server * opc_ua_server = nullptr;

UA_Int32 myInteger = 42;

REDIRECT_STDOUT_TO(Serial)

/**************************************************************************************
 * LOCAL FUNCTIONS
 **************************************************************************************/

void updater(UA_Server *server) {
  while (1) {
    delay(1000);
    UA_NodeId myIntegerNodeId = UA_NODEID_STRING(1, "the.answer");
    myInteger++;
    UA_Variant myVar;
    UA_Variant_init(&myVar);
    UA_Variant_setScalar(&myVar, &myInteger, &UA_TYPES[UA_TYPES_INT32]);
    UA_Server_writeValue(server, myIntegerNodeId, myVar);
  }
}

/**************************************************************************************
 * SETUP/LOOP
 **************************************************************************************/

void setup()
{
  Serial.begin(115200);
  //auto const start = millis();
  //for (; !Serial && (millis() - start) < 1000; ) { }
  while (!Serial) { }

  /* Initialize Ethernet interface and print obtained IP to Serial. */
  Ethernet.begin();
  Serial.print("Our IP is ");
  Serial.println(Ethernet.localIP());

  /* Create a server listening on port 4840 (default) */
  opc_ua_server = UA_Server_new();

  /* Add a variable node to the server */

  /* 1) Define the variable attributes */
  UA_VariableAttributes attr = UA_VariableAttributes_default;
  attr.displayName = UA_LOCALIZEDTEXT("en-US", "the answer");
  attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE | UA_ACCESSLEVELMASK_HISTORYREAD;
  /* We also set this node to historizing, so the server internals also know from it. */
  attr.historizing = true;
  UA_Variant_setScalar(&attr.value, &myInteger, &UA_TYPES[UA_TYPES_INT32]);

  rtos::Thread t;
  t.start(mbed::callback(updater, opc_ua_server));

  /* 2) Define where the node shall be added with which browsename */
  UA_NodeId newNodeId = UA_NODEID_STRING(1, "the.answer");
  UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
  UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
  UA_NodeId variableType = UA_NODEID_NULL; /* take the default variable type */
  UA_QualifiedName browseName = UA_QUALIFIEDNAME(1, "the answer");

  /* 3) Add the node */
  UA_Server_addVariableNode(opc_ua_server,
                            newNodeId,
                            parentNodeId,
                            parentReferenceNodeId,
                            browseName,
                            variableType,
                            attr,
                            NULL, NULL);

  /* Run the server (until ctrl-c interrupt) */
  UA_StatusCode status = UA_Server_runUntilInterrupt(opc_ua_server);

  /* Clean up */
  UA_Server_delete(opc_ua_server);
}

void loop() {
  // put your main code here, to run repeatedly:
}
