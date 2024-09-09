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

/**
 * @class Relay
 * @brief Provides an OPC UA variable node abstraction for controlling a mechanical or solid-state relay.
 *
 * This class creates an OPC UA variable node which is representing a mechanical or solid-state
 * relay. When writing to the OPC UA variable node a callback is triggered which either activates
 * or deactivates the relay.
 */
class Relay
{
public:
  /**
   * SharedPtr is std::shared_ptr of a Relay class.
   */
  typedef std::shared_ptr<Relay> SharedPtr;
  /**
   * OnSetRelayStateFunc is definition for a callback which is called
   * during a write-access on the variable node representing a relay
   * subsequently either activating (true -> switch closes) or deactivating
   * a relay (false -> switch opens).
   */
  typedef std::function<void(bool const)> OnSetRelayStateFunc;


  /**
   * Creates a new instance of the opcua::Relay class, creating an OPC UA variable node abstraction in the process.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param parent_node_id OPC UA node id of parent object in OPC UA tree.
   * @param display_name Character string providing an easy identifiable name for the variable node representing a relay, i.e. "Relay 1".
   * @param on_set_relay_state Function pointer which is called during a write-access on the variable node representing a relay.
   * @return std::shared_ptr holding the newly allocated instance of opcua::Relay.
   */
  static SharedPtr
  create(
    UA_Server *server,
    UA_NodeId const &parent_node_id,
    const char *display_name,
    OnSetRelayStateFunc const on_set_relay_state);


  /**
   * Constructor of the opcua::Relay class.
   * Note: Objects should not be instantiated directly, but by using Relay::create.
   * @param node_id OPC UA node id of the variable node representing the relay.
   * @param on_set_relay_state Function pointer which is called during a write-access on the variable node representing a relay.
   */
  Relay(
    UA_NodeId const &node_id,
    OnSetRelayStateFunc const on_set_relay_state);


  /**
   * This function is called by the framework when a write-access on the variable node representing a relay is performed.
   * Note: This function should not be called directly, it will be invoked by the framework.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param node_id OPC UA node id of the variable node representing the relay.
   * @param value Desired state of the relay, true -> relay is activated (relay switch closes), false -> LED is deactivated (relay switch opens).
   */
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
