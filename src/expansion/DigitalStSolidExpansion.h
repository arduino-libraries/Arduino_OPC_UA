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

#include "DigitalExpansion.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

/**
 * @class DigitalStSolidExpansion
 * @brief Provides an OPC UA object node abstraction for a Digital Expansion board with solid-state relays.
 *
 * This class creates an OPC UA object node which is representing an Arduino Opta
 * Digital Expansion board with solid-state relays.
 */
class DigitalStSolidExpansion : public DigitalExpansion
{
public:
  /**
   * SharedPtr is std::shared_ptr of an DigitalStSolidExpansion class.
   */
  typedef std::shared_ptr<DigitalStSolidExpansion> SharedPtr;


  /**
   * Creates a new instance of the opcua::DigitalStSolidExpansion class, creating an OPC UA object node abstraction in the process.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param parent_node_id OPC UA node id of parent object in OPC UA tree.
   * @param exp_num A numerical identifier provided by the Arduino_Opta_Blueprint library and identifying the number of the expansion module in the daisy-chain of expansion modules, i.e. exp_num = 2 refers to the second connect expansion module.
   * @return std::shared_ptr holding the newly allocated instance of opcua::DigitalStSolidExpansion.
   */
  static SharedPtr
  create(
    UA_Server *server,
    UA_NodeId const parent_node_id,
    uint8_t const exp_num)
  {
    char display_name[64] = {0};
    snprintf(display_name, sizeof(display_name), "Arduino Opta Expansion %d: Digital (Solid State)", exp_num);

    char node_name[32] = {0};
    snprintf(node_name, sizeof(node_name), "DigExpSoli_%d", exp_num);

    auto const instance_ptr = std::make_shared<DigitalStSolidExpansion>(server, parent_node_id, display_name, node_name);
    return instance_ptr;
  }


  /**
   * Constructor of the opcua::DigitalStSolidExpansion class.
   * Note: Objects should not be instantiated directly, but by using DigitalStSolidExpansion::create.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param parent_node_id OPC UA node id of parent object in OPC UA tree.
   * @param display_name Character string providing an easy identifiable name for the object node representing an analog expansion board, i.e. "Arduino Opta Expansion 1: Digital (Solid State)".
   * @param node_name The unique node name identifying the Analog Expansion Board object node within the OPC UA tree.
   */
  DigitalStSolidExpansion(
    UA_Server * server,
    UA_NodeId const parent_node_id,
    char * display_name,
    char * node_name)
    : DigitalExpansion{server, parent_node_id, display_name, node_name, (char *)toSKUString().c_str()}
  {}
  /**
   * Destructor of the opcua::DigitalStSolidExpansion class.
   */
  virtual ~DigitalStSolidExpansion() = default;


  /**
   * Returns the SKU number of the Digital Expansion board with solid-state relays as std::string.
   * @return SKU number of Digital Expansion board / solid-state relays
   */
  virtual std::string
  toSKUString() const override final
  {
    return std::string("AFX00006");
  }
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
