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

#include "Led.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

/**
 * @class LedManager
 * @brief Provides methods for creating and storing LED objects in a collection.
 *
 * This class creates an OPC UA object node which is representing all LEDs
 * of a given OPC UA devices. LEDs can be created and added to the OPC UA
 * object node using this class.
 */
class LedManager
{
public:
  /**
   * SharedPtr is std::shared_ptr of an LedManager class.
   */
  typedef std::shared_ptr<LedManager> SharedPtr;


  /**
   * Creates a new instance of the opcua::LedManager class, creating an OPC UA object node abstraction in the process.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param parent_node_id OPC UA node id of parent object in OPC UA tree.
   * @return std::shared_ptr holding the newly allocated instance of opcua::LedManager.
   */
  static SharedPtr
  create(
    UA_Server * server,
    UA_NodeId const parent_node_id);


  /**
   * Constructor of the opcua::LedManager class.
   * Note: Objects should not be instantiated directly, but by using LedManager::create.
   * @param node_id OPC UA node id of the object node representing all LEDs.
   */
  LedManager(UA_NodeId const & node_id);


  /**
   * This function creates a new opcua::LED and adds it to the opcua::LEDManager.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param display_name Character string providing an easy identifiable name for the variable node representing a LED, i.e. "LED1".
   * @param on_set_led_state Function pointer which is called during a write-access on the variable node representing the LED.
   */
  void
  addLedOutput(
    UA_Server * server,
    const char * display_name,
    Led::OnSetLedStateFunc const on_set_led_state);


private:
  UA_NodeId _node_id;
  std::list<Led::SharedPtr> _led_list;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
