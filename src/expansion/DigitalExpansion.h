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


  DigitalExpansion(
    UA_Server * server,
    UA_NodeId const parent_node_id,
    char * display_name,
    char * node_name,
    char * model_name);
  virtual ~DigitalExpansion() = default;

  void
  add_analog_input(
    UA_Server * server,
    const char * display_name,
    AnalogInput::OnReadRequestFunc const on_read_request_func);

  void
  add_digital_input(
    UA_Server * server,
    const char * display_name,
    DigitalInput::OnReadRequestFunc const on_read_request_func);

  void
  add_relay_output(
    UA_Server * server,
    const char * display_name,
    Relay::OnSetRelayStateFunc const on_set_relay_state);


private:
  AnalogInputManager::SharedPtr _analog_input_mgr;
  DigitalInputManager::SharedPtr _digital_input_mgr;
  RelayManager::SharedPtr _relay_mgr;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
