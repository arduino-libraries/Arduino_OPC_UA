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

#include <Arduino.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

/**
 * @class UserButton
 * @brief Provides an OPC UA variable node abstraction for a user button input.
 *
 * This class creates an OPC UA variable node which is representing a user button input.
 * When reading from the OPC UA variable node a callback is triggered which performs the
 * actual readout of the current state of the user button.
 */
class UserButton
{
public:
  /**
   * SharedPtr is std::shared_ptr of an UserButton class.
   */
  typedef std::shared_ptr<UserButton> SharedPtr;


  /**
   * Creates a new instance of the opcua::UserButton class, creating an OPC UA variable node "User Button" abstraction in the process.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param parent_node_id OPC UA node id of parent object in OPC UA tree.
   * @return std::shared_ptr holding the newly allocated instance of opcua::UserButton.
   */
  static SharedPtr
  create(
    UA_Server * server,
    UA_NodeId const & parent_node_id);


  /**
   * Constructor of the opcua::UserButton class.
   * Note: Objects should not be instantiated directly, but by using UserButton::create.
   * @param node_id OPC UA node id of the variable node representing the user button.
   */
  UserButton(
    UA_NodeId const & node_id);


  /**
   * This function is called by the framework when a read-access on the variable node representing the user button input is performed.
   * Note: This function should not be called directly, it will be invoked by the framework.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param node_id OPC UA node id of the variable node representing the user button.
   */
  void
  onReadRequest(
    UA_Server * server,
    UA_NodeId const * node_id);


private:
  UA_NodeId _node_id;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
