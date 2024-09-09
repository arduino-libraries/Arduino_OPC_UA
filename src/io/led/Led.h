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
 * @class Led
 * @brief Provides an OPC UA variable node abstraction for controlling a LED.
 *
 * This class creates an OPC UA variable node which is representing a LED. When writing
 * to the OPC UA variable node a callback is triggered which either turns the LED on or off.
 */
class Led
{
public:
  /**
   * SharedPtr is std::shared_ptr of a Led class.
   */
  typedef std::shared_ptr<Led> SharedPtr;
  /**
   * OnSetLedStateFunc is definition for a callback which is called
   * during a write-access on the variable node representing a LED
   * subsequently turned the LED either ON (true) or OFF (false).
   */
  typedef std::function<void(bool const)> OnSetLedStateFunc;


  /**
   * Creates a new instance of the opcua::Led class, creating an OPC UA variable node abstraction in the process.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param parent_node_id OPC UA node id of parent object in OPC UA tree.
   * @param display_name Character string providing an easy identifiable name for the variable node representing a LED, i.e. "LED1".
   * @param on_set_led_state Function pointer which is called during a write-access on the variable node representing the LED.
   * @return std::shared_ptr holding the newly allocated instance of opcua::Led.
   */
  static SharedPtr
  create(
    UA_Server *server,
    UA_NodeId const &parent_node_id,
    const char *display_name,
    OnSetLedStateFunc const on_set_led_state);


  /**
   * Constructor of the opcua::Led class.
   * Note: Objects should not be instantiated directly, but by using Led::create.
   * @param node_id OPC UA node id of the variable node representing the analog output.
   * @param on_set_led_state Function pointer which is called during a write-access on the variable node representing the LED.
   */
  Led(
    UA_NodeId const &node_id,
    OnSetLedStateFunc const on_set_led_state);


  /**
   * This function is called by the framework when a write-access on the variable node representing a LED is performed.
   * Note: This function should not be called directly, it will be invoked by the framework.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param node_id OPC UA node id of the variable node representing the LED.
   * @param value Desired state of the LED, true -> LED is turned ON, false -> LED is turned off.
   */
  void
  onWriteRequest(
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
