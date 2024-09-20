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

#include "AnalogInput.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

/**
 * @class AnalogInputManager
 * @brief Provides methods for creating and storing AnalogInput objects in a collection.
 *
 * This class creates an OPC UA object node which is representing all analog
 * inputs of a given OPC UA devices. Analog inputs can be created and added
 * to the OPC UA object node using this class.
 */
class AnalogInputManager
{
public:
  /**
   * SharedPtr is std::shared_ptr of an AnalogInputManager class.
   */
  typedef std::shared_ptr<AnalogInputManager> SharedPtr;


  /**
   * Creates a new instance of the opcua::AnalogInputManager class, creating an OPC UA object node abstraction in the process.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param parent_node_id OPC UA node id of parent object in OPC UA tree.
   * @return std::shared_ptr holding the newly allocated instance of opcua::AnalogInputManager.
   */
  static SharedPtr
  create(
    UA_Server * server,
    UA_NodeId const parent_node_id);


  /**
   * Constructor of the opcua::AnalogInputManager class.
   * Note: Objects should not be instantiated directly, but by using AnalogInputManager::create.
   * @param node_id OPC UA node id of the object node representing all analog inputs.
   */
  AnalogInputManager(
    UA_NodeId const & node_id);


  /**
   * This function creates a new opcua::AnalogInput and adds it to the opcua::AnalogInputManager.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param display_name Character string providing an easy identifiable name for the variable node representing an analog input, i.e. "Analog Input I1".
   * @param on_read_request Function pointer which is called during a read-access on the variable node representing the analog input.
   */
  void
  addAnalogInput(
    UA_Server * server,
    const char * display_name,
    AnalogInput::OnReadRequestFunc const on_read_request);


private:
  UA_NodeId _node_id;
  std::list<AnalogInput::SharedPtr> _analog_input_list;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
