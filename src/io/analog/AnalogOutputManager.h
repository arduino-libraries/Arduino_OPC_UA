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

#include <list>
#include <memory>

#include "AnalogOutput.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class AnalogOutputManager
{
public:
  typedef std::shared_ptr<AnalogOutputManager> SharedPtr;

  static SharedPtr create(UA_Server * server, UA_NodeId const parent_node_id);

  AnalogOutputManager(UA_NodeId const & node_id);

  void add_analog_output(UA_Server * server,
                         const char * display_name,
                         AnalogOutput::OnWriteRequestFunc const on_write_request_func);


private:
  UA_NodeId _node_id;
  std::list<AnalogOutput::SharedPtr> _analog_output_list;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
