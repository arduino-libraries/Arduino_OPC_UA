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

#include "DigitalInput.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class DigitalInputManager
{
public:
  DigitalInputManager();

  UA_StatusCode begin(UA_Server * server,
                      UA_NodeId const parent_node_id);


  UA_StatusCode add_digital_input(UA_Server * server,
                                  const char * display_name,
                                  DigitalInput::OnReadRequestFunc const on_read_request_func);


private:
  bool _is_initialized;
  UA_NodeId _node_id;

  std::list<DigitalInput::SharedPtr> _digital_input_list;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
