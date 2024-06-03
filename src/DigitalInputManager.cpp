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

#include <map>

#include <Arduino.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

DigitalInputManager::DigitalInputManager()
: _is_initialized{false}
{
  /* Nothing happens here. */
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

UA_StatusCode DigitalInputManager::begin(UA_Server * server,
                                         UA_NodeId const parent_node_id)
{
  UA_StatusCode rc = UA_STATUSCODE_GOOD;

  UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
  oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Digital Inputs");
  rc = UA_Server_addObjectNode(server,
                               UA_NODEID_NULL,
                               parent_node_id,
                               UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                               UA_QUALIFIEDNAME(1, "DigitalInputs"),
                               UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                               oAttr,
                               NULL,
                               &_node_id);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,  "DigitalInputManager::begin: UA_Server_addObjectNode(...) failed with %s", UA_StatusCode_name(rc));
    return rc;
  }

  _is_initialized = true;
  return rc;
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

UA_StatusCode DigitalInputManager::add_digital_input(UA_Server * server,
                                                     const char * display_name,
                                                     DigitalInput::OnReadRequestFunc const on_read_request_func)
{
  if (!_is_initialized)
    return UA_STATUSCODE_BAD;

  UA_StatusCode rc = UA_STATUSCODE_GOOD;

  /* Create the digital input pin. */
  auto const digital_input = std::make_shared<DigitalInput>(server, _node_id, display_name, on_read_request_func);
  /* Add the digital input pin to our internal list. */
  _digital_input_list.push_back(digital_input);

  return UA_STATUSCODE_GOOD;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
