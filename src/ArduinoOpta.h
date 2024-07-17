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

#include "LedManager.h"
#include "RelayManager.h"
#include "AnalogInputManager.h"
#include "DigitalInputManager.h"
#include "UserButton.h"
#include "ArduinoOptaVariant.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class ArduinoOpta
{
public:
  typedef std::shared_ptr<ArduinoOpta> SharedPtr;

  static SharedPtr create(UA_Server * server, ArduinoOptaVariant::Type const opta_type);

  ArduinoOpta(UA_Server * server, UA_NodeId const & node_id);

  AnalogInputManager::SharedPtr  analog_input_mgr();
  DigitalInputManager::SharedPtr digital_input_mgr();
  RelayManager::SharedPtr        relay_mgr();
  LedManager::SharedPtr          led_mgr();

  [[nodiscard]] UA_NodeId node_id() const { return _node_id; }

private:
  UA_Server * _server;
  UA_NodeId _node_id;

  UserButton::SharedPtr _usr_button;
  AnalogInputManager::SharedPtr _analog_input_mgr;
  DigitalInputManager::SharedPtr _digital_input_mgr;
  RelayManager::SharedPtr _relay_mgr;
  LedManager::SharedPtr _led_mgr;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
