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

AnalogInputManager::SharedPtr AnalogExpansion::analog_input_mgr()
{
  if (!_analog_input_mgr)
  {
    _analog_input_mgr = opcua::AnalogInputManager::create(_server, _node_id);
    if (!_analog_input_mgr)
      UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "AnalogExpansion::analog_input_mgr: AnalogInputManager::create(...) failed.");
  }

  return _analog_input_mgr;
}

AnalogOutputManager::SharedPtr AnalogExpansion::analog_output_mgr()
{
  if (!_analog_output_mgr)
  {
    _analog_output_mgr = opcua::AnalogOutputManager::create(_server, _node_id);
    if (!_analog_output_mgr)
      UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "AnalogExpansion::analog_output_mgr: AnalogOutputManager::create(...) failed.");
  }

  return _analog_output_mgr;
}

LedManager::SharedPtr AnalogExpansion::led_mgr()
{
  if (!_led_mgr)
  {
    _led_mgr = opcua::LedManager::create(_server, _node_id);
    if (!_led_mgr)
      UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "AnalogExpansion::led_mgr: LedManager::create(...) failed.");
  }

  return _led_mgr;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
