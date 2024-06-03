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

static size_t const OPC_UA_SERVER_THREAD_STACK_SIZE = 16*1024UL;
template <size_t SIZE> struct alignas(uint32_t) OPC_UA_STACK final : public std::array<uint8_t, SIZE> {};
static OPC_UA_STACK<OPC_UA_SERVER_THREAD_STACK_SIZE> OPC_UA_SERVER_THREAD_STACK;

static size_t const OPC_UA_SERVER_THREAD_HEAP_SIZE = 256*1024UL;
template <size_t SIZE> struct alignas(O1HEAP_ALIGNMENT) OPC_UA_HEAP final : public std::array<uint8_t, SIZE> {};
static OPC_UA_HEAP<OPC_UA_SERVER_THREAD_HEAP_SIZE> OPC_UA_SERVER_THREAD_HEAP;

UA_Server * opc_ua_server = nullptr;
O1HeapInstance * o1heap_ins = nullptr;
rtos::Thread opc_ua_server_thread(osPriorityNormal, OPC_UA_SERVER_THREAD_STACK.size(), OPC_UA_SERVER_THREAD_STACK.data());

opcua::DigitalInputManager opta_digital_input_manager;

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

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
  if (!Ethernet.begin()) {
    Serial.println("\"Ethernet.begin()\" failed.");
    for (;;) { }
  }

  /* Initialize heap memory. */
  o1heap_ins = o1heapInit(OPC_UA_SERVER_THREAD_HEAP.data(), OPC_UA_SERVER_THREAD_HEAP.size());
  if (o1heap_ins == nullptr) {
    Serial.println("\"o1heapInit\" failed.");
    for (;;) { }
  }
  UA_mallocSingleton  = o1heap_malloc;
  UA_freeSingleton    = o1heap_free;
  UA_callocSingleton  = o1heap_calloc;
  UA_reallocSingleton = o1heap_realloc;

  opc_ua_server_thread.start(
    +[]()
    {
      /* Create a server listening on port 4840 (default) */
      opc_ua_server = UA_Server_new();
      UA_ServerConfig * config = UA_Server_getConfig(opc_ua_server);

      /* Printing OPC/UA server IP and port. */
      UA_LOG_INFO(config->logging,
                  UA_LOGCATEGORY_SERVER,
                  "Arduino Opta IP: %s",
                  Ethernet.localIP().toString().c_str());

      UA_StatusCode rc = UA_STATUSCODE_GOOD;

      /* Define the Arduino Opta as a OPC/UA object. */
      UA_NodeId opta_node_id;
      rc = opc_ua_define_opta_obj(opc_ua_server, &opta_node_id);
      if (UA_StatusCode_isBad(rc))
      {
        UA_ServerConfig * config = UA_Server_getConfig(opc_ua_server);
        UA_LOG_ERROR(config->logging,
                     UA_LOGCATEGORY_SERVER,
                     "opc_ua_define_opta(...) failed with %s",
                     UA_StatusCode_name(rc));
      }

      /* Define Arduino Opta's digital inputs base object. */
      rc = opta_digital_input_manager.begin(opc_ua_server, opta_node_id);
      if (UA_StatusCode_isBad(rc)) {
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "opta_digital_input_manager.begin(...) failed with %s", UA_StatusCode_name(rc));
        return;
      }
      /* Add the various digital input pins. */
      rc = opta_digital_input_manager.add_digital_input(opc_ua_server, UA_NODEID_STRING(1, "digital-input-value-1"), "Digital Input 1 Value", opcua::on_read_request_opta_digital_input_1);
      rc = opta_digital_input_manager.add_digital_input(opc_ua_server, UA_NODEID_STRING(1, "digital-input-value-2"), "Digital Input 2 Value", opcua::on_read_request_opta_digital_input_2);
      rc = opta_digital_input_manager.add_digital_input(opc_ua_server, UA_NODEID_STRING(1, "digital-input-value-3"), "Digital Input 3 Value", opcua::on_read_request_opta_digital_input_3);
      rc = opta_digital_input_manager.add_digital_input(opc_ua_server, UA_NODEID_STRING(1, "digital-input-value-4"), "Digital Input 4 Value", opcua::on_read_request_opta_digital_input_4);
      rc = opta_digital_input_manager.add_digital_input(opc_ua_server, UA_NODEID_STRING(1, "digital-input-value-5"), "Digital Input 5 Value", opcua::on_read_request_opta_digital_input_5);
      rc = opta_digital_input_manager.add_digital_input(opc_ua_server, UA_NODEID_STRING(1, "digital-input-value-6"), "Digital Input 6 Value", opcua::on_read_request_opta_digital_input_6);
      rc = opta_digital_input_manager.add_digital_input(opc_ua_server, UA_NODEID_STRING(1, "digital-input-value-7"), "Digital Input 7 Value", opcua::on_read_request_opta_digital_input_7);
      rc = opta_digital_input_manager.add_digital_input(opc_ua_server, UA_NODEID_STRING(1, "digital-input-value-8"), "Digital Input 8 Value", opcua::on_read_request_opta_digital_input_8);

      /* Define Arduino Opta's relays to be accessed via OPC/UA. */
      UA_NodeId opta_relay_node_id;
      rc = opc_ua_define_relay_obj(opc_ua_server, opta_node_id, &opta_relay_node_id);
      if (UA_StatusCode_isBad(rc))
      {
        UA_ServerConfig * config = UA_Server_getConfig(opc_ua_server);
        UA_LOG_ERROR(config->logging,
                     UA_LOGCATEGORY_SERVER,
                     "opc_ua_define_relay_obj(...) failed with %s",
                     UA_StatusCode_name(rc));
      }

      unsigned int const ARDUINO_OPTA_RELAY_NUM_RELAYS = 4;
      for (unsigned int relay_num = 1;
           relay_num <= ARDUINO_OPTA_RELAY_NUM_RELAYS;
           relay_num++)
      {
        rc = opc_ua_define_relay(opc_ua_server,
                                 opta_relay_node_id,
                                 relay_num);
        if (UA_StatusCode_isBad(rc))
        {
          UA_ServerConfig * config = UA_Server_getConfig(opc_ua_server);
          UA_LOG_ERROR(config->logging,
                       UA_LOGCATEGORY_SERVER,
                       "opc_ua_define_relay(..., %d, ...) failed with %s",
                       relay_num,
                       UA_StatusCode_name(rc));
        }
      }

      /* Print some threading related message. */
      UA_LOG_INFO(config->logging,
                  UA_LOGCATEGORY_SERVER,
                  "stack: size = %d | free = %d | used = %d | max = %d",
                  opc_ua_server_thread.stack_size(),
                  opc_ua_server_thread.free_stack(),
                  opc_ua_server_thread.used_stack(),
                  opc_ua_server_thread.max_stack());

      /* Log some data concerning heap allocation. */
      UA_LOG_INFO(config->logging,
                  UA_LOGCATEGORY_SERVER,
                  "o1heap: capacity: %d | allocated: %d | peak_allocated: %d",
                  o1heapGetDiagnostics(o1heap_ins).capacity,
                  o1heapGetDiagnostics(o1heap_ins).allocated,
                  o1heapGetDiagnostics(o1heap_ins).peak_allocated);

      /* Run the server (until ctrl-c interrupt) */
      UA_StatusCode const status = UA_Server_runUntilInterrupt(opc_ua_server);
      Serial.println(status);
    });

  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(LED_D0, OUTPUT);
  pinMode(RELAY1, OUTPUT);
}

void loop()
{
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(500);
}
