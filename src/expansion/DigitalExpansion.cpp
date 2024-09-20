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
 * CTOR/DTOR
 **************************************************************************************/

DigitalExpansion::DigitalExpansion(
  UA_Server * server,
  UA_NodeId const parent_node_id,
  char * display_name,
  char * node_name,
  char * model_name)
  : Expansion(server, parent_node_id, display_name, node_name, model_name)
  , _analog_input_mgr{opcua::AnalogInputManager::create(_server, _node_id)}
  , _digital_input_mgr{opcua::DigitalInputManager::create(_server, _node_id)}
  , _relay_mgr{opcua::RelayManager::create(_server, _node_id)}
{
  if (!_analog_input_mgr)
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: AnalogInputManager::create(...) failed.", __PRETTY_FUNCTION__);
  if (!_digital_input_mgr)
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: DigitalInputManager::create(...) failed.", __PRETTY_FUNCTION__);
  if (!_relay_mgr)
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: RelayManager::create(...) failed.", __PRETTY_FUNCTION__);
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void
DigitalExpansion::addAnalogInput(
  UA_Server * server,
  const char * display_name,
  AnalogInput::OnReadRequestFunc const on_read_request)
{
  _analog_input_mgr->addAnalogInput(server, display_name, on_read_request);
}

void
DigitalExpansion::addDigitalInput(
  UA_Server * server,
  const char * display_name,
  DigitalInput::OnReadRequestFunc const on_read_request)
{
  _digital_input_mgr->addDigitalInput(server, display_name, on_read_request);
}

void
DigitalExpansion::addRelayOutput(
  UA_Server * server,
  const char * display_name,
  Relay::OnSetRelayStateFunc const on_set_relay_state)
{
  _relay_mgr->addRelayOutput(server, display_name, on_set_relay_state);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
