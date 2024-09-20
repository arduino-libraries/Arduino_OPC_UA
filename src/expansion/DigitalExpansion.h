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

#include "Expansion.h"

#include <memory>

#include "../io/relay/RelayManager.h"
#include "../io/analog/AnalogInputManager.h"
#include "../io/digital/DigitalInputManager.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

/**
 * @class DigitalExpansion
 * @brief Provides an OPC UA object node abstraction for both Digital Expansion board.
 *
 * This class creates an OPC UA object node which is representing an Arduino Opta
 * Digital Expansion board. Furthermore, this class provides methods for adding
 * OPC UA exposure to all IO entities supported by the Digital Expansion board.
 */
class DigitalExpansion : public Expansion
{
public:
  /**
   * SharedPtr is std::shared_ptr of an DigitalExpansion class.
   */
  typedef std::shared_ptr<DigitalExpansion> SharedPtr;


  /**
   * Constructor of the opcua::DigitalExpansion class.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param parent_node_id OPC UA node id of parent object in OPC UA tree.
   * @param display_name Character string providing an easy identifiable name for the object node representing an analog expansion board, i.e. "Arduino Opta Expansion 1: Analog".
   * @param node_name The unique node name identifying the Analog Expansion Board object node within the OPC UA tree.
   * @param model_name This parameter must be filled with the SKU of the actual Digital Expansion board.
   */
  DigitalExpansion(
    UA_Server * server,
    UA_NodeId const parent_node_id,
    char * display_name,
    char * node_name,
    char * model_name);
  /**
   * Destructor of the opcua::DigitalExpansion class.
   */
  virtual ~DigitalExpansion() = default;


/**
 * This function creates a new opcua::AnalogInput and adds it to the opcua::AnalogInputManager belonging to the opcua::DigitalExpansion class.
 * @param server Pointer to the OPC UA server implementation of the open62541 library.
 * @param display_name Character string providing an easy identifiable name for the variable node representing an analog input, i.e. "Analog Input I1".
 * @param on_read_request Function pointer which is called during a read-access on the variable node representing the analog input.
 */
  void
  addAnalogInput(
    UA_Server * server,
    const char * display_name,
    AnalogInput::OnReadRequestFunc const on_read_request);

  /**
   * This function creates a new opcua::DigitalInput and adds it to the opcua::DigitalInputManager belonging to the opcua::DigitalExpansion class.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param display_name Character string providing an easy identifiable name for the variable node representing an analog input, i.e. "Digital Input I1".
   * @param on_read_request Function pointer which is called during a read-access on the variable node representing the digital input.
   */
  void
  addDigitalInput(
    UA_Server * server,
    const char * display_name,
    DigitalInput::OnReadRequestFunc const on_read_request);

  /**
   * This function creates a new opcua::Relay and adds it to the opcua::RelayManager belonging to the opcua::DigitalExpansion class.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param display_name Character string providing an easy identifiable name for the variable node representing a relay, i.e. "Relay 1".
   * @param on_set_relay_state Function pointer which is called during a write-access on the variable node representing a relay.
   */
  void
  addRelayOutput(
    UA_Server * server,
    const char * display_name,
    Relay::OnSetRelayStateFunc const on_set_relay_state);


private:
  AnalogInputManager::SharedPtr _analog_input_mgr;
  DigitalInputManager::SharedPtr _digital_input_mgr;
  RelayManager::SharedPtr _relay_mgr;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
