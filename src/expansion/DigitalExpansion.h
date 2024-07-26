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

#include "../io/relay/RelayManager.h"
#include "../io/analog/AnalogInputManager.h"
#include "../io/digital/DigitalInputManager.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class DigitalExpansion : public Expansion
{
public:
  typedef std::shared_ptr<DigitalExpansion> SharedPtr;


  DigitalExpansion(UA_Server * server,
                   UA_NodeId const parent_node_id,
                   char * display_name,
                   char * node_name,
                   char * model_name)
  : Expansion(server, parent_node_id, display_name, node_name, model_name)
  { }


  AnalogInputManager::SharedPtr  analog_input_mgr();
  DigitalInputManager::SharedPtr digital_input_mgr();
  RelayManager::SharedPtr        relay_mgr();


private:
  AnalogInputManager::SharedPtr _analog_input_mgr;
  DigitalInputManager::SharedPtr _digital_input_mgr;
  RelayManager::SharedPtr _relay_mgr;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
