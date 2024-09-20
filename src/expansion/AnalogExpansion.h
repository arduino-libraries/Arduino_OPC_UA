/*
 * Copyright (c) 2024 Arduino
 *
 * SPDX-License-Identifier: MPL-2.0
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include "Expansion.h"

#include <memory>

#include "../io/led/LedManager.h"
#include "../io/pwm/PwmOutputManager.h"
#include "../io/analog/AnalogInputManager.h"
#include "../io/analog/AnalogOutputManager.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

/**
 * @class AnalogExpansion
 * @brief Provides an OPC UA object node abstraction for an Analog Expansion board.
 *
 * This class creates an OPC UA object node which is representing an Arduino Opta
 * Analog Expansion board. Furthermore, this class provides methods for adding
 * OPC UA exposure to all IO entities supported by the Analog Expansion board.
 */
class AnalogExpansion : public Expansion
{
public:
  /**
   * SharedPtr is std::shared_ptr of an AnalogExpansion class.
   */
  typedef std::shared_ptr<AnalogExpansion> SharedPtr;


  /**
   * Creates a new instance of the opcua::AnalogExpansion class, creating an OPC UA object node abstraction in the process.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param parent_node_id OPC UA node id of parent object in OPC UA tree.
   * @param exp_num A numerical identifier provided by the Arduino_Opta_Blueprint library and identifying the number of the expansion module in the daisy-chain of expansion modules, i.e. exp_num = 2 refers to the second connect expansion module.
   * @return std::shared_ptr holding the newly allocated instance of opcua::AnalogExpansion.
   */
  static SharedPtr
  create(
    UA_Server *server,
    UA_NodeId const parent_node_id,
    uint8_t const exp_num);


  /**
   * Constructor of the opcua::AnalogExpansion class.
   * Note: Objects should not be instantiated directly, but by using AnalogExpansion::create.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param parent_node_id OPC UA node id of parent object in OPC UA tree.
   * @param display_name Character string providing an easy identifiable name for the object node representing an analog expansion board, i.e. "Arduino Opta Expansion 1: Analog".
   * @param node_name The unique node name identifying the Analog Expansion Board object node within the OPC UA tree.
   */
  AnalogExpansion(
    UA_Server * server,
    UA_NodeId const parent_node_id,
    char * display_name,
    char * node_name);
  /**
   * Destructor of the opcua::AnalogExpansion class.
   */
  virtual ~AnalogExpansion() = default;


  /**
   * Returns the SKU number of the Analog Expansion board as std::string.
   * @return SKU number of Analog Expansion board
   */
  virtual std::string
  toSKUString() const override final
  {
    return std::string("AFX00007");
  }


  /**
   * This function creates a new opcua::AnalogInput and adds it to the opcua::AnalogInputManager belonging to the opcua::AnalogExpansion class.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param display_name Character string providing an easy identifiable name for the variable node representing an analog input, i.e. "Analog Input I1".
   * @param on_read_request Function pointer which is called during a read-access on the variable node representing the analog input.
   */
  void
  addAnalogInput(
    UA_Server * server,
    const char * display_name,
    AnalogInput::OnReadRequestFunc const on_read_request);

  /**
   * This function creates a new opcua::AnalogOutput and adds it to the opcua::AnalogOutputManager belonging to the opcua::AnalogExpansion class.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param display_name Character string providing an easy identifiable name for the variable node representing an analog output, i.e. "Analog Output O1".
   * @param on_read_request Function pointer which is called during a read-access on the variable node representing the analog output.
   * @param on_write_request Function pointer which is called during a write-access on the variable node representing the analog output.
   */
  void
  addAnalogOutput(
    UA_Server * server,
    const char * display_name,
    AnalogOutput::OnReadRequestFunc const on_read_request,
    AnalogOutput::OnWriteRequestFunc const on_write_request);

  /**
   * This function creates a new opcua::PwmOutput and adds it to the opcua::PwmOutputManager belonging to the opcua::AnalogExpansion class.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param display_name Character string providing an easy identifiable name for the variable node representing an analog output, i.e. "PWM Output P1".
   * @param set_pwm_func Function pointer which is called during a write-access on the variable node representing the PWM output and used for setting the PWM period and pulse width.
   * @param get_pwm_period_func Function pointer which is called during a read-access on the variable node representing the PWM output's period.
   * @param get_pwm_pulse_width_func Function pointer which is called during a read-access on the variable node representing the PWM output's pulse width.
   */
  void
  addPwmOutput(
    UA_Server * server,
    const char * display_name,
    PwmOutput::SetPwmFunc const set_pwm_func,
    PwmOutput::GetPwmPeriodFunc const get_pwm_period_func,
    PwmOutput::GetPwmPulseWidthFunc const get_pwm_pulse_width_func);

  /**
   * This function creates a new opcua::LED and adds it to the opcua::LEDManager belonging to the opcua::AnalogExpansion class.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param display_name Character string providing an easy identifiable name for the variable node representing a LED, i.e. "LED1".
   * @param on_set_led_state Function pointer which is called during a write-access on the variable node representing the LED.
   */
  void
  addLedOutput(
    UA_Server * server,
    const char * display_name,
    Led::OnSetLedStateFunc const on_set_led_state);


private:
  AnalogInputManager::SharedPtr _analog_input_mgr;
  AnalogOutputManager::SharedPtr _analog_output_mgr;
  PwmOutputManager::SharedPtr _pwm_output_mgr;
  LedManager::SharedPtr _led_mgr;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
