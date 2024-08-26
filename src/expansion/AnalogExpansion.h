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
#include "../io/analog/AnalogInputManager.h"

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


  static SharedPtr create(UA_Server *server, UA_NodeId const parent_node_id, uint8_t const exp_num)
  {
    char display_name[64] = {0};
    snprintf(display_name, sizeof(display_name), "Arduino Opta Expansion %d: Analog", exp_num);

    char node_name[32] = {0};
    snprintf(node_name, sizeof(node_name), "AnaExp_%d", exp_num);

    char model_name[] = {"AFX00007"};

    auto const instance_ptr = std::make_shared<AnalogExpansion>(server, parent_node_id, display_name, node_name, model_name);
    return instance_ptr;
  }


  AnalogExpansion(UA_Server * server,
                   UA_NodeId const parent_node_id,
                   char * display_name,
                   char * node_name,
                   char * model_name)
    : Expansion(server, parent_node_id, display_name, node_name, model_name)
  { }


  AnalogInputManager::SharedPtr analog_input_mgr();
  LedManager::SharedPtr         led_mgr();



private:
  AnalogInputManager::SharedPtr _analog_input_mgr;
  LedManager::SharedPtr _led_mgr;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
