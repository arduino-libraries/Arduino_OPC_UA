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
`class ` [`opcua::AnalogOutput`](#classopcua_1_1_analog_output) | 
`class ` [`opcua::AnalogOutputManager`](#classopcua_1_1_analog_output_manager) | 
`class ` [`opcua::UserButton`](#classopcua_1_1_user_button) | 
`class ` [`opcua::DigitalInput`](#classopcua_1_1_digital_input) | 
`class ` [`opcua::DigitalInputManager`](#classopcua_1_1_digital_input_manager) | 
`class ` [`opcua::Led`](#classopcua_1_1_led) | 
`class ` [`opcua::LedManager`](#classopcua_1_1_led_manager) | 
`class ` [`opcua::PwmOutput`](#classopcua_1_1_pwm_output) | 
`class ` [`opcua::PwmOutputManager`](#classopcua_1_1_pwm_output_manager) | 
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
| [`AnalogExpansion`](#classopcua_1_1_analog_expansion_1a8922c1b320139757c7200ec568d25324) |  |
| [`~AnalogExpansion`](#classopcua_1_1_analog_expansion_1ad9a18c730a6451d543e48a91bf7eeff1) |  |
| [`toSKUString`](#classopcua_1_1_analog_expansion_1a37b9a4657d1e8c0cf2e1d0322adfa27c) |  |
| [`add_analog_input`](#classopcua_1_1_analog_expansion_1a511ae8067b88c476c5a7e47acccede15) |  |
| [`add_analog_output`](#classopcua_1_1_analog_expansion_1aa5ba819a44dfd2f8b651741499ffa5a0) |  |
| [`add_pwm_output`](#classopcua_1_1_analog_expansion_1a3a0997c332767761b4d96cac2e9f0963) |  |
| [`add_led_output`](#classopcua_1_1_analog_expansion_1a748779b79841cfa4329e318450be9be9) |  |
| [`SharedPtr`](#classopcua_1_1_analog_expansion_1a3a99cadc0594891e0ce7ee9acc06d1f3) |  |
| [`create`](#classopcua_1_1_analog_expansion_1a13a953b2d732d52f0c6772957b45abe8) |  |

## Members

### `AnalogExpansion` <a id="classopcua_1_1_analog_expansion_1a8922c1b320139757c7200ec568d25324" class="anchor"></a>

```cpp
AnalogExpansion(UA_Server * server, UA_NodeId const parent_node_id, char * display_name, char * node_name)
```

<hr />

### `~AnalogExpansion` <a id="classopcua_1_1_analog_expansion_1ad9a18c730a6451d543e48a91bf7eeff1" class="anchor"></a>

```cpp
virtual ~AnalogExpansion() = default
```

<hr />

### `toSKUString` <a id="classopcua_1_1_analog_expansion_1a37b9a4657d1e8c0cf2e1d0322adfa27c" class="anchor"></a>

```cpp
inline virtual std::string toSKUString() const
```

<hr />

### `add_analog_input` <a id="classopcua_1_1_analog_expansion_1a511ae8067b88c476c5a7e47acccede15" class="anchor"></a>

```cpp
void add_analog_input(UA_Server * server, const char * display_name, AnalogInput::OnReadRequestFunc const on_read_request_func)
```

<hr />

### `add_analog_output` <a id="classopcua_1_1_analog_expansion_1aa5ba819a44dfd2f8b651741499ffa5a0" class="anchor"></a>

```cpp
void add_analog_output(UA_Server * server, const char * display_name, AnalogOutput::OnReadRequestFunc const on_read_request, AnalogOutput::OnWriteRequestFunc const on_write_request_func)
```

<hr />

### `add_pwm_output` <a id="classopcua_1_1_analog_expansion_1a3a0997c332767761b4d96cac2e9f0963" class="anchor"></a>

```cpp
void add_pwm_output(UA_Server * server, const char * display_name, PwmOutput::SetPwmFunc const set_pwm_func, PwmOutput::GetPwmPeriodFunc const get_pwm_period_func, PwmOutput::GetPwmPulseWidthFunc const get_pwm_pulse_width_func)
```

<hr />

### `add_led_output` <a id="classopcua_1_1_analog_expansion_1a748779b79841cfa4329e318450be9be9" class="anchor"></a>

```cpp
void add_led_output(UA_Server * server, const char * display_name, Led::OnSetLedStateFunc const on_set_led_state)
```

<hr />

### `SharedPtr` <a id="classopcua_1_1_analog_expansion_1a3a99cadc0594891e0ce7ee9acc06d1f3" class="anchor"></a>

```cpp
typedef SharedPtr
```

<hr />

### `create` <a id="classopcua_1_1_analog_expansion_1a13a953b2d732d52f0c6772957b45abe8" class="anchor"></a>

```cpp
static SharedPtr create(UA_Server * server, UA_NodeId const parent_node_id, uint8_t const exp_num)
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
| [`~DigitalExpansion`](#classopcua_1_1_digital_expansion_1ab446f1129440aa88fe7d3fd133fc8bb1) |  |
| [`add_analog_input`](#classopcua_1_1_digital_expansion_1a49daa5502a89ab1656a3027529a651cf) |  |
| [`add_digital_input`](#classopcua_1_1_digital_expansion_1a7c5c6f636eb49335d5554e2be81d6b76) |  |
| [`add_relay_output`](#classopcua_1_1_digital_expansion_1a1ec45c5da3b0d3427a63a9cd30f775d0) |  |
| [`SharedPtr`](#classopcua_1_1_digital_expansion_1a808388135d0335260aed3725a4ca8eb9) |  |

## Members

### `DigitalExpansion` <a id="classopcua_1_1_digital_expansion_1a83aace406ca80bde86e563dcf4ea12fe" class="anchor"></a>

```cpp
DigitalExpansion(UA_Server * server, UA_NodeId const parent_node_id, char * display_name, char * node_name, char * model_name)
```

<hr />

### `~DigitalExpansion` <a id="classopcua_1_1_digital_expansion_1ab446f1129440aa88fe7d3fd133fc8bb1" class="anchor"></a>

```cpp
virtual ~DigitalExpansion() = default
```

<hr />

### `add_analog_input` <a id="classopcua_1_1_digital_expansion_1a49daa5502a89ab1656a3027529a651cf" class="anchor"></a>

```cpp
void add_analog_input(UA_Server * server, const char * display_name, AnalogInput::OnReadRequestFunc const on_read_request_func)
```

<hr />

### `add_digital_input` <a id="classopcua_1_1_digital_expansion_1a7c5c6f636eb49335d5554e2be81d6b76" class="anchor"></a>

```cpp
void add_digital_input(UA_Server * server, const char * display_name, DigitalInput::OnReadRequestFunc const on_read_request_func)
```

<hr />

### `add_relay_output` <a id="classopcua_1_1_digital_expansion_1a1ec45c5da3b0d3427a63a9cd30f775d0" class="anchor"></a>

```cpp
void add_relay_output(UA_Server * server, const char * display_name, Relay::OnSetRelayStateFunc const on_set_relay_state)
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
| [`DigitalMechExpansion`](#classopcua_1_1_digital_mech_expansion_1ad7349ea0108d988330c6b2623ef99696) |  |
| [`~DigitalMechExpansion`](#classopcua_1_1_digital_mech_expansion_1a10367a637954294193c4391c7507a8bc) |  |
| [`toSKUString`](#classopcua_1_1_digital_mech_expansion_1a5d81cd280f0ab93fd5380d070c3d48b6) |  |
| [`SharedPtr`](#classopcua_1_1_digital_mech_expansion_1abc60f0e66b8f12e051497c58b113a16e) |  |
| [`create`](#classopcua_1_1_digital_mech_expansion_1af777877670455dbd9032ca0aa47fcee3) |  |

## Members

### `DigitalMechExpansion` <a id="classopcua_1_1_digital_mech_expansion_1ad7349ea0108d988330c6b2623ef99696" class="anchor"></a>

```cpp
inline DigitalMechExpansion(UA_Server * server, UA_NodeId const parent_node_id, char * display_name, char * node_name)
```

<hr />

### `~DigitalMechExpansion` <a id="classopcua_1_1_digital_mech_expansion_1a10367a637954294193c4391c7507a8bc" class="anchor"></a>

```cpp
virtual ~DigitalMechExpansion() = default
```

<hr />

### `toSKUString` <a id="classopcua_1_1_digital_mech_expansion_1a5d81cd280f0ab93fd5380d070c3d48b6" class="anchor"></a>

```cpp
inline virtual std::string toSKUString() const
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
| [`DigitalStSolidExpansion`](#classopcua_1_1_digital_st_solid_expansion_1a896bf61b18c63b055343d0b5f408dbb0) |  |
| [`~DigitalStSolidExpansion`](#classopcua_1_1_digital_st_solid_expansion_1afb8021cf2b6041d723c2a3c1888ed5f7) |  |
| [`toSKUString`](#classopcua_1_1_digital_st_solid_expansion_1a67cb3b12dfc74b9747257daf1c481d99) |  |
| [`SharedPtr`](#classopcua_1_1_digital_st_solid_expansion_1a8bb44b6e51c634b1910dafb066f4e448) |  |
| [`create`](#classopcua_1_1_digital_st_solid_expansion_1a6b94afd184c4d435cea8ad32297fc045) |  |

## Members

### `DigitalStSolidExpansion` <a id="classopcua_1_1_digital_st_solid_expansion_1a896bf61b18c63b055343d0b5f408dbb0" class="anchor"></a>

```cpp
inline DigitalStSolidExpansion(UA_Server * server, UA_NodeId const parent_node_id, char * display_name, char * node_name)
```

<hr />

### `~DigitalStSolidExpansion` <a id="classopcua_1_1_digital_st_solid_expansion_1afb8021cf2b6041d723c2a3c1888ed5f7" class="anchor"></a>

```cpp
virtual ~DigitalStSolidExpansion() = default
```

<hr />

### `toSKUString` <a id="classopcua_1_1_digital_st_solid_expansion_1a67cb3b12dfc74b9747257daf1c481d99" class="anchor"></a>

```cpp
inline virtual std::string toSKUString() const
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
| [`~Expansion`](#classopcua_1_1_expansion_1a10a1451bd459c4375e7dcc0c1ffabed7) |  |
| [`toSKUString`](#classopcua_1_1_expansion_1ac2087b6c0d2153a8fd760fe5c7e689df) |  |
| [`SharedPtr`](#classopcua_1_1_expansion_1a0e496feb6cd2259a2a9f4cded8f9076a) |  |

## Members

### `Expansion` <a id="classopcua_1_1_expansion_1a52b0201d688fe43ddf8e662ce4a2ec32" class="anchor"></a>

```cpp
Expansion(UA_Server * server, UA_NodeId const parent_node_id, char * display_name, char * node_name, char * model_name)
```

<hr />

### `~Expansion` <a id="classopcua_1_1_expansion_1a10a1451bd459c4375e7dcc0c1ffabed7" class="anchor"></a>

```cpp
virtual ~Expansion() = default
```

<hr />

### `toSKUString` <a id="classopcua_1_1_expansion_1ac2087b6c0d2153a8fd760fe5c7e689df" class="anchor"></a>

```cpp
std::string toSKUString() const
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

# class `opcua::AnalogOutput` <a id="classopcua_1_1_analog_output" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`AnalogOutput`](#classopcua_1_1_analog_output_1a16ac9355b42c1d58d132babc5a207d2e) |  |
| [`onReadRequest`](#classopcua_1_1_analog_output_1a277345f3fe918b57f3c9e10e80a6b29b) |  |
| [`onWriteRequest`](#classopcua_1_1_analog_output_1a072e18e88dd85d16e949434951c9942c) |  |
| [`SharedPtr`](#classopcua_1_1_analog_output_1aa104e63edd1f282690fb7853ac24f3dd) |  |
| [`OnReadRequestFunc`](#classopcua_1_1_analog_output_1a4763f65ceb33a44a12e1a24fb48a2e37) |  |
| [`OnWriteRequestFunc`](#classopcua_1_1_analog_output_1a607044dc4f4a50e50f68a343c6bb4d1f) |  |
| [`create`](#classopcua_1_1_analog_output_1a16351e621798694bb3e09bd84eaf5571) |  |

## Members

### `AnalogOutput` <a id="classopcua_1_1_analog_output_1a16ac9355b42c1d58d132babc5a207d2e" class="anchor"></a>

```cpp
AnalogOutput(UA_NodeId const & node_id, OnReadRequestFunc const on_read_request, OnWriteRequestFunc const on_write_request)
```

<hr />

### `onReadRequest` <a id="classopcua_1_1_analog_output_1a277345f3fe918b57f3c9e10e80a6b29b" class="anchor"></a>

```cpp
void onReadRequest(UA_Server * server, UA_NodeId const * node_id)
```

<hr />

### `onWriteRequest` <a id="classopcua_1_1_analog_output_1a072e18e88dd85d16e949434951c9942c" class="anchor"></a>

```cpp
void onWriteRequest(UA_Server * server, UA_NodeId const * node_id, float const voltage)
```

<hr />

### `SharedPtr` <a id="classopcua_1_1_analog_output_1aa104e63edd1f282690fb7853ac24f3dd" class="anchor"></a>

```cpp
typedef SharedPtr
```

<hr />

### `OnReadRequestFunc` <a id="classopcua_1_1_analog_output_1a4763f65ceb33a44a12e1a24fb48a2e37" class="anchor"></a>

```cpp
typedef OnReadRequestFunc
```

<hr />

### `OnWriteRequestFunc` <a id="classopcua_1_1_analog_output_1a607044dc4f4a50e50f68a343c6bb4d1f" class="anchor"></a>

```cpp
typedef OnWriteRequestFunc
```

<hr />

### `create` <a id="classopcua_1_1_analog_output_1a16351e621798694bb3e09bd84eaf5571" class="anchor"></a>

```cpp
static SharedPtr create(UA_Server * server, UA_NodeId const & parent_node_id, const char * display_name, OnReadRequestFunc const on_read_request, OnWriteRequestFunc const on_write_request)
```

<hr />

# class `opcua::AnalogOutputManager` <a id="classopcua_1_1_analog_output_manager" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`AnalogOutputManager`](#classopcua_1_1_analog_output_manager_1af41a1bda2ad81560a6e9d4c005df0cff) |  |
| [`add_analog_output`](#classopcua_1_1_analog_output_manager_1afd370d4f4c0a3f7fb6df761f0254d7bb) |  |
| [`SharedPtr`](#classopcua_1_1_analog_output_manager_1a019101cbb84c3458e510153db559be63) |  |
| [`create`](#classopcua_1_1_analog_output_manager_1ae70361c7213c9ddb274b607eb0dda289) |  |

## Members

### `AnalogOutputManager` <a id="classopcua_1_1_analog_output_manager_1af41a1bda2ad81560a6e9d4c005df0cff" class="anchor"></a>

```cpp
AnalogOutputManager(UA_NodeId const & node_id)
```

<hr />

### `add_analog_output` <a id="classopcua_1_1_analog_output_manager_1afd370d4f4c0a3f7fb6df761f0254d7bb" class="anchor"></a>

```cpp
void add_analog_output(UA_Server * server, const char * display_name, AnalogOutput::OnReadRequestFunc const on_read_request, AnalogOutput::OnWriteRequestFunc const on_write_request_func)
```

<hr />

### `SharedPtr` <a id="classopcua_1_1_analog_output_manager_1a019101cbb84c3458e510153db559be63" class="anchor"></a>

```cpp
typedef SharedPtr
```

<hr />

### `create` <a id="classopcua_1_1_analog_output_manager_1ae70361c7213c9ddb274b607eb0dda289" class="anchor"></a>

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

# class `opcua::PwmOutput` <a id="classopcua_1_1_pwm_output" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`PwmOutput`](#classopcua_1_1_pwm_output_1afb7531394d5f6949a1139efc8eb4a2d4) |  |
| [`onReadRequestPwmPeriod`](#classopcua_1_1_pwm_output_1a996ade007bc33c1755cb7a58556d1b72) |  |
| [`onWriteRequestPwmPeriod`](#classopcua_1_1_pwm_output_1ab3361d34f09f0d478253c3eaeaa5d0b8) |  |
| [`onReadRequestPwmPulseWidth`](#classopcua_1_1_pwm_output_1ad94b10965197e6e34421e01826851e5b) |  |
| [`onWriteRequestPwmPulseWidth`](#classopcua_1_1_pwm_output_1a590f6ca875c9858102436e5f3316748d) |  |
| [`SharedPtr`](#classopcua_1_1_pwm_output_1ad871619fdeeccd340fad668e1d59c668) |  |
| [`SetPwmFunc`](#classopcua_1_1_pwm_output_1a979bc7c17dbac4dfb518a65dd92c1c56) |  |
| [`GetPwmPeriodFunc`](#classopcua_1_1_pwm_output_1ae9f4bd8023add25dda7eb038745e494c) |  |
| [`GetPwmPulseWidthFunc`](#classopcua_1_1_pwm_output_1ad9ca89b1b476fac49dd9d32306b819af) |  |
| [`create`](#classopcua_1_1_pwm_output_1a595c247e837f0e9a34e11b2b7b5a26ff) |  |

## Members

### `PwmOutput` <a id="classopcua_1_1_pwm_output_1afb7531394d5f6949a1139efc8eb4a2d4" class="anchor"></a>

```cpp
PwmOutput(UA_NodeId const & pwm_period_node_id, UA_NodeId const & pwm_pulse_width_node_id, SetPwmFunc const set_pwm_func, GetPwmPeriodFunc const get_pwm_period_func, GetPwmPulseWidthFunc const get_pwm_pulse_width_func)
```

<hr />

### `onReadRequestPwmPeriod` <a id="classopcua_1_1_pwm_output_1a996ade007bc33c1755cb7a58556d1b72" class="anchor"></a>

```cpp
void onReadRequestPwmPeriod(UA_Server * server, UA_NodeId const * node_id)
```

<hr />

### `onWriteRequestPwmPeriod` <a id="classopcua_1_1_pwm_output_1ab3361d34f09f0d478253c3eaeaa5d0b8" class="anchor"></a>

```cpp
void onWriteRequestPwmPeriod(UA_Server * server, UA_NodeId const * pwm_period_node_id, uint32_t const pwm_period_us)
```

<hr />

### `onReadRequestPwmPulseWidth` <a id="classopcua_1_1_pwm_output_1ad94b10965197e6e34421e01826851e5b" class="anchor"></a>

```cpp
void onReadRequestPwmPulseWidth(UA_Server * server, UA_NodeId const * node_id)
```

<hr />

### `onWriteRequestPwmPulseWidth` <a id="classopcua_1_1_pwm_output_1a590f6ca875c9858102436e5f3316748d" class="anchor"></a>

```cpp
void onWriteRequestPwmPulseWidth(UA_Server * server, UA_NodeId const * node_id, uint32_t const pwm_pulse_width_us)
```

<hr />

### `SharedPtr` <a id="classopcua_1_1_pwm_output_1ad871619fdeeccd340fad668e1d59c668" class="anchor"></a>

```cpp
typedef SharedPtr
```

<hr />

### `SetPwmFunc` <a id="classopcua_1_1_pwm_output_1a979bc7c17dbac4dfb518a65dd92c1c56" class="anchor"></a>

```cpp
typedef SetPwmFunc
```

<hr />

### `GetPwmPeriodFunc` <a id="classopcua_1_1_pwm_output_1ae9f4bd8023add25dda7eb038745e494c" class="anchor"></a>

```cpp
typedef GetPwmPeriodFunc
```

<hr />

### `GetPwmPulseWidthFunc` <a id="classopcua_1_1_pwm_output_1ad9ca89b1b476fac49dd9d32306b819af" class="anchor"></a>

```cpp
typedef GetPwmPulseWidthFunc
```

<hr />

### `create` <a id="classopcua_1_1_pwm_output_1a595c247e837f0e9a34e11b2b7b5a26ff" class="anchor"></a>

```cpp
static SharedPtr create(UA_Server * server, UA_NodeId const & parent_node_id, const char * display_name, SetPwmFunc const set_pwm_func, GetPwmPeriodFunc const get_pwm_period_func, GetPwmPulseWidthFunc const get_pwm_pulse_width_func)
```

<hr />

# class `opcua::PwmOutputManager` <a id="classopcua_1_1_pwm_output_manager" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`PwmOutputManager`](#classopcua_1_1_pwm_output_manager_1ae682f02d81ae9cdd8234e670e5140380) |  |
| [`add_pwm_output`](#classopcua_1_1_pwm_output_manager_1aaad206b4639e87595bf60f9154a9e0a4) |  |
| [`SharedPtr`](#classopcua_1_1_pwm_output_manager_1ae595b9016fec91f1e5caa1a74df4bcd5) |  |
| [`create`](#classopcua_1_1_pwm_output_manager_1a032bb88f9e5a54a6d68adc37a685374c) |  |

## Members

### `PwmOutputManager` <a id="classopcua_1_1_pwm_output_manager_1ae682f02d81ae9cdd8234e670e5140380" class="anchor"></a>

```cpp
PwmOutputManager(UA_NodeId const & node_id)
```

<hr />

### `add_pwm_output` <a id="classopcua_1_1_pwm_output_manager_1aaad206b4639e87595bf60f9154a9e0a4" class="anchor"></a>

```cpp
void add_pwm_output(UA_Server * server, const char * display_name, PwmOutput::SetPwmFunc const set_pwm_func, PwmOutput::GetPwmPeriodFunc const get_pwm_period_func, PwmOutput::GetPwmPulseWidthFunc const get_pwm_pulse_width_func)
```

<hr />

### `SharedPtr` <a id="classopcua_1_1_pwm_output_manager_1ae595b9016fec91f1e5caa1a74df4bcd5" class="anchor"></a>

```cpp
typedef SharedPtr
```

<hr />

### `create` <a id="classopcua_1_1_pwm_output_manager_1a032bb88f9e5a54a6d68adc37a685374c" class="anchor"></a>

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
| [`Opta`](#classopcua_1_1_opta_1a283e8bca4e4044cce2e85d86bb95cd55) |  |
| [`add_analog_input`](#classopcua_1_1_opta_1a6caea0f035f0831d6a57dc3e5f972dcf) |  |
| [`add_digital_input`](#classopcua_1_1_opta_1a844b182bb773dd05310b8f92cdcb8428) |  |
| [`add_relay_output`](#classopcua_1_1_opta_1ae015db2b74d47771632648d97508bc9c) |  |
| [`add_led_output`](#classopcua_1_1_opta_1a0ca04bd872b6c67fc8e0a01ec7b60773) |  |
| [`SharedPtr`](#classopcua_1_1_opta_1a75b2e05ac5b273859709490686dfa165) |  |
| [`create`](#classopcua_1_1_opta_1a01f8da6cd187c6237c903dc6d004828a) |  |

## Members

### `Opta` <a id="classopcua_1_1_opta_1a283e8bca4e4044cce2e85d86bb95cd55" class="anchor"></a>

```cpp
Opta(UA_Server * server, UA_NodeId const & node_id, OptaVariant::Type const opta_type)
```

<hr />

### `add_analog_input` <a id="classopcua_1_1_opta_1a6caea0f035f0831d6a57dc3e5f972dcf" class="anchor"></a>

```cpp
void add_analog_input(UA_Server * server, const char * display_name, AnalogInput::OnReadRequestFunc const on_read_request_func)
```

<hr />

### `add_digital_input` <a id="classopcua_1_1_opta_1a844b182bb773dd05310b8f92cdcb8428" class="anchor"></a>

```cpp
void add_digital_input(UA_Server * server, const char * display_name, DigitalInput::OnReadRequestFunc const on_read_request_func)
```

<hr />

### `add_relay_output` <a id="classopcua_1_1_opta_1ae015db2b74d47771632648d97508bc9c" class="anchor"></a>

```cpp
void add_relay_output(UA_Server * server, const char * display_name, Relay::OnSetRelayStateFunc const on_set_relay_state)
```

<hr />

### `add_led_output` <a id="classopcua_1_1_opta_1a0ca04bd872b6c67fc8e0a01ec7b60773" class="anchor"></a>

```cpp
void add_led_output(UA_Server * server, const char * display_name, Led::OnSetLedStateFunc const on_set_led_state)
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

