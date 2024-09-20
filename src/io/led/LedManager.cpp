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

#include "LedManager.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

LedManager::LedManager(
  UA_NodeId const & node_id)
: _node_id{node_id}
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

LedManager::SharedPtr
LedManager::create(
  UA_Server * server,
  UA_NodeId const parent_node_id)
{
  UA_StatusCode rc = UA_STATUSCODE_GOOD;

  UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
  oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "LEDs");
  UA_NodeId node_id;
  rc = UA_Server_addObjectNode(server,
                               UA_NODEID_NULL,
                               parent_node_id,
                               UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                               UA_QUALIFIEDNAME(1, "LEDs"),
                               UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                               oAttr,
                               NULL,
                               &node_id);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "%s: UA_Server_addObjectNode(...) failed with %s", __PRETTY_FUNCTION__, UA_StatusCode_name(rc));
    return nullptr;
  }

  auto const instance_ptr = std::make_shared<LedManager>(node_id);
  return instance_ptr;
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void
LedManager::addLedOutput(
  UA_Server * server,
  const char * display_name,
  Led::OnSetLedStateFunc const on_set_led_state)
{
  auto const led = Led::create(server, _node_id, display_name, on_set_led_state);
  if (!led) {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: Led::create(...) failed: returned nullptr", __PRETTY_FUNCTION__);
    return;
  }
  _led_list.push_back(led);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
