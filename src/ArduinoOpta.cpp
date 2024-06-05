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

#include "ArduinoOpta.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

ArduinoOpta::ArduinoOpta(UA_Server * server, UA_NodeId const & node_id)
: _node_id{node_id}
{
  _usr_button = opcua::UserButton::create(server, _node_id);
  if (!_usr_button) {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "ArduinoOpta::Ctor: UserButton::create(...) failed.");
  }

  _analog_input_mgr = opcua::AnalogInputManager::create(server, _node_id);
  if (!_analog_input_mgr) {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "ArduinoOpta::Ctor: AnalogInputManager::create(...) failed.");
  }

  _digital_input_mgr = opcua::DigitalInputManager::create(server, _node_id);
  if (!_digital_input_mgr) {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "ArduinoOpta::Ctor: DigitalInputManager::create(...) failed.");
  }

  _relay_mgr = opcua::RelayManager::create(server, _node_id);
  if (!_relay_mgr) {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "ArduinoOpta::Ctor: RelayManager::create(...) failed.");
  }
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

ArduinoOpta::SharedPtr ArduinoOpta::create(UA_Server * server)
{
  UA_StatusCode rc = UA_STATUSCODE_GOOD;

  UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
  oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Arduino Opta");
  UA_NodeId node_id;
  rc = UA_Server_addObjectNode(server,
                               UA_NODEID_NULL,
                               UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                               UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                               UA_QUALIFIEDNAME(1, "ArduinoOpta"),
                               UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                               oAttr,
                               NULL,
                               &node_id);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "ArduinoOpta::create: UA_Server_addObjectNode(...) failed with %s",
                 UA_StatusCode_name(rc));
    return nullptr;
  }

  UA_VariableAttributes mnAttr = UA_VariableAttributes_default;
  UA_String manufacturerName = UA_STRING("Arduino");
  UA_Variant_setScalar(&mnAttr.value, &manufacturerName, &UA_TYPES[UA_TYPES_STRING]);
  mnAttr.displayName = UA_LOCALIZEDTEXT("en-US", "ManufacturerName");
  rc = UA_Server_addVariableNode(server,
                                 UA_NODEID_NULL,
                                 node_id,
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                 UA_QUALIFIEDNAME(1, "ManufacturerName"),
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                 mnAttr,
                                 NULL,
                                 NULL);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "ArduinoOpta::create: UA_Server_addVariableNode(..., \"ManufacturerName\", ...) failed with %s",
                 UA_StatusCode_name(rc));
    return nullptr;
  }

  UA_VariableAttributes modelAttr = UA_VariableAttributes_default;
  UA_String modelName = UA_STRING("Arduino Opta WiFi");
  UA_Variant_setScalar(&modelAttr.value, &modelName, &UA_TYPES[UA_TYPES_STRING]);
  modelAttr.displayName = UA_LOCALIZEDTEXT("en-US", "ModelName");
  rc = UA_Server_addVariableNode(server,
                                 UA_NODEID_NULL,
                                 node_id,
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                 UA_QUALIFIEDNAME(1, "ModelName"),
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                 modelAttr,
                                 NULL,
                                 NULL);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "ArduinoOpta::create: UA_Server_addVariableNode(..., \"ModelName\", ...) failed with %s",
                 UA_StatusCode_name(rc));
    return nullptr;
  }

  UA_VariableAttributes statusAttr = UA_VariableAttributes_default;
  UA_Boolean status = true;
  UA_Variant_setScalar(&statusAttr.value, &status, &UA_TYPES[UA_TYPES_BOOLEAN]);
  statusAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Status");
  rc = UA_Server_addVariableNode(server,
                                 UA_NODEID_NULL,
                                 node_id,
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                 UA_QUALIFIEDNAME(1, "Status"),
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                 statusAttr,
                                 NULL,
                                 NULL);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "ArduinoOpta::create: UA_Server_addVariableNode(..., \"Status\", ...) failed with %s",
                 UA_StatusCode_name(rc));
    return nullptr;
  }

  auto const instance_ptr = std::make_shared<ArduinoOpta>(server, node_id);
  return instance_ptr;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
