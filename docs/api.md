# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`namespace ` [`opcua`](#namespaceopcua) | 
`struct ` [`O1HeapDiagnostics`](#struct_o1_heap_diagnostics) | Runtime diagnostic information. This information can be used to facilitate runtime self-testing, as required by certain safety-critical development guidelines. If assertion checks are not disabled, the library will perform automatic runtime self-diagnostics that trigger an assertion failure if a heap corruption is detected. Health checks and validation can be done with o1heapDoInvariantsHold().

# namespace `opcua` <a id="namespaceopcua" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public time_t ` [`cvt_time`](#cvt__time_8h_1ac8a236e4356144a3ee7ebede7d49cfa7)`(char const * time)`            | 
`class ` [`opcua::AnalogExpansion`](#classopcua_1_1_analog_expansion) | 
`class ` [`opcua::DigitalExpansion`](#classopcua_1_1_digital_expansion) | 
`class ` [`opcua::DigitalMechExpansion`](#classopcua_1_1_digital_mech_expansion) | 
`class ` [`opcua::DigitalStSolidExpansion`](#classopcua_1_1_digital_st_solid_expansion) | 
`class ` [`opcua::Expansion`](#classopcua_1_1_expansion) | 
`class ` [`opcua::AnalogInput`](#classopcua_1_1_analog_input) | 
`class ` [`opcua::AnalogInputManager`](#classopcua_1_1_analog_input_manager) | 
`class ` [`opcua::UserButton`](#classopcua_1_1_user_button) | 
`class ` [`opcua::DigitalInput`](#classopcua_1_1_digital_input) | 
`class ` [`opcua::DigitalInputManager`](#classopcua_1_1_digital_input_manager) | 
`class ` [`opcua::Led`](#classopcua_1_1_led) | 
`class ` [`opcua::LedManager`](#classopcua_1_1_led_manager) | 
`class ` [`opcua::Relay`](#classopcua_1_1_relay) | 
`class ` [`opcua::RelayManager`](#classopcua_1_1_relay_manager) | 
`class ` [`opcua::Opta`](#classopcua_1_1_opta) | 
`class ` [`opcua::OptaExpansionManager`](#classopcua_1_1_opta_expansion_manager) | 
`class ` [`opcua::OptaVariant`](#classopcua_1_1_opta_variant) | 
`class ` [`opcua::NTPUtils`](#classopcua_1_1_n_t_p_utils) | 
`class ` [`opcua::ExpansionType`](#classopcua_1_1_expansion_type) | 

## Members

#### `public time_t ` [`cvt_time`](#cvt__time_8h_1ac8a236e4356144a3ee7ebede7d49cfa7)`(char const * time)` <a id="cvt__time_8h_1ac8a236e4356144a3ee7ebede7d49cfa7" class="anchor"></a>

# class `opcua::AnalogExpansion` <a id="classopcua_1_1_analog_expansion" class="anchor"></a>

```cpp
class opcua::AnalogExpansion
  : public opcua::Expansion
```

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`AnalogExpansion`](#classopcua_1_1_analog_expansion_1a43039d49f853487893aef8108cef366d) |  |
| [`SharedPtr`](#classopcua_1_1_analog_expansion_1a3a99cadc0594891e0ce7ee9acc06d1f3) |  |
| [`create`](#classopcua_1_1_analog_expansion_1a13a953b2d732d52f0c6772957b45abe8) |  |

## Members

### `AnalogExpansion` <a id="classopcua_1_1_analog_expansion_1a43039d49f853487893aef8108cef366d" class="anchor"></a>

```cpp
inline AnalogExpansion(UA_Server * server, UA_NodeId const parent_node_id, char * display_name, char * node_name, char * model_name)
```

<hr />

### `SharedPtr` <a id="classopcua_1_1_analog_expansion_1a3a99cadc0594891e0ce7ee9acc06d1f3" class="anchor"></a>

```cpp
typedef SharedPtr
```

<hr />

### `create` <a id="classopcua_1_1_analog_expansion_1a13a953b2d732d52f0c6772957b45abe8" class="anchor"></a>

```cpp
inline static SharedPtr create(UA_Server * server, UA_NodeId const parent_node_id, uint8_t const exp_num)
```

<hr />

# class `opcua::DigitalExpansion` <a id="classopcua_1_1_digital_expansion" class="anchor"></a>

```cpp
class opcua::DigitalExpansion
  : public opcua::Expansion
```

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`DigitalExpansion`](#classopcua_1_1_digital_expansion_1a83aace406ca80bde86e563dcf4ea12fe) |  |
| [`analog_input_mgr`](#classopcua_1_1_digital_expansion_1aa70f758ccbffbe5644f5dc30141dc09d) |  |
| [`digital_input_mgr`](#classopcua_1_1_digital_expansion_1a932f1b307326b0c3a28e6ad1a7357e1e) |  |
| [`relay_mgr`](#classopcua_1_1_digital_expansion_1a87b2e863bb001b3b9c45300cef4f6db2) |  |
| [`SharedPtr`](#classopcua_1_1_digital_expansion_1a808388135d0335260aed3725a4ca8eb9) |  |

## Members

### `DigitalExpansion` <a id="classopcua_1_1_digital_expansion_1a83aace406ca80bde86e563dcf4ea12fe" class="anchor"></a>

```cpp
inline DigitalExpansion(UA_Server * server, UA_NodeId const parent_node_id, char * display_name, char * node_name, char * model_name)
```

<hr />

### `analog_input_mgr` <a id="classopcua_1_1_digital_expansion_1aa70f758ccbffbe5644f5dc30141dc09d" class="anchor"></a>

```cpp
AnalogInputManager::SharedPtr analog_input_mgr()
```

<hr />

### `digital_input_mgr` <a id="classopcua_1_1_digital_expansion_1a932f1b307326b0c3a28e6ad1a7357e1e" class="anchor"></a>

```cpp
DigitalInputManager::SharedPtr digital_input_mgr()
```

<hr />

### `relay_mgr` <a id="classopcua_1_1_digital_expansion_1a87b2e863bb001b3b9c45300cef4f6db2" class="anchor"></a>

```cpp
RelayManager::SharedPtr relay_mgr()
```

<hr />

### `SharedPtr` <a id="classopcua_1_1_digital_expansion_1a808388135d0335260aed3725a4ca8eb9" class="anchor"></a>

```cpp
typedef SharedPtr
```

<hr />

# class `opcua::DigitalMechExpansion` <a id="classopcua_1_1_digital_mech_expansion" class="anchor"></a>

```cpp
class opcua::DigitalMechExpansion
  : public opcua::DigitalExpansion
```

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`DigitalMechExpansion`](#classopcua_1_1_digital_mech_expansion_1ab35f6fd4ee4089d6f4312f11ef863c70) |  |
| [`SharedPtr`](#classopcua_1_1_digital_mech_expansion_1abc60f0e66b8f12e051497c58b113a16e) |  |
| [`create`](#classopcua_1_1_digital_mech_expansion_1af777877670455dbd9032ca0aa47fcee3) |  |

## Members

### `DigitalMechExpansion` <a id="classopcua_1_1_digital_mech_expansion_1ab35f6fd4ee4089d6f4312f11ef863c70" class="anchor"></a>

```cpp
inline DigitalMechExpansion(UA_Server * server, UA_NodeId const parent_node_id, char * display_name, char * node_name, char * model_name)
```

<hr />

### `SharedPtr` <a id="classopcua_1_1_digital_mech_expansion_1abc60f0e66b8f12e051497c58b113a16e" class="anchor"></a>

```cpp
typedef SharedPtr
```

<hr />

### `create` <a id="classopcua_1_1_digital_mech_expansion_1af777877670455dbd9032ca0aa47fcee3" class="anchor"></a>

```cpp
inline static SharedPtr create(UA_Server * server, UA_NodeId const parent_node_id, uint8_t const exp_num)
```

<hr />

# class `opcua::DigitalStSolidExpansion` <a id="classopcua_1_1_digital_st_solid_expansion" class="anchor"></a>

```cpp
class opcua::DigitalStSolidExpansion
  : public opcua::DigitalExpansion
```

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`DigitalStSolidExpansion`](#classopcua_1_1_digital_st_solid_expansion_1ad73696f5eabb7fb48c7ada0f9745e764) |  |
| [`SharedPtr`](#classopcua_1_1_digital_st_solid_expansion_1a8bb44b6e51c634b1910dafb066f4e448) |  |
| [`create`](#classopcua_1_1_digital_st_solid_expansion_1a6b94afd184c4d435cea8ad32297fc045) |  |

## Members

### `DigitalStSolidExpansion` <a id="classopcua_1_1_digital_st_solid_expansion_1ad73696f5eabb7fb48c7ada0f9745e764" class="anchor"></a>

```cpp
inline DigitalStSolidExpansion(UA_Server * server, UA_NodeId const parent_node_id, char * display_name, char * node_name, char * model_name)
```

<hr />

### `SharedPtr` <a id="classopcua_1_1_digital_st_solid_expansion_1a8bb44b6e51c634b1910dafb066f4e448" class="anchor"></a>

```cpp
typedef SharedPtr
```

<hr />

### `create` <a id="classopcua_1_1_digital_st_solid_expansion_1a6b94afd184c4d435cea8ad32297fc045" class="anchor"></a>

```cpp
inline static SharedPtr create(UA_Server * server, UA_NodeId const parent_node_id, uint8_t const exp_num)
```

<hr />

# class `opcua::Expansion` <a id="classopcua_1_1_expansion" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`Expansion`](#classopcua_1_1_expansion_1a52b0201d688fe43ddf8e662ce4a2ec32) |  |
| [`SharedPtr`](#classopcua_1_1_expansion_1a0e496feb6cd2259a2a9f4cded8f9076a) |  |

## Members

### `Expansion` <a id="classopcua_1_1_expansion_1a52b0201d688fe43ddf8e662ce4a2ec32" class="anchor"></a>

```cpp
Expansion(UA_Server * server, UA_NodeId const parent_node_id, char * display_name, char * node_name, char * model_name)
```

<hr />

### `SharedPtr` <a id="classopcua_1_1_expansion_1a0e496feb6cd2259a2a9f4cded8f9076a" class="anchor"></a>

```cpp
typedef SharedPtr
```

<hr />

# class `opcua::AnalogInput` <a id="classopcua_1_1_analog_input" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`AnalogInput`](#classopcua_1_1_analog_input_1ae30d8e20ce45b11730cdb43c4f9c16c4) |  |
| [`onReadRequest`](#classopcua_1_1_analog_input_1a3bacb7c68ba84388ad5c2f88012affe0) |  |
| [`SharedPtr`](#classopcua_1_1_analog_input_1abfac39c8c3cfda600c49522bb1b433c0) |  |
| [`OnReadRequestFunc`](#classopcua_1_1_analog_input_1a76301ddd02080ac8f8e1916b33d31116) |  |
| [`create`](#classopcua_1_1_analog_input_1a11a3e1f0bdef544ba77c15c16d5a2689) |  |

## Members

### `AnalogInput` <a id="classopcua_1_1_analog_input_1ae30d8e20ce45b11730cdb43c4f9c16c4" class="anchor"></a>

```cpp
AnalogInput(UA_NodeId const & node_id, OnReadRequestFunc const on_read_request)
```

<hr />

### `onReadRequest` <a id="classopcua_1_1_analog_input_1a3bacb7c68ba84388ad5c2f88012affe0" class="anchor"></a>

```cpp
void onReadRequest(UA_Server * server, UA_NodeId const * node_id)
```

<hr />

### `SharedPtr` <a id="classopcua_1_1_analog_input_1abfac39c8c3cfda600c49522bb1b433c0" class="anchor"></a>

```cpp
typedef SharedPtr
```

<hr />

### `OnReadRequestFunc` <a id="classopcua_1_1_analog_input_1a76301ddd02080ac8f8e1916b33d31116" class="anchor"></a>

```cpp
typedef OnReadRequestFunc
```

<hr />

### `create` <a id="classopcua_1_1_analog_input_1a11a3e1f0bdef544ba77c15c16d5a2689" class="anchor"></a>

```cpp
static SharedPtr create(UA_Server * server, UA_NodeId const & parent_node_id, const char * display_name, OnReadRequestFunc const on_read_request)
```

<hr />

# class `opcua::AnalogInputManager` <a id="classopcua_1_1_analog_input_manager" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`AnalogInputManager`](#classopcua_1_1_analog_input_manager_1a4acded183249c128a0577d592434667a) |  |
| [`add_analog_input`](#classopcua_1_1_analog_input_manager_1a3e3f23fcab755f090a4da8181106e54e) |  |
| [`SharedPtr`](#classopcua_1_1_analog_input_manager_1aaf63f82d26fae9a89478d568acdbd390) |  |
| [`create`](#classopcua_1_1_analog_input_manager_1a68d99b738809b67b102ce91fbfbfaf4c) |  |

## Members

### `AnalogInputManager` <a id="classopcua_1_1_analog_input_manager_1a4acded183249c128a0577d592434667a" class="anchor"></a>

```cpp
AnalogInputManager(UA_NodeId const & node_id)
```

<hr />

### `add_analog_input` <a id="classopcua_1_1_analog_input_manager_1a3e3f23fcab755f090a4da8181106e54e" class="anchor"></a>

```cpp
void add_analog_input(UA_Server * server, const char * display_name, AnalogInput::OnReadRequestFunc const on_read_request_func)
```

<hr />

### `SharedPtr` <a id="classopcua_1_1_analog_input_manager_1aaf63f82d26fae9a89478d568acdbd390" class="anchor"></a>

```cpp
typedef SharedPtr
```

<hr />

### `create` <a id="classopcua_1_1_analog_input_manager_1a68d99b738809b67b102ce91fbfbfaf4c" class="anchor"></a>

```cpp
static SharedPtr create(UA_Server * server, UA_NodeId const parent_node_id)
```

<hr />

# class `opcua::UserButton` <a id="classopcua_1_1_user_button" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`UserButton`](#classopcua_1_1_user_button_1a8a18ad7cb6edfefc58a8f1fe7cd5b87d) |  |
| [`onReadRequest`](#classopcua_1_1_user_button_1a211f565d05611888ec518de01ed6f120) |  |
| [`SharedPtr`](#classopcua_1_1_user_button_1a5ae06baa98d9a035629c86076d96bfc5) |  |
| [`create`](#classopcua_1_1_user_button_1aaccd71565a95f2c50e33c52077c16171) |  |

## Members

### `UserButton` <a id="classopcua_1_1_user_button_1a8a18ad7cb6edfefc58a8f1fe7cd5b87d" class="anchor"></a>

```cpp
UserButton(UA_NodeId const & node_id)
```

<hr />

### `onReadRequest` <a id="classopcua_1_1_user_button_1a211f565d05611888ec518de01ed6f120" class="anchor"></a>

```cpp
void onReadRequest(UA_Server * server, UA_NodeId const * node_id)
```

<hr />

### `SharedPtr` <a id="classopcua_1_1_user_button_1a5ae06baa98d9a035629c86076d96bfc5" class="anchor"></a>

```cpp
typedef SharedPtr
```

<hr />

### `create` <a id="classopcua_1_1_user_button_1aaccd71565a95f2c50e33c52077c16171" class="anchor"></a>

```cpp
static SharedPtr create(UA_Server * server, UA_NodeId const & parent_node_id)
```

<hr />

# class `opcua::DigitalInput` <a id="classopcua_1_1_digital_input" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`DigitalInput`](#classopcua_1_1_digital_input_1a0da78dff02b4ef7bd8038bab590413da) |  |
| [`onReadRequest`](#classopcua_1_1_digital_input_1a07d7f2c66fd7a856d28852fb72015243) |  |
| [`SharedPtr`](#classopcua_1_1_digital_input_1a5ed8dab221203259b007d15bb332edc8) |  |
| [`OnReadRequestFunc`](#classopcua_1_1_digital_input_1ae45c9b0e3cb2774b2e39431a7feccf41) |  |
| [`create`](#classopcua_1_1_digital_input_1a844932d3127b5adeedd8c7dc5c0f2feb) |  |

## Members

### `DigitalInput` <a id="classopcua_1_1_digital_input_1a0da78dff02b4ef7bd8038bab590413da" class="anchor"></a>

```cpp
DigitalInput(UA_NodeId const & node_id, OnReadRequestFunc const on_read_request)
```

<hr />

### `onReadRequest` <a id="classopcua_1_1_digital_input_1a07d7f2c66fd7a856d28852fb72015243" class="anchor"></a>

```cpp
void onReadRequest(UA_Server * server, UA_NodeId const * node_id)
```

<hr />

### `SharedPtr` <a id="classopcua_1_1_digital_input_1a5ed8dab221203259b007d15bb332edc8" class="anchor"></a>

```cpp
typedef SharedPtr
```

<hr />

### `OnReadRequestFunc` <a id="classopcua_1_1_digital_input_1ae45c9b0e3cb2774b2e39431a7feccf41" class="anchor"></a>

```cpp
typedef OnReadRequestFunc
```

<hr />

### `create` <a id="classopcua_1_1_digital_input_1a844932d3127b5adeedd8c7dc5c0f2feb" class="anchor"></a>

```cpp
static SharedPtr create(UA_Server * server, UA_NodeId const & parent_node_id, const char * display_name, OnReadRequestFunc const on_read_request)
```

<hr />

# class `opcua::DigitalInputManager` <a id="classopcua_1_1_digital_input_manager" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`DigitalInputManager`](#classopcua_1_1_digital_input_manager_1aa1a41ef9de849beb644a197c5d69c25e) |  |
| [`add_digital_input`](#classopcua_1_1_digital_input_manager_1af8b0c74d437131c49c78999af4a2d3bc) |  |
| [`SharedPtr`](#classopcua_1_1_digital_input_manager_1a65c34fbf328ac93e94931922547e2bbf) |  |
| [`create`](#classopcua_1_1_digital_input_manager_1aa4f8ec8ba017a9c51d5e8ce14f0d5775) |  |

## Members

### `DigitalInputManager` <a id="classopcua_1_1_digital_input_manager_1aa1a41ef9de849beb644a197c5d69c25e" class="anchor"></a>

```cpp
DigitalInputManager(UA_NodeId const & node_id)
```

<hr />

### `add_digital_input` <a id="classopcua_1_1_digital_input_manager_1af8b0c74d437131c49c78999af4a2d3bc" class="anchor"></a>

```cpp
void add_digital_input(UA_Server * server, const char * display_name, DigitalInput::OnReadRequestFunc const on_read_request_func)
```

<hr />

### `SharedPtr` <a id="classopcua_1_1_digital_input_manager_1a65c34fbf328ac93e94931922547e2bbf" class="anchor"></a>

```cpp
typedef SharedPtr
```

<hr />

### `create` <a id="classopcua_1_1_digital_input_manager_1aa4f8ec8ba017a9c51d5e8ce14f0d5775" class="anchor"></a>

```cpp
static SharedPtr create(UA_Server * server, UA_NodeId const parent_node_id)
```

<hr />

# class `opcua::Led` <a id="classopcua_1_1_led" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`Led`](#classopcua_1_1_led_1a8fc018148c11c526eddb312b6765d647) |  |
| [`onWriteRequest`](#classopcua_1_1_led_1aaf8221b4bc407e27e19d4efdbc2eba4e) |  |
| [`SharedPtr`](#classopcua_1_1_led_1ae98b3b6f5b9fc5efa65f5cb9afd36d26) |  |
| [`OnSetLedStateFunc`](#classopcua_1_1_led_1aaf87efcccae9e4a8bdbf44f59aabb448) |  |
| [`create`](#classopcua_1_1_led_1a629e48c791ae316f9ca0f08038ddcfe1) |  |

## Members

### `Led` <a id="classopcua_1_1_led_1a8fc018148c11c526eddb312b6765d647" class="anchor"></a>

```cpp
Led(UA_NodeId const & node_id, OnSetLedStateFunc const on_set_led_state)
```

<hr />

### `onWriteRequest` <a id="classopcua_1_1_led_1aaf8221b4bc407e27e19d4efdbc2eba4e" class="anchor"></a>

```cpp
void onWriteRequest(UA_Server * server, UA_NodeId const * node_id, bool const value)
```

<hr />

### `SharedPtr` <a id="classopcua_1_1_led_1ae98b3b6f5b9fc5efa65f5cb9afd36d26" class="anchor"></a>

```cpp
typedef SharedPtr
```

<hr />

### `OnSetLedStateFunc` <a id="classopcua_1_1_led_1aaf87efcccae9e4a8bdbf44f59aabb448" class="anchor"></a>

```cpp
typedef OnSetLedStateFunc
```

<hr />

### `create` <a id="classopcua_1_1_led_1a629e48c791ae316f9ca0f08038ddcfe1" class="anchor"></a>

```cpp
static SharedPtr create(UA_Server * server, UA_NodeId const & parent_node_id, const char * display_name, OnSetLedStateFunc const on_set_led_state)
```

<hr />

# class `opcua::LedManager` <a id="classopcua_1_1_led_manager" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`LedManager`](#classopcua_1_1_led_manager_1a1388f892d85f566acacca95b10b4c62a) |  |
| [`add_led_output`](#classopcua_1_1_led_manager_1ab8b5aaba9ad51d96e4e6d4167973ce9f) |  |
| [`SharedPtr`](#classopcua_1_1_led_manager_1add9494665b55716dcdb70b9ce1e0e1e2) |  |
| [`create`](#classopcua_1_1_led_manager_1a34dfb842af941ecc7505050808885e0f) |  |

## Members

### `LedManager` <a id="classopcua_1_1_led_manager_1a1388f892d85f566acacca95b10b4c62a" class="anchor"></a>

```cpp
LedManager(UA_NodeId const & node_id)
```

<hr />

### `add_led_output` <a id="classopcua_1_1_led_manager_1ab8b5aaba9ad51d96e4e6d4167973ce9f" class="anchor"></a>

```cpp
void add_led_output(UA_Server * server, const char * display_name, Led::OnSetLedStateFunc const on_set_led_state)
```

<hr />

### `SharedPtr` <a id="classopcua_1_1_led_manager_1add9494665b55716dcdb70b9ce1e0e1e2" class="anchor"></a>

```cpp
typedef SharedPtr
```

<hr />

### `create` <a id="classopcua_1_1_led_manager_1a34dfb842af941ecc7505050808885e0f" class="anchor"></a>

```cpp
static SharedPtr create(UA_Server * server, UA_NodeId const parent_node_id)
```

<hr />

# class `opcua::Relay` <a id="classopcua_1_1_relay" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`Relay`](#classopcua_1_1_relay_1aee598064d5f606fcd74e8fe473af1232) |  |
| [`onWriteRequest`](#classopcua_1_1_relay_1aaea6db4d009ec591232c10d5ade7f861) |  |
| [`SharedPtr`](#classopcua_1_1_relay_1a28a191bf7c9a5d6b769d7662063f47d7) |  |
| [`OnSetRelayStateFunc`](#classopcua_1_1_relay_1a52b846933e1fb40082c3c76dba8b03ed) |  |
| [`create`](#classopcua_1_1_relay_1ae26e71efaed1d390c3c4f62e831fce0d) |  |

## Members

### `Relay` <a id="classopcua_1_1_relay_1aee598064d5f606fcd74e8fe473af1232" class="anchor"></a>

```cpp
Relay(UA_NodeId const & node_id, OnSetRelayStateFunc const on_set_relay_state)
```

<hr />

### `onWriteRequest` <a id="classopcua_1_1_relay_1aaea6db4d009ec591232c10d5ade7f861" class="anchor"></a>

```cpp
void onWriteRequest(UA_Server * server, UA_NodeId const * node_id, bool const value)
```

<hr />

### `SharedPtr` <a id="classopcua_1_1_relay_1a28a191bf7c9a5d6b769d7662063f47d7" class="anchor"></a>

```cpp
typedef SharedPtr
```

<hr />

### `OnSetRelayStateFunc` <a id="classopcua_1_1_relay_1a52b846933e1fb40082c3c76dba8b03ed" class="anchor"></a>

```cpp
typedef OnSetRelayStateFunc
```

<hr />

### `create` <a id="classopcua_1_1_relay_1ae26e71efaed1d390c3c4f62e831fce0d" class="anchor"></a>

```cpp
static SharedPtr create(UA_Server * server, UA_NodeId const & parent_node_id, const char * display_name, OnSetRelayStateFunc const on_set_relay_state)
```

<hr />

# class `opcua::RelayManager` <a id="classopcua_1_1_relay_manager" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`RelayManager`](#classopcua_1_1_relay_manager_1a9d4e2106b768a1f1fa0afd4a5056b962) |  |
| [`add_relay_output`](#classopcua_1_1_relay_manager_1ae014ed047413e04ff3e72a924a2569d1) |  |
| [`SharedPtr`](#classopcua_1_1_relay_manager_1a5ed69275e13c134f54d16ba27eabc34c) |  |
| [`create`](#classopcua_1_1_relay_manager_1ae292144fb50a7f4b05e05f2520e41c21) |  |

## Members

### `RelayManager` <a id="classopcua_1_1_relay_manager_1a9d4e2106b768a1f1fa0afd4a5056b962" class="anchor"></a>

```cpp
RelayManager(UA_NodeId const & node_id)
```

<hr />

### `add_relay_output` <a id="classopcua_1_1_relay_manager_1ae014ed047413e04ff3e72a924a2569d1" class="anchor"></a>

```cpp
void add_relay_output(UA_Server * server, const char * display_name, Relay::OnSetRelayStateFunc const on_set_relay_state)
```

<hr />

### `SharedPtr` <a id="classopcua_1_1_relay_manager_1a5ed69275e13c134f54d16ba27eabc34c" class="anchor"></a>

```cpp
typedef SharedPtr
```

<hr />

### `create` <a id="classopcua_1_1_relay_manager_1ae292144fb50a7f4b05e05f2520e41c21" class="anchor"></a>

```cpp
static SharedPtr create(UA_Server * server, UA_NodeId const parent_node_id)
```

<hr />

# class `opcua::Opta` <a id="classopcua_1_1_opta" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`Opta`](#classopcua_1_1_opta_1ad6db2b203e9f15634ebd6b8e8e4898a2) |  |
| [`analog_input_mgr`](#classopcua_1_1_opta_1aa7667b3d727e6f3f0666dbc1d342b158) |  |
| [`digital_input_mgr`](#classopcua_1_1_opta_1aa34113d33f79bbb62f32cbdbf16d1230) |  |
| [`relay_mgr`](#classopcua_1_1_opta_1a7c685d9c3d44effae6e6e703cbb3b993) |  |
| [`led_mgr`](#classopcua_1_1_opta_1a50290f0e0fef4434ad82d6b3689c3423) |  |
| [`node_id`](#classopcua_1_1_opta_1a7c336a54bff79733569d0e268d210520) |  |
| [`SharedPtr`](#classopcua_1_1_opta_1a75b2e05ac5b273859709490686dfa165) |  |
| [`create`](#classopcua_1_1_opta_1a01f8da6cd187c6237c903dc6d004828a) |  |

## Members

### `Opta` <a id="classopcua_1_1_opta_1ad6db2b203e9f15634ebd6b8e8e4898a2" class="anchor"></a>

```cpp
Opta(UA_Server * server, UA_NodeId const & node_id)
```

<hr />

### `analog_input_mgr` <a id="classopcua_1_1_opta_1aa7667b3d727e6f3f0666dbc1d342b158" class="anchor"></a>

```cpp
AnalogInputManager::SharedPtr analog_input_mgr()
```

<hr />

### `digital_input_mgr` <a id="classopcua_1_1_opta_1aa34113d33f79bbb62f32cbdbf16d1230" class="anchor"></a>

```cpp
DigitalInputManager::SharedPtr digital_input_mgr()
```

<hr />

### `relay_mgr` <a id="classopcua_1_1_opta_1a7c685d9c3d44effae6e6e703cbb3b993" class="anchor"></a>

```cpp
RelayManager::SharedPtr relay_mgr()
```

<hr />

### `led_mgr` <a id="classopcua_1_1_opta_1a50290f0e0fef4434ad82d6b3689c3423" class="anchor"></a>

```cpp
LedManager::SharedPtr led_mgr()
```

<hr />

### `node_id` <a id="classopcua_1_1_opta_1a7c336a54bff79733569d0e268d210520" class="anchor"></a>

```cpp
inline UA_NodeId node_id() const
```

<hr />

### `SharedPtr` <a id="classopcua_1_1_opta_1a75b2e05ac5b273859709490686dfa165" class="anchor"></a>

```cpp
typedef SharedPtr
```

<hr />

### `create` <a id="classopcua_1_1_opta_1a01f8da6cd187c6237c903dc6d004828a" class="anchor"></a>

```cpp
static SharedPtr create(UA_Server * server, OptaVariant::Type const opta_type)
```

<hr />

# class `opcua::OptaExpansionManager` <a id="classopcua_1_1_opta_expansion_manager" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`OptaExpansionManager`](#classopcua_1_1_opta_expansion_manager_1a50f8f17012161470f0c80efa83f8aba8) |  |
| [`create_digital_mechanical_expansion`](#classopcua_1_1_opta_expansion_manager_1a4ccb3789aab33df7df7d92a1a741bd84) |  |
| [`create_digital_solid_state_expansion`](#classopcua_1_1_opta_expansion_manager_1adf13057818a23b761898b7f263f7811b) |  |
| [`create_analog_expansion`](#classopcua_1_1_opta_expansion_manager_1ab7d5c5d2d1a35f97be82ae45ce36dafd) |  |
| [`SharedPtr`](#classopcua_1_1_opta_expansion_manager_1abd9459852a863117520d564b018779dd) |  |
| [`create`](#classopcua_1_1_opta_expansion_manager_1a1fe5f600c6a428877e5c3fc2529a1db6) |  |

## Members

### `OptaExpansionManager` <a id="classopcua_1_1_opta_expansion_manager_1a50f8f17012161470f0c80efa83f8aba8" class="anchor"></a>

```cpp
inline OptaExpansionManager(UA_Server * server)
```

<hr />

### `create_digital_mechanical_expansion` <a id="classopcua_1_1_opta_expansion_manager_1a4ccb3789aab33df7df7d92a1a741bd84" class="anchor"></a>

```cpp
DigitalMechExpansion::SharedPtr create_digital_mechanical_expansion(uint8_t const exp_num)
```

<hr />

### `create_digital_solid_state_expansion` <a id="classopcua_1_1_opta_expansion_manager_1adf13057818a23b761898b7f263f7811b" class="anchor"></a>

```cpp
DigitalStSolidExpansion::SharedPtr create_digital_solid_state_expansion(uint8_t const exp_num)
```

<hr />

### `create_analog_expansion` <a id="classopcua_1_1_opta_expansion_manager_1ab7d5c5d2d1a35f97be82ae45ce36dafd" class="anchor"></a>

```cpp
AnalogExpansion::SharedPtr create_analog_expansion(uint8_t const exp_num)
```

<hr />

### `SharedPtr` <a id="classopcua_1_1_opta_expansion_manager_1abd9459852a863117520d564b018779dd" class="anchor"></a>

```cpp
typedef SharedPtr
```

<hr />

### `create` <a id="classopcua_1_1_opta_expansion_manager_1a1fe5f600c6a428877e5c3fc2529a1db6" class="anchor"></a>

```cpp
inline static SharedPtr create(UA_Server * server)
```

<hr />

# class `opcua::OptaVariant` <a id="classopcua_1_1_opta_variant" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`OptaVariant`](#classopcua_1_1_opta_variant_1acaaa63b7b37af5fab4f3df0080669d76) |  |
| [`OptaVariant`](#classopcua_1_1_opta_variant_1a82a5e186512309818c5a4922e18097b6) |  |
| [`Type`](#classopcua_1_1_opta_variant_1abd647955f6c174916e3c0e25ed240ea8) |  |
| [`get_opta_variant`](#classopcua_1_1_opta_variant_1a0b7ae42903e8beabeaf6962db7504d35) |  |
| [`toString`](#classopcua_1_1_opta_variant_1aa2b41d503d530c8f135f420b54d94068) |  |
| [`toSKUString`](#classopcua_1_1_opta_variant_1aba13996161689f6feb65753daa4e796e) |  |

## Members

### `OptaVariant` <a id="classopcua_1_1_opta_variant_1acaaa63b7b37af5fab4f3df0080669d76" class="anchor"></a>

```cpp
OptaVariant() = delete
```

<hr />

### `OptaVariant` <a id="classopcua_1_1_opta_variant_1a82a5e186512309818c5a4922e18097b6" class="anchor"></a>

```cpp
OptaVariant( OptaVariant const &) = delete
```

<hr />

### `Type` <a id="classopcua_1_1_opta_variant_1abd647955f6c174916e3c0e25ed240ea8" class="anchor"></a>

```cpp
enum Type
```

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
Lite            | 
RS485            | 
WiFi            | 

<hr />

### `get_opta_variant` <a id="classopcua_1_1_opta_variant_1a0b7ae42903e8beabeaf6962db7504d35" class="anchor"></a>

```cpp
static bool get_opta_variant(Type & type)
```

<hr />

### `toString` <a id="classopcua_1_1_opta_variant_1aa2b41d503d530c8f135f420b54d94068" class="anchor"></a>

```cpp
static std::string toString(Type const type)
```

<hr />

### `toSKUString` <a id="classopcua_1_1_opta_variant_1aba13996161689f6feb65753daa4e796e" class="anchor"></a>

```cpp
static std::string toSKUString(Type const type)
```

<hr />

# class `opcua::NTPUtils` <a id="classopcua_1_1_n_t_p_utils" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`getTime`](#classopcua_1_1_n_t_p_utils_1afb634cf860f54e4cc7d1cc23073af912) |  |

## Members

### `getTime` <a id="classopcua_1_1_n_t_p_utils_1afb634cf860f54e4cc7d1cc23073af912" class="anchor"></a>

```cpp
static unsigned long getTime(UDP & udp)
```

<hr />

# class `opcua::ExpansionType` <a id="classopcua_1_1_expansion_type" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`ExpansionType`](#classopcua_1_1_expansion_type_1a23ebe20fe86bce334acbebca12453f97) |  |
| [`ExpansionType`](#classopcua_1_1_expansion_type_1a93119a7176cebcc818038cc2cb5bd566) |  |
| [`toStr`](#classopcua_1_1_expansion_type_1a34fa70ff71feda985dd570b7e25f2286) |  |

## Members

### `ExpansionType` <a id="classopcua_1_1_expansion_type_1a23ebe20fe86bce334acbebca12453f97" class="anchor"></a>

```cpp
ExpansionType() = delete
```

<hr />

### `ExpansionType` <a id="classopcua_1_1_expansion_type_1a93119a7176cebcc818038cc2cb5bd566" class="anchor"></a>

```cpp
ExpansionType( ExpansionType const &) = delete
```

<hr />

### `toStr` <a id="classopcua_1_1_expansion_type_1a34fa70ff71feda985dd570b7e25f2286" class="anchor"></a>

```cpp
inline static std::string toStr(ExpansionType_t const type)
```

<hr />

# struct `O1HeapDiagnostics` <a id="struct_o1_heap_diagnostics" class="anchor"></a>

Runtime diagnostic information. This information can be used to facilitate runtime self-testing, as required by certain safety-critical development guidelines. If assertion checks are not disabled, the library will perform automatic runtime self-diagnostics that trigger an assertion failure if a heap corruption is detected. Health checks and validation can be done with o1heapDoInvariantsHold().

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`capacity`](#struct_o1_heap_diagnostics_1ad43d9507a941522c830a9695b4c72ebe) | The total amount of memory available for serving allocation requests (heap size). The maximum allocation size is (capacity - O1HEAP_ALIGNMENT). This parameter does not include the overhead used up by O1HeapInstance and arena alignment. This parameter is constant. |
| [`allocated`](#struct_o1_heap_diagnostics_1a26088df3cfdc97fdb7cb9aa270eb4f01) | The amount of memory that is currently allocated, including the per-fragment overhead and size alignment. For example, if the application requested a fragment of size 1 byte, the value reported here may be 32 bytes. |
| [`peak_allocated`](#struct_o1_heap_diagnostics_1a2dfd925e33942d0d87dbcd1c27ab74e2) | The maximum value of 'allocated' seen since initialization. This parameter is never decreased. |
| [`peak_request_size`](#struct_o1_heap_diagnostics_1a08dc28803ca2732f21f273bc8c563916) | The largest amount of memory that the allocator has attempted to allocate (perhaps unsuccessfully) since initialization (not including the rounding and the allocator's own per-fragment overhead, so the total is larger). This parameter is never decreased. The initial value is zero. |
| [`oom_count`](#struct_o1_heap_diagnostics_1aef5b37fb6497cc3fbdffc08fa6cac88e) | The number of times an allocation request could not be completed due to the lack of memory or excessive fragmentation. OOM stands for "out of memory". This parameter is never decreased. |

## Members

### `capacity` <a id="struct_o1_heap_diagnostics_1ad43d9507a941522c830a9695b4c72ebe" class="anchor"></a>

```cpp
size_t capacity
```

The total amount of memory available for serving allocation requests (heap size). The maximum allocation size is (capacity - O1HEAP_ALIGNMENT). This parameter does not include the overhead used up by O1HeapInstance and arena alignment. This parameter is constant.
<hr />

### `allocated` <a id="struct_o1_heap_diagnostics_1a26088df3cfdc97fdb7cb9aa270eb4f01" class="anchor"></a>

```cpp
size_t allocated
```

The amount of memory that is currently allocated, including the per-fragment overhead and size alignment. For example, if the application requested a fragment of size 1 byte, the value reported here may be 32 bytes.
<hr />

### `peak_allocated` <a id="struct_o1_heap_diagnostics_1a2dfd925e33942d0d87dbcd1c27ab74e2" class="anchor"></a>

```cpp
size_t peak_allocated
```

The maximum value of 'allocated' seen since initialization. This parameter is never decreased.

<hr />

### `peak_request_size` <a id="struct_o1_heap_diagnostics_1a08dc28803ca2732f21f273bc8c563916" class="anchor"></a>

```cpp
size_t peak_request_size
```

The largest amount of memory that the allocator has attempted to allocate (perhaps unsuccessfully) since initialization (not including the rounding and the allocator's own per-fragment overhead, so the total is larger). This parameter is never decreased. The initial value is zero.
<hr />

### `oom_count` <a id="struct_o1_heap_diagnostics_1aef5b37fb6497cc3fbdffc08fa6cac88e" class="anchor"></a>

```cpp
uint64_t oom_count
```

The number of times an allocation request could not be completed due to the lack of memory or excessive fragmentation. OOM stands for "out of memory". This parameter is never decreased.
<hr />

