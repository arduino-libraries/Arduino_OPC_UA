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

#include "../../open62541.h"

#include <memory>
#include <functional>

#include <Arduino.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

/**
 * @class PwmOutput
 * @brief Provides an OPC UA variable node abstraction for a PWM output.
 *
 * This class creates an OPC UA object node representing a PWM output with two
 * OPC UA variable nodes representing the PWM output's period and pulse width.
 * When writing to any OPC UA variable node a callback is triggered which performs
 * the setting of the desired PWM period and pulse width. When reading from the
 * OPC UA variable nodes different callback are triggered which performs reading
 * back the actual PWM period and pulse width.
 */
class PwmOutput
{
public:
  /**
   * SharedPtr is std::shared_ptr of a PwmOutput class.
   */
  typedef std::shared_ptr<PwmOutput> SharedPtr;
  /**
   * SetPwmFunc is definition for a callback which is called
   * during a write-access on the variable nodes representing
   * PWM period and PWM pulse width subsequently configuring
   * the PWN output with the desired period and pulse width.
   */
  typedef std::function<void(uint32_t const, uint32_t const)> SetPwmFunc;
  /**
   * GetPwmPeriodFunc is definition for a callback which is called
   * during a read-access on the variable node representing the PWM
   * period and which is used to retrieve the actual PWM period.
   */
  typedef std::function<uint32_t(void)> GetPwmPeriodFunc;
  /**
   * GetPwmPulseWidthFunc is definition for a callback which is called
   * during a read-access on the variable node representing the PWM
   * pulse width and which is used to retrieve the actual PWM pulse width.
   */
  typedef std::function<uint32_t(void)> GetPwmPulseWidthFunc;


  /**
   * Creates a new instance of the opcua::PwmOutput class, creating an OPC UA variable node abstraction in the process.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param parent_node_id OPC UA node id of parent object in OPC UA tree.
   * @param display_name Character string providing an easy identifiable name for the variable node representing an analog output, i.e. "PWM Output P1".
   * @param set_pwm_func Function pointer which is called during a write-access on the variable node representing the PWM output and used for setting the PWM period and pulse width.
   * @param get_pwm_period_func Function pointer which is called during a read-access on the variable node representing the PWM output's period.
   * @param get_pwm_pulse_width_func Function pointer which is called during a read-access on the variable node representing the PWM output's pulse width.
   * @return std::shared_ptr holding the newly allocated instance of opcua::PwmOutput.
   */
  static SharedPtr
  create(
    UA_Server * server,
    UA_NodeId const & parent_node_id,
    const char * display_name,
    SetPwmFunc const set_pwm_func,
    GetPwmPeriodFunc const get_pwm_period_func,
    GetPwmPulseWidthFunc const get_pwm_pulse_width_func);


  /**
   * Constructor of the opcua::PwmOutput class.
   * Note: Objects should not be instantiated directly, but by using PwmOutput::create.
   * @param pwm_period_node_id OPC UA node id of the variable node representing the PWM output's period.
   * @param pwm_pulse_width_node_id OPC UA node id of the variable node representing the PWM output's pulse width.
   * @param set_pwm_func Function pointer which is called during a write-access on the variable node representing the PWM output and used for setting the PWM period and pulse width.
   * @param get_pwm_period_func Function pointer which is called during a read-access on the variable node representing the PWM output's period.
   * @param get_pwm_pulse_width_func Function pointer which is called during a read-access on the variable node representing the PWM output's pulse width.
   */
  PwmOutput(
    UA_NodeId const & pwm_period_node_id,
    UA_NodeId const & pwm_pulse_width_node_id,
    SetPwmFunc const set_pwm_func,
    GetPwmPeriodFunc const get_pwm_period_func,
    GetPwmPulseWidthFunc const get_pwm_pulse_width_func);


  /**
   * This function is called by the framework when a read-access on the variable node representing the PWM output's period is performed.
   * Note: This function should not be called directly, it will be invoked by the framework.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param node_id OPC UA node id of the variable node representing the PWM output's period.
   */
  void
  onReadRequestPwmPeriod(
    UA_Server * server,
    UA_NodeId const * node_id);

  /**
   * This function is called by the framework when a write-access on the variable node representing the PWM output's period is performed.
   * Note: This function should not be called directly, it will be invoked by the framework.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param pwm_period_node_id OPC UA node id of the variable node representing the PWM output's period.
   * @param pwm_period_us Desired PWM output period in microseconds.
   */
  void
  onWriteRequestPwmPeriod(
    UA_Server * server,
    UA_NodeId const * pwm_period_node_id,
    uint32_t const pwm_period_us);

  /**
   * This function is called by the framework when a read-access on the variable node representing the PWM output's pulse width is performed.
   * Note: This function should not be called directly, it will be invoked by the framework.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param node_id OPC UA node id of the variable node representing the PWM output's pulse width.
   */
  void
  onReadRequestPwmPulseWidth(
    UA_Server * server,
    UA_NodeId const * node_id);

  /**
   * This function is called by the framework when a write-access on the variable node representing the PWM output's pulse width is performed.
   * Note: This function should not be called directly, it will be invoked by the framework.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param pwm_pulse_width_node_id OPC UA node id of the variable node representing the PWM output's pulse width.
   * @param pwm_pulse_width_us Desired PWM output pulse width in microseconds.
   */
  void
  onWriteRequestPwmPulseWidth(
    UA_Server * server,
    UA_NodeId const * pwm_pulse_width_node_id,
    uint32_t const pwm_pulse_width_us);


private:
  UA_NodeId _pwm_period_node_id;
  UA_NodeId _pwm_pulse_width_node_id;
  SetPwmFunc const _set_pwm_func;
  GetPwmPeriodFunc const _get_pwm_period_func;
  GetPwmPulseWidthFunc const _get_pwm_pulse_width_func;
  uint32_t _pwm_period_us, _pwm_pulse_width_us;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
