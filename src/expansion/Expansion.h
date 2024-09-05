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

class Expansion
{
public:
  typedef std::shared_ptr<Expansion> SharedPtr;


  Expansion(
    UA_Server * server,
    UA_NodeId const parent_node_id,
    char * display_name,
    char * node_name,
    char * model_name);
  virtual ~Expansion() = default;

  virtual std::string
  toSKUString() const = 0;


protected:
  UA_Server * _server;
  UA_NodeId _node_id;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
