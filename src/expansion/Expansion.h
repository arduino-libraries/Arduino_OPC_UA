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

#include "../open62541.h"

#include <memory>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

/**
 * @class Expansion
 * @brief Provides a generic base class for various expansion board specificic derived classes.
 */
class Expansion
{
public:
  /**
   * SharedPtr is std::shared_ptr of an Expansion class.
   */
  typedef std::shared_ptr<Expansion> SharedPtr;


  /**
   * Constructor of the opcua::Expansion class.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @param parent_node_id OPC UA node id of parent object in OPC UA tree.
   * @param display_name Character string providing an easy identifiable name for the object node representing an analog expansion board, i.e. "Arduino Opta Expansion 1: Analog".
   * @param node_name The unique node name identifying the Analog Expansion Board object node within the OPC UA tree.
   * @param model_name This parameter must be filled with the SKU of the actual expansion board.
   */
  Expansion(
    UA_Server * server,
    UA_NodeId const parent_node_id,
    char * display_name,
    char * node_name,
    char * model_name);
  /**
   * Destructor of the opcua::Expansion class.
   */
  virtual ~Expansion() = default;


  /**
   * Returns the SKU number of a concrete expansion board, must be overridden in derived classes.
   * @return SKU number of concrete expansion board.
   */
  virtual std::string
  toSKUString() const = 0;


protected:
  /**
   * _server is a pointer to the OPC UA server implementation of the open62541 library.
   */
  UA_Server * _server;
  /**
   * node_id OPC UA node id of the object node representing an expansion.
   */
  UA_NodeId _node_id;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
