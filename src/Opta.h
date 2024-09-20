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

#include "open62541.h"

#include <memory>

#include "io/led/LedManager.h"
#include "io/button/UserButton.h"
#include "io/relay/RelayManager.h"
#include "io/analog/AnalogInputManager.h"
#include "io/digital/DigitalInputManager.h"

#include "OptaVariant.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

/**
 * opcua is used as enclosing namespace for all parts of the Arduino_OPC_UA library
 * in order to avoid naming conflicts with already existing frameworks pertaining the
 * Arduino Opta.
 */
namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

/**
 * @class Opta
 * @brief Provides functions for exposing various IO capabilities of the Arduino Opta via OPC UA.
 *
 * This class allows the user to expose analog and digital inputs, as well as relay and LED outputs
 * via OPC UA properties.
 */
class Opta
{
public:
  /**
   * SharedPtr is std::shared_ptr of an Opta class.
   */
  typedef std::shared_ptr<Opta> SharedPtr;


  /**
   * Creates a new instance of the opcua::Opta class, creating an OPC UA object abstraction in the process.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param opta_type Enumerated type describing which Opta (WiFi, RS485, Lite) variant is being created.
   * @return std::shared_ptr holding the newly allocated instance of opcua::Opta.
   */
  static SharedPtr
  create(
    UA_Server * server,
    OptaVariant::Type const opta_type);


  /**
   * Constructor of the opcua::Opta class.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param node_id OPC UA node id uniquely identifying the OPC UA representation of the opcua::Opta class as an OPC UA object node.
   * @param opta_type Enumerated type describing which Opta (WiFi, RS485, Lite) variant is being created.
   */
  Opta(
    UA_Server * server,
    UA_NodeId const & node_id,
    OptaVariant::Type const opta_type);


  /**
   * Adds an analog input to the opcua::Opta object node and exposes it as an OPC UA variable node.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param display_name Character string providing an easy identifiable name for the variable node.
   * @param on_read_request Function pointer which is called during a read-access on the variable node representing the analog input.
   */
  void
  addAnalogInput(
    UA_Server * server,
    const char * display_name,
    AnalogInput::OnReadRequestFunc const on_read_request);

  /**
   * Adds a digital input to the opcua::Opta object node and exposes it as an OPC UA variable node.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param display_name Character string providing an easy identifiable name for the variable node.
   * @param on_read_request Function pointer which is called during a read-access on the variable node representing the digital input.
   */
  void
  addDigitalInput(
    UA_Server * server,
    const char * display_name,
    DigitalInput::OnReadRequestFunc const on_read_request);

  /**
   * Adds a relay output to the opcua::Opta object node and exposes it as an OPC UA variable node.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param display_name Character string providing an easy identifiable name for the variable node.
   * @param on_set_relay_state Function pointer which is called during a write-access on the variable node representing the relay output.
   */
  void
  addRelayOutput(
    UA_Server * server,
    const char * display_name,
    Relay::OnSetRelayStateFunc const on_set_relay_state);

  /**
   * Adds a LED output to the opcua::Opta object node and exposes it as an OPC UA variable node.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param display_name Character string providing an easy identifiable name for the variable node.
   * @param on_set_led_state Function pointer which is called during a write-access on the variable node representing the LED output.
   */
  void
  addLedOutput(
    UA_Server * server,
    const char * display_name,
    Led::OnSetLedStateFunc const on_set_led_state);


private:
  UA_Server * _server;
  UA_NodeId _node_id;

  UserButton::SharedPtr _usr_button;
  AnalogInputManager::SharedPtr _analog_input_mgr;
  DigitalInputManager::SharedPtr _digital_input_mgr;
  RelayManager::SharedPtr _relay_mgr;
  LedManager::SharedPtr _led_mgr;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
