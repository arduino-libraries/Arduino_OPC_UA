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
 * @class AnalogOutput
 * @brief Provides an OPC UA variable node abstraction for an analog output.
 *
 * This class creates an OPC UA variable node which is representing an analog output.
 * When writing to the OPC UA variable node a callback is triggered which performs
 * the setting of the output value of an actual analog output pin. When reading from the
 * OPC UA variable node a different callback is triggered which performs the actual analog
 * readout of an analog output pin.
 */
class AnalogOutput
{
public:
  /**
   * SharedPtr is std::shared_ptr of an AnalogOutput class.
   */
  typedef std::shared_ptr<AnalogOutput> SharedPtr;
  /**
   * OnReadRequestFunc is definition for a callback which is called
   * during a read-access on the variable node representing the analog
   * output performing the actual analog read-back from the current
   * value of the analog output pin.
   */
  typedef std::function<float(void)> OnReadRequestFunc;
  /**
   * OnWriteRequestFunc is definition for a callback which is called
   * during a write-access on the variable node representing the analog
   * output performing the actual writing of the desired output voltage
   * to the analog output pin.
   */
  typedef std::function<void(float)> OnWriteRequestFunc;


  /**
   * Creates a new instance of the opcua::AnalogOutput class, creating an OPC UA variable node abstraction in the process.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param parent_node_id OPC UA node id of parent object in OPC UA tree.
   * @param display_name Character string providing an easy identifiable name for the variable node representing an analog output, i.e. "Analog Output O1".
   * @param on_read_request Function pointer which is called during a read-access on the variable node representing the analog output.
   * @param on_write_request Function pointer which is called during a write-access on the variable node representing the analog output.
   * @return std::shared_ptr holding the newly allocated instance of opcua::AnalogOutput.
   */
  static SharedPtr
  create(
    UA_Server * server,
    UA_NodeId const & parent_node_id,
    const char * display_name,
    OnReadRequestFunc const on_read_request,
    OnWriteRequestFunc const on_write_request);


  /**
   * Constructor of the opcua::AnalogOutput class.
   * Note: Objects should not be instantiated directly, but by using AnalogOutput::create.
   * @param node_id OPC UA node id of the variable node representing the analog output.
   * @param on_read_request Function pointer which is called during a read-access on the variable node representing the analog output.
   * @param on_write_request Function pointer which is called during a write-access on the variable node representing the analog output.
   */
  AnalogOutput(
    UA_NodeId const & node_id,
    OnReadRequestFunc const on_read_request,
    OnWriteRequestFunc const on_write_request);


  /**
   * This function is called by the framework when a read-access on the variable node representing the analog output is performed.
   * Note: This function should not be called directly, it will be invoked by the framework.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param node_id OPC UA node id of the variable node representing the analog output.
   */
  void
  onReadRequest(
    UA_Server * server,
    UA_NodeId const * node_id);

  /**
   * This function is called by the framework when a write-access on the variable node representing the analog output is performed.
   * Note: This function should not be called directly, it will be invoked by the framework.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param node_id OPC UA node id of the variable node representing the analog output.
   * @param voltage Desired output voltage value for the analog output.
   */
  void
  onWriteRequest(
    UA_Server * server,
    UA_NodeId const * node_id,
    float const voltage);


private:
  UA_NodeId _node_id;
  OnReadRequestFunc const _on_read_request;
  OnWriteRequestFunc const _on_write_request;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
