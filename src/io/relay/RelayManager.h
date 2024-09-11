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

#include <list>
#include <memory>

#include "Relay.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

/**
 * @class RelayManager
 * @brief Provides methods for creating and storing Relay objects in a collection.
 *
 * This class creates an OPC UA object node which is representing all relays
 * of a given OPC UA devices. Relays can be created and added to the OPC UA
 * object node using this class.
 */
class RelayManager
{
public:
  /**
   * SharedPtr is std::shared_ptr of an RelayManager class.
   */
  typedef std::shared_ptr<RelayManager> SharedPtr;


  /**
   * Creates a new instance of the opcua::RelayManager class, creating an OPC UA object node abstraction in the process.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param parent_node_id OPC UA node id of parent object in OPC UA tree.
   * @return std::shared_ptr holding the newly allocated instance of opcua::RelayManager.
   */
  static SharedPtr
  create(
    UA_Server * server,
    UA_NodeId const parent_node_id);


  /**
   * Constructor of the opcua::RelayManager class.
   * Note: Objects should not be instantiated directly, but by using RelayManager::create.
   * @param node_id OPC UA node id of the object node representing all relays.
   */
  RelayManager(
    UA_NodeId const & node_id);


  /**
   * This function creates a new opcua::Relay and adds it to the opcua::RelayManager.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param display_name Character string providing an easy identifiable name for the variable node representing a relay, i.e. "Relay 1".
   * @param on_set_relay_state Function pointer which is called during a write-access on the variable node representing a relay.
   */
  void
  add_relay_output(
    UA_Server * server,
    const char * display_name,
    Relay::OnSetRelayStateFunc const on_set_relay_state);


private:
  UA_NodeId _node_id;
  std::list<Relay::SharedPtr> _relay_list;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
