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

#include <list>
#include <memory>

#include "PwmOutput.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

/**
 * @class PwmOutputManager
 * @brief Provides methods for creating and storing PwmOutput objects in a collection.
 *
 * This class creates an OPC UA object node which is representing all PWM
 * outputs of a given OPC UA devices. PWM outputs can be created and added
 * to the OPC UA object node using this class.
 */
class PwmOutputManager
{
public:
  /**
   * SharedPtr is std::shared_ptr of an PwmOutputManager class.
   */
  typedef std::shared_ptr<PwmOutputManager> SharedPtr;


  /**
   * Creates a new instance of the opcua::PwmOutputManager class, creating an OPC UA object node abstraction in the process.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param parent_node_id OPC UA node id of parent object in OPC UA tree.
   * @return std::shared_ptr holding the newly allocated instance of opcua::PwmOutputManager.
   */
  static SharedPtr
  create(
    UA_Server * server,
    UA_NodeId const parent_node_id);


  /**
   * Constructor of the opcua::PwmOutputManager class.
   * Note: Objects should not be instantiated directly, but by using PwmOutputManager::create.
   * @param node_id OPC UA node id of the object node representing all PWM outputs.
   */
  PwmOutputManager(
    UA_NodeId const & node_id);


  /**
   * This function creates a new opcua::PwmOutput and adds it to the opcua::PwmOutputManager.
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


private:
  UA_NodeId _node_id;
  std::list<PwmOutput::SharedPtr> _pwm_output_list;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
