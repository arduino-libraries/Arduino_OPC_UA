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
 * @class DigitalInput
 * @brief Provides an OPC UA variable node abstraction for a digital input.
 *
 * This class creates an OPC UA variable node which is representing a digital input. When
 * reading from the OPC UA variable node a callback is triggered which performs the
 * actual readout of a digital input pin.
 */
class DigitalInput
{
public:
  /**
   * SharedPtr is std::shared_ptr of a DigitalInput class.
   */
  typedef std::shared_ptr<DigitalInput> SharedPtr;
  /**
   * OnReadRequestFunc is definition for a callback which is called
   * during a read-access on the variable node representing the digital
   * input performing the actual digital reading.
   */
  typedef std::function<PinStatus(void)> OnReadRequestFunc;


  /**
   * Creates a new instance of the opcua::DigitalInput class, creating an OPC UA variable node abstraction in the process.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param parent_node_id OPC UA node id of parent object in OPC UA tree.
   * @param display_name Character string providing an easy identifiable name for the variable node representing an analog input, i.e. "Digital Input I1".
   * @param on_read_request Function pointer which is called during a read-access on the variable node representing the digital input.
   * @return std::shared_ptr holding the newly allocated instance of opcua::DigitalInput.
   */
  static SharedPtr
  create(
    UA_Server * server,
    UA_NodeId const & parent_node_id,
    const char * display_name,
    OnReadRequestFunc const on_read_request);


  /**
   * Constructor of the opcua::DigitalInput class.
   * Note: Objects should not be instantiated directly, but by using DigitalInput::create.
   * @param node_id OPC UA node id of the variable node representing the digital input.
   * @param on_read_request Function pointer which is called during a read-access on the variable node representing the digital input.
   */
  DigitalInput(
    UA_NodeId const & node_id,
    OnReadRequestFunc const on_read_request);


  /**
   * This function is called by the framework when a read-access on the variable node representing the digital input is performed.
   * Note: This function should not be called directly, it will be invoked by the framework.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param node_id OPC UA node id of the variable node representing the digital input.
   */
  void
  onReadRequest(
    UA_Server * server,
    UA_NodeId const * node_id);


private:
  UA_NodeId _node_id;
  OnReadRequestFunc _on_read_request;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
