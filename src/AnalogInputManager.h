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

#include "AnalogInput.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class AnalogInputManager
{
public:
  typedef std::shared_ptr<AnalogInputManager> SharedPtr;


  static SharedPtr create(UA_Server * server,
                          UA_NodeId const parent_node_id);


  /* Do no invoke directly, use create for creating
   * new instances of AnalogInputManager.
   */
  AnalogInputManager(UA_NodeId const & node_id);


  void add_analog_input(UA_Server * server,
                        const char * display_name,
                        AnalogInput::OnReadRequestFunc const on_read_request_func);


private:
  UA_NodeId _node_id;
  std::list<AnalogInput::SharedPtr> _analog_input_list;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
