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

class PwmOutputManager
{
public:
  typedef std::shared_ptr<PwmOutputManager> SharedPtr;


  static SharedPtr
  create(
    UA_Server * server,
    UA_NodeId const parent_node_id);


  PwmOutputManager(UA_NodeId const & node_id);


  void
  add_pwm_output(
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
