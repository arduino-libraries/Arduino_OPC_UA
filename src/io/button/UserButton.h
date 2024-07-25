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

#include <Arduino.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class UserButton
{
public:
  typedef std::shared_ptr<UserButton> SharedPtr;

  static SharedPtr create(UA_Server * server, UA_NodeId const & parent_node_id);

  UserButton(UA_NodeId const & node_id);

  void onReadRequest(UA_Server * server, UA_NodeId const * node_id);


private:
  UA_NodeId _node_id;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
