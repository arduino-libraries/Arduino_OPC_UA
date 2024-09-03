/*
 * Copyright (c) 2024 Arduino
 *
 * SPDX-License-Identifier: MPL-2.0
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include "AnalogExpansion.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

AnalogExpansion::SharedPtr
AnalogExpansion::create(
  UA_Server *server,
  UA_NodeId const parent_node_id,
  uint8_t const exp_num)
{
  char display_name[64] = {0};
  snprintf(display_name, sizeof(display_name), "Arduino Opta Expansion %d: Analog", exp_num);

  char node_name[32] = {0};
  snprintf(node_name, sizeof(node_name), "AnaExp_%d", exp_num);

  char model_name[] = {"AFX00007"};

  auto const instance_ptr = std::make_shared<AnalogExpansion>(server, parent_node_id, display_name, node_name, model_name);
  return instance_ptr;
}

AnalogInputManager::SharedPtr
AnalogExpansion::analog_input_mgr()
{
  if (!_analog_input_mgr)
  {
    _analog_input_mgr = opcua::AnalogInputManager::create(_server, _node_id);
    if (!_analog_input_mgr)
      UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                   "%s: AnalogInputManager::create(...) failed.", __PRETTY_FUNCTION__);
  }

  return _analog_input_mgr;
}

AnalogOutputManager::SharedPtr
AnalogExpansion::analog_output_mgr()
{
  if (!_analog_output_mgr)
  {
    _analog_output_mgr = opcua::AnalogOutputManager::create(_server, _node_id);
    if (!_analog_output_mgr)
      UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: AnalogOutputManager::create(...) failed.", __PRETTY_FUNCTION__);
  }

  return _analog_output_mgr;
}

PwmOutputManager::SharedPtr
AnalogExpansion::pwm_output_mgr()
{
  if (!_pwm_output_mgr)
  {
    _pwm_output_mgr = opcua::PwmOutputManager::create(_server, _node_id);
    if (!_pwm_output_mgr)
      UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: PwmOutputManager::create(...) failed.", __PRETTY_FUNCTION__);
  }

  return _pwm_output_mgr;
}

LedManager::SharedPtr
AnalogExpansion::led_mgr()
{
  if (!_led_mgr)
  {
    _led_mgr = opcua::LedManager::create(_server, _node_id);
    if (!_led_mgr)
      UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                   "%s: LedManager::create(...) failed.", __PRETTY_FUNCTION__);
  }

  return _led_mgr;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
