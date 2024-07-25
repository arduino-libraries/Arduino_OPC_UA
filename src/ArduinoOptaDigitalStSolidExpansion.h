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

#include "open62541.h"

#include <memory>

#include "RelayManager.h"
#include "AnalogInputManager.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class ArduinoOptaDigitalStSolidExpansion
{
public:
  typedef std::shared_ptr<ArduinoOptaDigitalStSolidExpansion> SharedPtr;

  static SharedPtr create(UA_Server * server, UA_NodeId const parent_node_id, uint8_t const exp_num);

  ArduinoOptaDigitalStSolidExpansion(UA_Server * server, UA_NodeId const & node_id)
    : _server{server}
    , _node_id{node_id}
  { }


  AnalogInputManager::SharedPtr  analog_input_mgr();
  RelayManager::SharedPtr        relay_mgr();


private:
  UA_Server * _server;
  UA_NodeId const _node_id;

  AnalogInputManager::SharedPtr _analog_input_mgr;
  RelayManager::SharedPtr _relay_mgr;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
