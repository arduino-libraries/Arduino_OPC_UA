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

class Relay
{
public:
  typedef std::shared_ptr<Relay> SharedPtr;
  typedef std::function<void(bool const)> OnSetRelayStateFunc;


  static SharedPtr
  create(
    UA_Server *server,
    UA_NodeId const &parent_node_id,
    const char *display_name,
    OnSetRelayStateFunc const on_set_relay_state);


  Relay(
    UA_NodeId const &node_id,
    OnSetRelayStateFunc const on_set_relay_state);


  void
  onWriteRequest(
    UA_Server * server,
    UA_NodeId const * node_id,
    bool const value);


private:
  UA_NodeId _node_id;
  OnSetRelayStateFunc const _on_set_relay_state;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
