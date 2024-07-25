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
#include "DigitalInputManager.h"
#include "UserButton.h"

#include "io/analog/AnalogInputManager.h"

#include "ArduinoOptaVariant.h"
#include "ArduinoOptaExpansionType.h"
#include "ArduinoOptaDigitalMechExpansion.h"
#include "ArduinoOptaDigitalStSolidExpansion.h"

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

  ArduinoOptaDigitalMechExpansion::SharedPtr create_digital_mechanical_expansion(uint8_t const exp_num);
  ArduinoOptaDigitalStSolidExpansion::SharedPtr create_digital_solid_state_expansion(uint8_t const exp_num);

private:
  UA_Server * _server;
  UA_NodeId _node_id;

  UserButton::SharedPtr _usr_button;
  AnalogInputManager::SharedPtr _analog_input_mgr;
  DigitalInputManager::SharedPtr _digital_input_mgr;
  RelayManager::SharedPtr _relay_mgr;
  LedManager::SharedPtr _led_mgr;

  std::list<ArduinoOptaDigitalMechExpansion::SharedPtr> _dig_mech_exp_list;
  std::list<ArduinoOptaDigitalStSolidExpansion::SharedPtr> _dig_solid_state_exp_list;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
