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

#include "../../open62541.h"

#include <memory>
#include <functional>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class Led
{
public:
  typedef std::shared_ptr<Led> SharedPtr;
  typedef std::function<void(bool const)> OnSetLedStateFunc;


  static SharedPtr
  create(
    UA_Server *server,
    UA_NodeId const &parent_node_id,
    const char *display_name,
    OnSetLedStateFunc const on_set_led_state);


  Led(
    UA_NodeId const &node_id,
    OnSetLedStateFunc const on_set_led_state);


  void onWriteRequest(
    UA_Server * server,
    UA_NodeId const * node_id,
    bool const value);


private:
  UA_NodeId _node_id;
  OnSetLedStateFunc const _on_set_led_state;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
