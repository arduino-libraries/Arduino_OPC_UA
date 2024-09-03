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

#include "DigitalExpansion.h"

#include <Arduino.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

AnalogInputManager::SharedPtr
DigitalExpansion::analog_input_mgr()
{
  if (!_analog_input_mgr)
  {
    _analog_input_mgr = opcua::AnalogInputManager::create(_server, _node_id);
    if (!_analog_input_mgr)
      UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: AnalogInputManager::create(...) failed.", __PRETTY_FUNCTION__);
  }

  return _analog_input_mgr;
}

DigitalInputManager::SharedPtr
DigitalExpansion::digital_input_mgr()
{
  if (!_digital_input_mgr)
  {
    _digital_input_mgr = opcua::DigitalInputManager::create(_server, _node_id);
    if (!_digital_input_mgr)
      UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: DigitalInputManager::create(...) failed.", __PRETTY_FUNCTION__);
  }

  return _digital_input_mgr;
}

RelayManager::SharedPtr
DigitalExpansion::relay_mgr()
{
  if (!_relay_mgr)
  {
    _relay_mgr = opcua::RelayManager::create(_server, _node_id);
    if (!_relay_mgr)
      UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: RelayManager::create(...) failed.", __PRETTY_FUNCTION__);
  }

  return _relay_mgr;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
