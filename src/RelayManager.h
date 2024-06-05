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

#include <list>
#include <memory>

#include "Relay.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class RelayManager
{
public:
  typedef std::shared_ptr<RelayManager> SharedPtr;

  static SharedPtr create(UA_Server * server, UA_NodeId const parent_node_id);

  RelayManager(UA_NodeId const & node_id);

  void add_relay_output(UA_Server * server, const char * display_name);


private:
  UA_NodeId _node_id;
  std::list<Relay::SharedPtr> _relay_list;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
