#include "PortentaEthernet.h"
#include "Arduino_open62541-1.3.x.h"
extern "C" {
#include <open62541.h>

  UA_DateTime UA_DateTime_nowMonotonic() {
    return millis() * UA_DATETIME_MSEC;
  }

  UA_DateTime UA_DateTime_now() {
    return millis() * UA_DATETIME_MSEC;
  }

  UA_Int64 UA_DateTime_localTimeUtcOffset(void) {
    return 0;
  }

  int gethostname(char *str, size_t len) {
    memcpy(str, "arduino", 7);
    return 0;
  }
}

REDIRECT_STDOUT_TO(Serial)

void setup() {

  Serial.begin(115200);
  while (!Serial)
    ;

  //Ethernet.begin();
  //Serial.print("Our IP is ");
  //Serial.println(Ethernet.localIP());

  UA_Boolean waitInternal = false;

  /* Create a server listening on port 4840 (default) */
  UA_Server *server = UA_Server_new();
  //UA_Server *server = UA_Server_newFromFile(UA_STRING_ALLOC("config.json"));

  /* Add a variable node to the server */

  /* 1) Define the variable attributes */
  UA_VariableAttributes attr = UA_VariableAttributes_default;
  attr.displayName = UA_LOCALIZEDTEXT("en-US", "the answer");
  UA_Int32 myInteger = 42;
  UA_Variant_setScalar(&attr.value, &myInteger, &UA_TYPES[UA_TYPES_INT32]);

  /* 2) Define where the node shall be added with which browsename */
  UA_NodeId newNodeId = UA_NODEID_STRING(1, "the.answer");
  UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
  UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
  UA_NodeId variableType = UA_NODEID_NULL; /* take the default variable type */
  UA_QualifiedName browseName = UA_QUALIFIEDNAME(1, "the answer");

  /* 3) Add the node */
  UA_Server_addVariableNode(server, newNodeId, parentNodeId,
                            parentReferenceNodeId, browseName,
                            variableType, attr, NULL, NULL);

  /* Run the server (until ctrl-c interrupt) */
  UA_StatusCode status = UA_Server_run_iterate(server, waitInternal);

  /* Clean up */
  UA_Server_delete(server);
}

void loop() {
  // put your main code here, to run repeatedly:
}
