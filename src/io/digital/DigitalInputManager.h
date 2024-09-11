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

#include "DigitalInput.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

/**
 * @class DigitalInputManager
 * @brief Provides methods for creating and storing DigitalInput objects in a collection.
 *
 * This class creates an OPC UA object node which is representing all digital
 * inputs of a given OPC UA devices. Digital inputs can be created and added
 * to the OPC UA object node using this class.
 */
class DigitalInputManager
{
public:
  /**
   * SharedPtr is std::shared_ptr of an DigitalInputManager class.
   */
  typedef std::shared_ptr<DigitalInputManager> SharedPtr;


  /**
   * Creates a new instance of the opcua::DigitalInputManager class, creating an OPC UA object node abstraction in the process.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param parent_node_id OPC UA node id of parent object in OPC UA tree.
   * @return std::shared_ptr holding the newly allocated instance of opcua::DigitalInputManager.
   */
  static SharedPtr
  create(
    UA_Server * server,
    UA_NodeId const parent_node_id);


  /**
   * Constructor of the opcua::DigitalInputManager class.
   * Note: Objects should not be instantiated directly, but by using DigitalInputManager::create.
   * @param node_id OPC UA node id of the object node representing all digital inputs.
   */
  DigitalInputManager(
    UA_NodeId const & node_id);


  /**
   * This function creates a new opcua::DigitalInput and adds it to the opcua::DigitalInputManager.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param display_name Character string providing an easy identifiable name for the variable node representing an analog input, i.e. "Digital Input I1".
   * @param on_read_request Function pointer which is called during a read-access on the variable node representing the digital input.
   */
  void
  add_digital_input(
    UA_Server * server,
    const char * display_name,
    DigitalInput::OnReadRequestFunc const on_read_request);


private:
  UA_NodeId _node_id;
  std::list<DigitalInput::SharedPtr> _digital_input_list;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
