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

#include "DigitalExpansion.h"

#include <Arduino.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

DigitalExpansion::DigitalExpansion(UA_Server * server,
                                   UA_NodeId const parent_node_id,
                                   char * display_name,
                                   char * node_name,
                                   char * model_name)
: _server{server}
{
  UA_StatusCode rc = UA_STATUSCODE_GOOD;

  UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
  oAttr.displayName = UA_LOCALIZEDTEXT("en-US", display_name);
  rc = UA_Server_addObjectNode(server,
                               UA_NODEID_NULL,
                               parent_node_id,
                               UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                               UA_QUALIFIEDNAME(1, node_name),
                               UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                               oAttr,
                               NULL,
                               &_node_id);

  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "DigitalExpansion::Ctor: UA_Server_addObjectNode(...) failed with %s", UA_StatusCode_name(rc));
    return;
  }

  UA_VariableAttributes mnAttr = UA_VariableAttributes_default;
  UA_String manufacturerName = UA_STRING("Arduino");
  UA_Variant_setScalar(&mnAttr.value, &manufacturerName, &UA_TYPES[UA_TYPES_STRING]);
  mnAttr.displayName = UA_LOCALIZEDTEXT("en-US", "ManufacturerName");
  rc = UA_Server_addVariableNode(server,
                                 UA_NODEID_NULL,
                                 _node_id,
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                 UA_QUALIFIEDNAME(1, "ManufacturerName"),
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                 mnAttr,
                                 NULL,
                                 NULL);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "DigitalExpansion::Ctor: UA_Server_addVariableNode(..., \"ManufacturerName\", ...) failed with %s",
                 UA_StatusCode_name(rc));
    return;
  }

  UA_VariableAttributes modelAttr = UA_VariableAttributes_default;
  UA_String modelName = UA_STRING(model_name);
  UA_Variant_setScalar(&modelAttr.value, &modelName, &UA_TYPES[UA_TYPES_STRING]);
  modelAttr.displayName = UA_LOCALIZEDTEXT("en-US", "ModelName");
  rc = UA_Server_addVariableNode(server,
                                 UA_NODEID_NULL,
                                 _node_id,
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                 UA_QUALIFIEDNAME(1, "ModelName"),
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                 modelAttr,
                                 NULL,
                                 NULL);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "DigitalExpansion::Ctor: UA_Server_addVariableNode(..., \"ModelName\", ...) failed with %s",
                 UA_StatusCode_name(rc));
    return;
  }

  UA_VariableAttributes statusAttr = UA_VariableAttributes_default;
  UA_Boolean status = true;
  UA_Variant_setScalar(&statusAttr.value, &status, &UA_TYPES[UA_TYPES_BOOLEAN]);
  statusAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Status");
  rc = UA_Server_addVariableNode(server,
                                 UA_NODEID_NULL,
                                 _node_id,
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                 UA_QUALIFIEDNAME(1, "Status"),
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                 statusAttr,
                                 NULL,
                                 NULL);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "DigitalExpansion::Ctor: UA_Server_addVariableNode(..., \"Status\", ...) failed with %s",
                 UA_StatusCode_name(rc));
    return;
  }
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

AnalogInputManager::SharedPtr DigitalExpansion::analog_input_mgr()
{
  if (!_analog_input_mgr)
  {
    _analog_input_mgr = opcua::AnalogInputManager::create(_server, _node_id);
    if (!_analog_input_mgr)
      UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "DigitalExpansion::analog_input_mgr: AnalogInputManager::create(...) failed.");
  }

  return _analog_input_mgr;
}

DigitalInputManager::SharedPtr DigitalExpansion::digital_input_mgr()
{
  if (!_digital_input_mgr)
  {
    _digital_input_mgr = opcua::DigitalInputManager::create(_server, _node_id);
    if (!_digital_input_mgr)
      UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "DigitalExpansion::digital_input_mgr: DigitalInputManager::create(...) failed.");
  }

  return _digital_input_mgr;
}

RelayManager::SharedPtr DigitalExpansion::relay_mgr()
{
  if (!_relay_mgr)
  {
    _relay_mgr = opcua::RelayManager::create(_server, _node_id);
    if (!_relay_mgr)
      UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "DigitalExpansion::relay_mgr: RelayManager::create(...) failed.");
  }

  return _relay_mgr;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
