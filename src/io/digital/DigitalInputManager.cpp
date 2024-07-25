/*
 * Copyright (c) 2024 Arduino
 *
 * SPDX-License-Identifier: MPL-2.0
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include "DigitalInputManager.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

DigitalInputManager::DigitalInputManager(UA_NodeId const & node_id)
: _node_id{node_id}
{
  /* Nothing happens here. */
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

DigitalInputManager::SharedPtr DigitalInputManager::create(UA_Server * server, UA_NodeId const parent_node_id)
{
  UA_StatusCode rc = UA_STATUSCODE_GOOD;

  UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
  oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Digital Inputs");
  UA_NodeId node_id;
  rc = UA_Server_addObjectNode(server,
                               UA_NODEID_NULL,
                               parent_node_id,
                               UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                               UA_QUALIFIEDNAME(1, "DigitalInputs"),
                               UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                               oAttr,
                               NULL,
                               &node_id);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "DigitalInputManager::create: UA_Server_addObjectNode(...) failed with %s", UA_StatusCode_name(rc));
    return nullptr;
  }

  auto const instance_ptr = std::make_shared<DigitalInputManager>(node_id);
  return instance_ptr;
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void DigitalInputManager::add_digital_input(UA_Server * server,
                                            const char * display_name,
                                            DigitalInput::OnReadRequestFunc const on_read_request_func)
{
  auto const digital_input = DigitalInput::create(server, _node_id, display_name, on_read_request_func);
  if (!digital_input){
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "DigitalInputManager::add_digital_input: DigitalInput::create(...) failed: returned nullptr");
    return;
  }
  _digital_input_list.push_back(digital_input);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
