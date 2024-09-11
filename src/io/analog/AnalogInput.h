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
 * @class AnalogInput
 * @brief Provides an OPC UA variable node abstraction for an analog input.
 *
 * This class creates an OPC UA variable node which is representing an analog input. When
 * reading from the OPC UA variable node a callback is triggered which performs the
 * actual analog readout of an analog input pin.
 */
class AnalogInput
{
public:
  /**
   * SharedPtr is std::shared_ptr of an AnalogInput class.
   */
  typedef std::shared_ptr<AnalogInput> SharedPtr;
  /**
   * OnReadRequestFunc is definition for a callback which is called
   * during a read-access on the variable node representing the analog
   * input performing the actual analog reading.
   */
  typedef std::function<float(void)> OnReadRequestFunc;


  /**
   * Creates a new instance of the opcua::AnalogInput class, creating an OPC UA variable node abstraction in the process.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param parent_node_id OPC UA node id of parent object in OPC UA tree.
   * @param display_name Character string providing an easy identifiable name for the variable node representing an analog input, i.e. "Analog Input I1".
   * @param on_read_request Function pointer which is called during a read-access on the variable node representing the analog input.
   * @return std::shared_ptr holding the newly allocated instance of opcua::AnalogInput.
   */
  static SharedPtr
  create(
    UA_Server * server,
    UA_NodeId const & parent_node_id,
    const char * display_name,
    OnReadRequestFunc const on_read_request);


  /**
   * Constructor of the opcua::AnalogInput class.
   * Note: Objects should not be instantiated directly, but by using AnalogInput::create.
   * @param node_id OPC UA node id of the variable node representing the analog input.
   * @param on_read_request Function pointer which is called during a read-access on the variable node representing the analog input.
   */
  AnalogInput(
    UA_NodeId const & node_id,
    OnReadRequestFunc const on_read_request);


  /**
   * This function is called by the framework when a read-access on the variable node representing the analog input is performed.
   * Note: This function should not be called directly, it will be invoked by the framework.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param node_id OPC UA node id of the variable node representing the analog input.
   */
  void onReadRequest(
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
