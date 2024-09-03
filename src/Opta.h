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

#include "io/led/LedManager.h"
#include "io/button/UserButton.h"
#include "io/relay/RelayManager.h"
#include "io/analog/AnalogInputManager.h"
#include "io/digital/DigitalInputManager.h"

#include "OptaVariant.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class Opta
{
public:
  typedef std::shared_ptr<Opta> SharedPtr;


  static SharedPtr
  create(
    UA_Server * server,
    OptaVariant::Type const opta_type);


  Opta(
    UA_Server * server,
    UA_NodeId const & node_id,
    OptaVariant::Type const opta_type);


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

  void
  add_led_output(
    UA_Server * server,
    const char * display_name,
    Led::OnSetLedStateFunc const on_set_led_state);

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
