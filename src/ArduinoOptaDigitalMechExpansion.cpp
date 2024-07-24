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

#include "ArduinoOptaDigitalMechExpansion.h"

#include <Arduino.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

ArduinoOptaDigitalMechExpansion::SharedPtr ArduinoOptaDigitalMechExpansion::create(UA_Server * server, UA_NodeId const parent_node_id, uint8_t const exp_num)
{
  UA_StatusCode rc = UA_STATUSCODE_GOOD;

  char display_name[32] = {0};
  snprintf(display_name, sizeof(display_name), "Expansion %d: Digital (Mechanic)", exp_num);

  UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
  oAttr.displayName = UA_LOCALIZEDTEXT("en-US", display_name);
  UA_NodeId node_id;
  rc = UA_Server_addObjectNode(server,
                               UA_NODEID_NULL,
                               parent_node_id,
                               UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                               UA_QUALIFIEDNAME(1, "DigExpMech"),
                               UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                               oAttr,
                               NULL,
                               &node_id);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "ArduinoOptaDigitalMechExpansion::create: UA_Server_addObjectNode(...) failed with %s", UA_StatusCode_name(rc));
    return nullptr;
  }

  auto const instance_ptr = std::make_shared<ArduinoOptaDigitalMechExpansion>(server, node_id);
  return instance_ptr;
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

RelayManager::SharedPtr ArduinoOptaDigitalMechExpansion::relay_mgr()
{
  if (!_relay_mgr)
  {
    _relay_mgr = opcua::RelayManager::create(_server, _node_id);
    if (!_relay_mgr)
      UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "ArduinoOptaDigitalMechExpansion::relay_mgr: RelayManager::create(...) failed.");
  }

  return _relay_mgr;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */