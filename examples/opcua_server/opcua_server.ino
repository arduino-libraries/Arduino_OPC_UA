/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include "PortentaEthernet.h"
#include "Arduino_open62541.h"
#include <OptaBlue.h> /* Arduino_Opta_Blueprint */
#include <mbed_rtc_time.h>

#ifndef ARDUINO_OPEN62541_O1HEAP_DEBUG
# define ARDUINO_OPEN62541_O1HEAP_DEBUG (0) /* Change to (1) if you want to see debug messages on Serial concerning o1heap memory calls. */
#endif

#if MBED_HEAP_STATS_ENABLED && MBED_MEM_TRACING_ENABLED && MBED_STACK_STATS_ENABLED
#include "mbed_mem_trace.h"
#endif

#if USE_MODBUS_SENSOR_MD02
# include <ArduinoRS485.h>
# include <ArduinoModbus.h>
#endif

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

#if USE_MODBUS_SENSOR_MD02
static unsigned int const MODBUS_BAUDRATE      = 9600;
static float        const MODBUS_BIT_DURATION  = 1.f / MODBUS_BAUDRATE;
static float        const MODBUS_PRE_DELAY_BR  = MODBUS_BIT_DURATION * 9.6f * 3.5f * 1e6;
static float        const MODBUS_POST_DELAY_BR = MODBUS_BIT_DURATION * 9.6f * 3.5f * 1e6;

static int          const MODBUS_DEVICE_ID                   = 1;
static int          const MODBUS_DEVICE_TEMPERATURE_REGISTER = 0x0001;
static int          const MODBUS_DEVICE_HUMIDITY_REGISTER    = 0x0002;
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
#if USE_MODBUS_SENSOR_MD02
UA_NodeId modbus_md02_temperature_node_id;
#endif

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

#if USE_MODBUS_SENSOR_MD02
  RS485.setDelays(MODBUS_PRE_DELAY_BR, MODBUS_POST_DELAY_BR);
  if (!ModbusRTUClient.begin(MODBUS_BAUDRATE, SERIAL_8N1))
  {
    Serial.println("Failed to start Modbus RTU Client!");
    for (;;) { }
  }
  ModbusRTUClient.setTimeout(2 * 1000UL); /* 2 seconds. */
#endif

  /* Initialize Ethernet interface and print obtained IP to Serial. */
  if (!Ethernet.begin()) {
    Serial.println("\"Ethernet.begin()\" failed.");
    for (;;) { }
  }

  /* Try and obtain the current time via NTP and configure the Arduino
   * Opta's onboard RTC accordingly. The RTC is then used inside the
   * open62541 Arduino wrapper to obtain the correct timestamps for
   * the OPC/UA server.
   */
  EthernetUDP udp_client;
  auto const epoch = opcua::NTPUtils::getTime(udp_client);
  if (epoch > 0) {
    set_time(epoch); /* Directly set RTC of Arduino Opta. */
  } else {
    set_time(opcua::cvt_time(__DATE__)); /* Configure Arduino Opta with time at compile time as last time of defense. */
  }

  /* Initialize Opta Expansion module controller. */
  OptaController.begin();
  OptaController.update();

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

      /* Check availability of expansion modules. */
      uint8_t const opta_expansion_num = OptaController.getExpansionNum();
      UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "OptaController %d expansion modules detected.", opta_expansion_num);
      for(uint8_t i = 0; i < opta_expansion_num; i++)
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Expansion %d: type = %d (\"%16s\"), I2C address= 0x%02X",
                    i, OptaController.getExpansionType(i), opcua::ArduinoOptaExpansionType::toStr(OptaController.getExpansionType(i)).c_str(), OptaController.getExpansionI2Caddress(i));

      /* Expose Arduino Opta expansion module IO via OPC/UA. */
      for(uint8_t i = 0; i < opta_expansion_num; i++)
      {
        ExpansionType_t const exp_type = OptaController.getExpansionType(i);
        if (exp_type == EXPANSION_OPTA_DIGITAL_MEC)
        {
          auto const exp_mech_opcua = arduino_opta_opcua->create_digital_mechanical_expansion(i);
          /* Expose digital/analog pins via OPC/UA. */
          for (uint8_t d = 0; d < OPTA_DIGITAL_IN_NUM; d++)
          {
            char analog_in_name[32] = {0};
            snprintf(analog_in_name, sizeof(analog_in_name), "Analog Input %d", d + 1);
            exp_mech_opcua->analog_input_mgr()->add_analog_input(opc_ua_server, analog_in_name, [i, d]() { return reinterpret_cast<DigitalMechExpansion *>(OptaController.getExpansionPtr(i))->pinVoltage(d); });
          }
          /* Expose mechanical relays via OPC/UA. */
          for (uint8_t r = 0; r < OPTA_DIGITAL_OUT_NUM; r++)
          {
            char mech_relay_name[32] = {0};
            snprintf(mech_relay_name, sizeof(mech_relay_name), "Relay %d", r + 1);
            exp_mech_opcua->relay_mgr()->add_relay_output(opc_ua_server, mech_relay_name, [i, r](bool const value) { reinterpret_cast<DigitalMechExpansion *>(OptaController.getExpansionPtr(i))->digitalWrite(r, value ? HIGH : LOW); });
          }
        }
        else if (exp_type == EXPANSION_OPTA_DIGITAL_STS)
        {
          auto const exp_solid_state_opcua = arduino_opta_opcua->create_digital_solid_state_expansion(i);
          /* Expose digital/analog pins via OPC/UA. */
          for (uint8_t d = 0; d < OPTA_DIGITAL_IN_NUM; d++)
          {
            char analog_in_name[32] = {0};
            snprintf(analog_in_name, sizeof(analog_in_name), "Analog Input %d", d + 1);
            exp_solid_state_opcua->analog_input_mgr()->add_analog_input(opc_ua_server, analog_in_name, [i, d]() { return reinterpret_cast<DigitalStSolidExpansion *>(OptaController.getExpansionPtr(i))->pinVoltage(d); });
          }
          /* Expose solit state relays via OPC/UA. */
          for (uint8_t r = 0; r < OPTA_DIGITAL_OUT_NUM; r++)
          {
            char solid_state_relay_name[32] = {0};
            snprintf(solid_state_relay_name, sizeof(solid_state_relay_name), "Relay %d", r + 1);
            exp_solid_state_opcua->relay_mgr()->add_relay_output(opc_ua_server, solid_state_relay_name, [i, r](bool const value) { reinterpret_cast<DigitalStSolidExpansion *>(OptaController.getExpansionPtr(i))->digitalWrite(r, value ? HIGH : LOW); });
          }
        }
      }

