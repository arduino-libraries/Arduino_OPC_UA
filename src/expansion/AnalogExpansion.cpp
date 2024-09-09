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
 * CTOR/DTOR
 **************************************************************************************/

AnalogExpansion::AnalogExpansion(
  UA_Server * server,
  UA_NodeId const parent_node_id,
  char * display_name,
  char * node_name)
  : Expansion(server, parent_node_id, display_name, node_name, (char *)toSKUString().c_str())
  , _analog_input_mgr{opcua::AnalogInputManager::create(_server, _node_id)}
  , _analog_output_mgr{opcua::AnalogOutputManager::create(_server, _node_id)}
  , _pwm_output_mgr{opcua::PwmOutputManager::create(_server, _node_id)}
  , _led_mgr{opcua::LedManager::create(_server, _node_id)}
{
  if (!_analog_input_mgr)
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: AnalogInputManager::create(...) failed.", __PRETTY_FUNCTION__);
  if (!_analog_output_mgr)
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: AnalogOutputManager::create(...) failed.", __PRETTY_FUNCTION__);
  if (!_pwm_output_mgr)
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: PwmOutputManager::create(...) failed.", __PRETTY_FUNCTION__);
  if (!_led_mgr)
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: LedManager::create(...) failed.", __PRETTY_FUNCTION__);
}

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

  auto const instance_ptr = std::make_shared<AnalogExpansion>(server, parent_node_id, display_name, node_name);
  return instance_ptr;
}

void
AnalogExpansion::add_analog_input(
  UA_Server * server,
  const char * display_name,
  AnalogInput::OnReadRequestFunc const on_read_request)
{
  _analog_input_mgr->add_analog_input(server, display_name, on_read_request);
}

void
AnalogExpansion::add_analog_output(
  UA_Server * server,
  const char * display_name,
  AnalogOutput::OnReadRequestFunc const on_read_request,
  AnalogOutput::OnWriteRequestFunc const on_write_request)
{
  _analog_output_mgr->add_analog_output(server, display_name, on_read_request, on_write_request);
}

void
AnalogExpansion::add_pwm_output(
  UA_Server * server,
  const char * display_name,
  PwmOutput::SetPwmFunc const set_pwm_func,
  PwmOutput::GetPwmPeriodFunc const get_pwm_period_func,
  PwmOutput::GetPwmPulseWidthFunc const get_pwm_pulse_width_func)
{
  _pwm_output_mgr->add_pwm_output(server, display_name, set_pwm_func, get_pwm_period_func, get_pwm_pulse_width_func);
}

void
AnalogExpansion::add_led_output(
  UA_Server * server,
  const char * display_name,
  Led::OnSetLedStateFunc const on_set_led_state)
{
  _led_mgr->add_led_output(server, display_name, on_set_led_state);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
