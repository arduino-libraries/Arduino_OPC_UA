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

class PwmOutput
{
public:
  typedef std::shared_ptr<PwmOutput> SharedPtr;
  typedef std::function<void(uint32_t const, uint32_t const)> SetPwmFunc;
  typedef std::function<uint32_t(void)> GetPwmPeriodFunc;
  typedef std::function<uint32_t(void)> GetPwmPulseWidthFunc;


  static SharedPtr
  create(
    UA_Server * server,
    UA_NodeId const & parent_node_id,
    const char * display_name,
    SetPwmFunc const set_pwm_func,
    GetPwmPeriodFunc const get_pwm_period_func,
    GetPwmPulseWidthFunc const get_pwm_pulse_width_func);


  PwmOutput(
    UA_NodeId const & pwm_period_node_id,
    UA_NodeId const & pwm_pulse_width_node_id,
    SetPwmFunc const set_pwm_func,
    GetPwmPeriodFunc const get_pwm_period_func,
    GetPwmPulseWidthFunc const get_pwm_pulse_width_func);


  void
  onReadRequestPwmPeriod(
    UA_Server * server,
    UA_NodeId const * node_id);

  void
  onWriteRequestPwmPeriod(
    UA_Server * server,
    UA_NodeId const * pwm_period_node_id,
    uint32_t const pwm_period_us);

  void
  onReadRequestPwmPulseWidth(
    UA_Server * server,
    UA_NodeId const * node_id);

  void
  onWriteRequestPwmPulseWidth(
    UA_Server * server,
    UA_NodeId const * node_id,
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
