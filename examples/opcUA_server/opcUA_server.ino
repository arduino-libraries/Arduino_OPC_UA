/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include "PortentaEthernet.h"
#include "Arduino_open62541.h"

#ifndef ARDUINO_OPEN62541_O1HEAP_DEBUG
# define ARDUINO_OPEN62541_O1HEAP_DEBUG (0) /* Change to (1) if you want to see debug messages on Serial concerning o1heap memory calls. */
#endif

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

UA_Server * opc_ua_server = nullptr;

static size_t const OPC_UA_SERVER_THREAD_STACK_SIZE = 32768; /* 32 kB */
static uint8_t alignas(uint32_t) OPC_UA_SERVER_THREAD_STACK[OPC_UA_SERVER_THREAD_STACK_SIZE];
rtos::Thread opc_ua_server_thread(osPriorityNormal, OPC_UA_SERVER_THREAD_STACK_SIZE, OPC_UA_SERVER_THREAD_STACK);

static size_t const OPC_UA_SERVER_THREAD_HEAP_SIZE = 65536*4; /* 64*4 kB */
template <size_t SIZE> struct alignas(O1HEAP_ALIGNMENT) OPC_UA_HEAP final : public std::array<uint8_t, SIZE> {};
static OPC_UA_HEAP<OPC_UA_SERVER_THREAD_HEAP_SIZE> OPC_UA_SERVER_THREAD_HEAP;
O1HeapInstance * o1heap_ins = nullptr;

REDIRECT_STDOUT_TO(Serial)

/**************************************************************************************
 * LOCAL FUNCTIONS
 **************************************************************************************/

extern "C" void * o1heap_malloc(size_t size)
{
#if ARDUINO_OPEN62541_O1HEAP_DEBUG
  if (!o1heapDoInvariantsHold(o1heap_ins))
    Serial.println("malloc error");
#endif

  void * new_ptr = o1heapAllocate(o1heap_ins, size);

#if ARDUINO_OPEN62541_O1HEAP_DEBUG
  char msg[64];
  snprintf(msg, sizeof(msg), "malloc: %d (%X)", size, new_ptr);
  Serial.println(msg);
#endif

  return new_ptr;
}

extern "C" void o1heap_free(void * ptr)
{
#if ARDUINO_OPEN62541_O1HEAP_DEBUG
  if (!o1heapDoInvariantsHold(o1heap_ins))
    Serial.println("free error");

  char msg[64];
  snprintf(msg, sizeof(msg), "free: (%X)", ptr);
  Serial.println(msg);
#endif
  o1heapFree(o1heap_ins, ptr);
}

extern "C" void * o1heap_calloc(size_t nelem, size_t elsize)
{
#if ARDUINO_OPEN62541_O1HEAP_DEBUG
  if (!o1heapDoInvariantsHold(o1heap_ins))
    Serial.println("calloc error");

  char msg[64];
  snprintf(msg, sizeof(msg), "calloc: nelem = %d, elsize = %d", nelem, elsize);
  Serial.println(msg);
#endif

  void * ptr = o1heap_malloc(nelem * elsize);
  memset(ptr, 0, nelem * elsize);
  return ptr;
}

extern "C" void * o1heap_realloc(void * old_ptr, size_t size)
{
#if ARDUINO_OPEN62541_O1HEAP_DEBUG
  if (!o1heapDoInvariantsHold(o1heap_ins))
    Serial.println("realloc error");

  char msg[64];
  snprintf(msg, sizeof(msg), "realloc: old_ptr = %X, size = %d", old_ptr, size);
  Serial.println(msg);
#endif
  void * new_ptr = o1heap_malloc(size);
  memcpy(new_ptr, old_ptr, size);
  o1heap_free(old_ptr);
  return new_ptr;
}

//void updater(UA_Server *server) {
//  while (1) {
//    delay(1000);
//    UA_NodeId myIntegerNodeId = UA_NODEID_STRING(1, "the.answer");
//    myInteger++;
//    UA_Variant myVar;
//    UA_Variant_init(&myVar);
//    UA_Variant_setScalar(&myVar, &myInteger, &UA_TYPES[UA_TYPES_INT32]);
//    UA_Server_writeValue(server, myIntegerNodeId, myVar);
//  }
//}

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

  /* Initialize heap memory. */
  o1heap_ins = o1heapInit(OPC_UA_SERVER_THREAD_HEAP.data(), OPC_UA_SERVER_THREAD_HEAP.size());
  if (o1heap_ins == nullptr) {
    Serial.println("o1heap initialisation failed.");
    for (;;) { }
  }
  char o1heap_info[128] = {0};
  snprintf(o1heap_info,
           sizeof(o1heap_info),
           "o1Heap capacity: %d | allocated: %d | peak_allocated: %d",
           o1heapGetDiagnostics(o1heap_ins).capacity,
           o1heapGetDiagnostics(o1heap_ins).allocated,
           o1heapGetDiagnostics(o1heap_ins).peak_allocated);
  Serial.println(o1heap_info);

  UA_mallocSingleton  = o1heap_malloc;
  UA_freeSingleton    = o1heap_free;
  UA_callocSingleton  = o1heap_calloc;
  UA_reallocSingleton = o1heap_realloc;

  opc_ua_server_thread.start(
    +[]()
    {
      /* Create a server listening on port 4840 (default) */
      opc_ua_server = UA_Server_new();

      UA_StatusCode rc = UA_STATUSCODE_GOOD;
      /* Add a variable node to the server */
      uint32_t const the_answer = 42;
      rc = add_variable(opc_ua_server,
                        UA_LOCALIZEDTEXT("en-US", "the answer"),
                        UA_LOCALIZEDTEXT("en-US","42 is the answer to everything"),
                        UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE,
                        UA_NODEID_STRING(1, "the.answer"),
                        UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                        UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                        UA_QUALIFIEDNAME(1, "the answer"),
                        the_answer);
      if (UA_StatusCode_isBad(rc))
      {
        char msg[32] = {0};
        snprintf(msg, sizeof(msg), "add_variable(..., the_answer) failed with %s", UA_StatusCode_name(rc));
        Serial.println(msg);
      }

      bool const relay_1_active = false;
      rc = add_variable(opc_ua_server,
                        UA_LOCALIZEDTEXT("en-US", "OUTPUT 1"),
                        UA_LOCALIZEDTEXT("en-US","Control relay \"OUTPUT 1\""),
                        UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE,
                        UA_NODEID_STRING(1, "relay.output1"),
                        UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                        UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                        UA_QUALIFIEDNAME(1, "Relay OUTPUT 1"),
                        relay_1_active);
      if (UA_StatusCode_isBad(rc))
      {
        char msg[32] = {0};
        snprintf(msg, sizeof(msg), "add_variable(..., relay_1_active) failed with %s", UA_StatusCode_name(rc));
        Serial.println(msg);
      }

      /* Print some threading related message. */
      char thd_info_msg[128] = {0};
      snprintf(thd_info_msg,
               sizeof(thd_info_msg),
               "stack: size = %d | free = %d | used = %d | max = %d",
               opc_ua_server_thread.stack_size(),
               opc_ua_server_thread.free_stack(),
               opc_ua_server_thread.used_stack(),
               opc_ua_server_thread.max_stack());
      Serial.println(thd_info_msg);

      /* Run the server (until ctrl-c interrupt) */
      UA_StatusCode const status = UA_Server_runUntilInterrupt(opc_ua_server);
      Serial.println(status);
    });

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(500);
}