#if USE_MODBUS_SENSOR_MD02
      {
        UA_StatusCode rc = UA_STATUSCODE_GOOD;
        UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
        oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Modbus RS485 MD02 Sensor");
        UA_NodeId modbus_md02_node_id;
        rc = UA_Server_addObjectNode(opc_ua_server,
                                     UA_NODEID_NULL,
                                     arduino_opta_opcua->node_id(),
                                     UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                                     UA_QUALIFIEDNAME(1, "ModbusRs485Md02"),
                                     UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                                     oAttr,
                                     NULL,
                                     &modbus_md02_node_id);
        if (UA_StatusCode_isBad(rc)) {
          UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Modbus MD02 Sensor: UA_Server_addObjectNode(...) failed with %s", UA_StatusCode_name(rc));
          return;
        }

        UA_VariableAttributes temperature_value_attr = UA_VariableAttributes_default;

        /* Obtain the current value of the input pin. */
        UA_Float temperature_value = 0.f;
        UA_Variant_setScalar(&temperature_value_attr.value, &temperature_value, &UA_TYPES[UA_TYPES_FLOAT]);

        temperature_value_attr.displayName = UA_LOCALIZEDTEXT("en-US", "Temperature / °C");
        temperature_value_attr.dataType = UA_TYPES[UA_TYPES_FLOAT].typeId;
        temperature_value_attr.accessLevel = UA_ACCESSLEVELMASK_READ;

        /* Add the variable node. */
        rc = UA_Server_addVariableNode(opc_ua_server,
                                       UA_NODEID_NULL,
                                       modbus_md02_node_id,
                                       UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                       UA_QUALIFIEDNAME(1, "md02_temperature_deg"),
                                       UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                       temperature_value_attr,
                                       NULL,
                                       &modbus_md02_temperature_node_id);
        if (UA_StatusCode_isBad(rc))
        {
          UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Modbus MD02 Sensor: UA_Server_addVariableNode(...) failed with %s", UA_StatusCode_name(rc));
          return;
        }
      }
#endif

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
      size_t const num_thds = osThreadGetCount();
      mbed_stats_stack_t *stack_stats = (mbed_stats_stack_t *) malloc(num_thds * sizeof(mbed_stats_stack_t));
      mbed_stats_stack_get_each(stack_stats, num_thds);

      mbed_stats_thread_t * thd_stats = (mbed_stats_thread_t *) malloc(num_thds * sizeof(mbed_stats_thread_t));
      mbed_stats_thread_get_each(thd_stats, num_thds);

      for (int i = 0; i < num_thds; i++)
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Thread: 0x%lX (\"%s\"), Stack size: %lu / %lu",
                    stack_stats[i].thread_id, thd_stats[i].name, stack_stats[i].max_size, stack_stats[i].reserved_size);
      free(stack_stats);
      free(thd_stats);

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
  /* Always call update as fast as possible */
  OptaController.update();

  /* Determine the number of expansion boards available and call update on them. */
  uint8_t const opta_expansion_num = OptaController.getExpansionNum();
  for(uint8_t i = 0; i < opta_expansion_num; i++)
  {
    ExpansionType_t const exp_type = OptaController.getExpansionType(i);
    if (exp_type == EXPANSION_OPTA_DIGITAL_MEC)
      reinterpret_cast<DigitalMechExpansion *>(OptaController.getExpansionPtr(i))->updateDigitalOutputs();
    else if (exp_type == EXPANSION_OPTA_DIGITAL_STS)
      reinterpret_cast<DigitalStSolidExpansion *>(OptaController.getExpansionPtr(i))->updateDigitalOutputs();
  }

  /* Toggle main LED signalling progress. */
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(500);

#if USE_MODBUS_SENSOR_MD02
  if (!ModbusRTUClient.requestFrom(MODBUS_DEVICE_ID, INPUT_REGISTERS, MODBUS_DEVICE_TEMPERATURE_REGISTER, 1)) {
    Serial.print("failed to read temperature register! ");
    Serial.println(ModbusRTUClient.lastError());
    return;
  }
  if (ModbusRTUClient.available())
  {
    int16_t const temperature_raw = ModbusRTUClient.read();
    float const temperature_deg = temperature_raw / 100.f;
    Serial.println(temperature_deg);

    UA_Float temperature_deg_opcua_value = temperature_deg;
    UA_Variant temperature_deg_opcua_variant;
    UA_Variant_init(&temperature_deg_opcua_variant);
    UA_Variant_setScalar(&temperature_deg_opcua_variant, &temperature_deg_opcua_value, &UA_TYPES[UA_TYPES_FLOAT]);
    UA_Server_writeValue(opc_ua_server, modbus_md02_temperature_node_id, temperature_deg_opcua_variant);
  }
#endif
}
