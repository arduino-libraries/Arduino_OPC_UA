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

class AnalogExpansion : public Expansion
{
public:
  typedef std::shared_ptr<AnalogExpansion> SharedPtr;


  static SharedPtr
  create(
    UA_Server *server,
    UA_NodeId const parent_node_id,
    uint8_t const exp_num);


  AnalogExpansion(
    UA_Server * server,
    UA_NodeId const parent_node_id,
    char * display_name,
    char * node_name);
  virtual ~AnalogExpansion() = default;


  virtual std::string
  toSKUString() const override final
  {
    return std::string("AFX00007");
  }

  void
  add_analog_input(
    UA_Server * server,
    const char * display_name,
    AnalogInput::OnReadRequestFunc const on_read_request_func);

  void
  add_analog_output(
    UA_Server * server,
    const char * display_name,
    AnalogOutput::OnReadRequestFunc const on_read_request,
    AnalogOutput::OnWriteRequestFunc const on_write_request_func);

  void
  add_pwm_output(
    UA_Server * server,
    const char * display_name,
    PwmOutput::SetPwmFunc const set_pwm_func,
    PwmOutput::GetPwmPeriodFunc const get_pwm_period_func,
    PwmOutput::GetPwmPulseWidthFunc const get_pwm_pulse_width_func);

  void
  add_led_output(
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
