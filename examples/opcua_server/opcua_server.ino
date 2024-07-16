/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include "PortentaEthernet.h"
#include "Arduino_open62541.h"

#ifndef ARDUINO_OPEN62541_O1HEAP_DEBUG
# define ARDUINO_OPEN62541_O1HEAP_DEBUG (0) /* Change to (1) if you want to see debug messages on Serial concerning o1heap memory calls. */
#endif

#if MBED_HEAP_STATS_ENABLED && MBED_MEM_TRACING_ENABLED && MBED_STACK_STATS_ENABLED
#include "mbed_mem_trace.h"
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

opcua::ArduinoOpta::SharedPtr arduino_opta_opcua;

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

static float arduino_opta_analog_read(pin_size_t const pin)
{
  static float const VOLTAGE_MAX = 3.3;      // Maximum voltage that can be read
  static float const RESOLUTION  = 4096.0;   // 12-bit resolution
  static float const DIVIDER     = 0.3034;   // Voltage divider

  /* Read the actual analog value from the pin. */
  int const pin_value = analogRead(pin);
  /* Convert the raw ADC value into an actual voltage. */
  float const pin_voltage = pin_value * (VOLTAGE_MAX / RESOLUTION) / DIVIDER;

  return pin_voltage;
}

static PinStatus arduino_opta_digital_read(pin_size_t const pin)
{
  float const pin_voltage = arduino_opta_analog_read(pin);

  if (pin_voltage > 5.f) /* Half of the full range as measurable by the ADC. */
    return HIGH;
  else
    return LOW;
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

      /* Printing OPC/UA server IP and port. */
      UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                  "Arduino Opta IP: %s", Ethernet.localIP().toString().c_str());

      /* Determine the Arduino OPC/UA hardware variant. */
      opcua::ArduinoOptaVariant::Type opta_type;
      if (!opcua::ArduinoOptaVariant::get_opta_variant(opta_type)) {
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "opcua::ArduinoOptaVariant::get_opta_variant(...) failed");
        return;
      }
      UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Arduino Opta Variant: %s", opcua::ArduinoOptaVariant::toString(opta_type).c_str());

      /* Read all analog inputs at least once to have them pre-configured as ADCs. */
      std::list<pin_size_t> const ADC_PIN_LIST = { A0, A1, A2, A3, A4, A5, A6, A7 };
      for (auto const adc_pin : ADC_PIN_LIST)
        arduino_opta_analog_read(adc_pin);
      /* Configure analog solution to 12-Bit. */
      analogReadResolution(12);

      /* Define the Arduino Opta as a OPC/UA object. */
      arduino_opta_opcua = opcua::ArduinoOpta::create(opc_ua_server, opta_type);
      if (!arduino_opta_opcua) {
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "opcua::ArduinoOpta::create(...) failed");
        return;
      }

      /* Add the various digital input pins. */
      arduino_opta_opcua->analog_input_mgr()->add_analog_input(opc_ua_server, "Analog Input 1", []() { return arduino_opta_analog_read(A0); });
      arduino_opta_opcua->analog_input_mgr()->add_analog_input(opc_ua_server, "Analog Input 2", []() { return arduino_opta_analog_read(A1); });
      arduino_opta_opcua->analog_input_mgr()->add_analog_input(opc_ua_server, "Analog Input 3", []() { return arduino_opta_analog_read(A2); });
      arduino_opta_opcua->analog_input_mgr()->add_analog_input(opc_ua_server, "Analog Input 4", []() { return arduino_opta_analog_read(A3); });
      arduino_opta_opcua->analog_input_mgr()->add_analog_input(opc_ua_server, "Analog Input 5", []() { return arduino_opta_analog_read(A4); });
      arduino_opta_opcua->analog_input_mgr()->add_analog_input(opc_ua_server, "Analog Input 6", []() { return arduino_opta_analog_read(A5); });
      arduino_opta_opcua->analog_input_mgr()->add_analog_input(opc_ua_server, "Analog Input 7", []() { return arduino_opta_analog_read(A6); });
      arduino_opta_opcua->analog_input_mgr()->add_analog_input(opc_ua_server, "Analog Input 8", []() { return arduino_opta_analog_read(A7); });

      /* Add the various digital input pins. */
      arduino_opta_opcua->digital_input_mgr()->add_digital_input(opc_ua_server, "Digital Input 1", []() { return arduino_opta_digital_read(A0); });
      arduino_opta_opcua->digital_input_mgr()->add_digital_input(opc_ua_server, "Digital Input 2", []() { return arduino_opta_digital_read(A1); });
      arduino_opta_opcua->digital_input_mgr()->add_digital_input(opc_ua_server, "Digital Input 3", []() { return arduino_opta_digital_read(A2); });
      arduino_opta_opcua->digital_input_mgr()->add_digital_input(opc_ua_server, "Digital Input 4", []() { return arduino_opta_digital_read(A3); });
      arduino_opta_opcua->digital_input_mgr()->add_digital_input(opc_ua_server, "Digital Input 5", []() { return arduino_opta_digital_read(A4); });
      arduino_opta_opcua->digital_input_mgr()->add_digital_input(opc_ua_server, "Digital Input 6", []() { return arduino_opta_digital_read(A5); });
      arduino_opta_opcua->digital_input_mgr()->add_digital_input(opc_ua_server, "Digital Input 7", []() { return arduino_opta_digital_read(A6); });
      arduino_opta_opcua->digital_input_mgr()->add_digital_input(opc_ua_server, "Digital Input 8", []() { return arduino_opta_digital_read(A7); });

      /* Add the various relay outputs. */
      arduino_opta_opcua->relay_mgr()->add_relay_output(opc_ua_server, "Relay 1", [](bool const value) { pinMode(RELAY1, OUTPUT); digitalWrite(RELAY1, value); pinMode(LED_D0, OUTPUT); digitalWrite(LED_D0, value); });
      arduino_opta_opcua->relay_mgr()->add_relay_output(opc_ua_server, "Relay 2", [](bool const value) { pinMode(RELAY2, OUTPUT); digitalWrite(RELAY2, value); pinMode(LED_D1, OUTPUT); digitalWrite(LED_D1, value);});
      arduino_opta_opcua->relay_mgr()->add_relay_output(opc_ua_server, "Relay 3", [](bool const value) { pinMode(RELAY3, OUTPUT); digitalWrite(RELAY3, value); pinMode(LED_D2, OUTPUT); digitalWrite(LED_D2, value);});
      arduino_opta_opcua->relay_mgr()->add_relay_output(opc_ua_server, "Relay 4", [](bool const value) { pinMode(RELAY4, OUTPUT); digitalWrite(RELAY4, value); pinMode(LED_D3, OUTPUT); digitalWrite(LED_D3, value);});

      /* Add the various LED outputs. */
      if (opta_type == opcua::ArduinoOptaVariant::Type::WiFi) {
        arduino_opta_opcua->led_mgr()->add_led_output(opc_ua_server, "User LED", [](bool const value) { pinMode(LEDB, OUTPUT); digitalWrite(LEDB, value); });
      }

      /* Print some threading related message. */
      UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                  "stack: size = %d | free = %d | used = %d | max = %d",
                  opc_ua_server_thread.stack_size(),
                  opc_ua_server_thread.free_stack(),
                  opc_ua_server_thread.used_stack(),
                  opc_ua_server_thread.max_stack());

      /* Log some data concerning heap allocation. */
      UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                  "o1heap: capacity: %d | allocated: %d | peak_allocated: %d",
                  o1heapGetDiagnostics(o1heap_ins).capacity,
                  o1heapGetDiagnostics(o1heap_ins).allocated,
                  o1heapGetDiagnostics(o1heap_ins).peak_allocated);

#if MBED_HEAP_STATS_ENABLED && MBED_MEM_TRACING_ENABLED && MBED_STACK_STATS_ENABLED
      /* Print stack/heap memory information. For information how to enable it
       * see https://os.mbed.com/blog/entry/Tracking-memory-usage-with-Mbed-OS/
       */
      int num_thds = osThreadGetCount();
      mbed_stats_stack_t *stats = (mbed_stats_stack_t*) malloc(num_thds * sizeof(mbed_stats_stack_t));

      num_thds = mbed_stats_stack_get_each(stats, num_thds);
      for (int i = 0; i < num_thds; i++)
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Thread: 0x%lX, Stack size: %lu / %lu", stats[i].thread_id, stats[i].max_size, stats[i].reserved_size);
      free(stats);

      mbed_stats_heap_t heap_stats;
      mbed_stats_heap_get(&heap_stats);
      UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Heap size: %lu / %lu bytes", heap_stats.current_size, heap_stats.reserved_size);
#endif

      /* Run the server (until ctrl-c interrupt) */
      UA_StatusCode const status = UA_Server_runUntilInterrupt(opc_ua_server);
    });

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(500);
}
