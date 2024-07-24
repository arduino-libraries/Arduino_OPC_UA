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
: _server{server}
, _node_id{node_id}
, _analog_input_mgr{nullptr}
, _digital_input_mgr{nullptr}
, _relay_mgr{nullptr}
, _led_mgr{nullptr}
{
  _usr_button = opcua::UserButton::create(_server, _node_id);
  if (!_usr_button)
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "ArduinoOpta::Ctor: UserButton::create(...) failed.");
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

ArduinoOpta::SharedPtr ArduinoOpta::create(UA_Server * server, ArduinoOptaVariant::Type const opta_type)
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
  UA_String modelName = UA_STRING((char *)ArduinoOptaVariant::toString(opta_type).c_str());
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

AnalogInputManager::SharedPtr ArduinoOpta::analog_input_mgr()
{
  if (!_analog_input_mgr)
  {
    _analog_input_mgr = opcua::AnalogInputManager::create(_server, _node_id);
    if (!_analog_input_mgr)
      UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "ArduinoOpta::analog_input_mgr: AnalogInputManager::create(...) failed.");
  }

  return _analog_input_mgr;
}

DigitalInputManager::SharedPtr ArduinoOpta::digital_input_mgr()
{
  if (!_digital_input_mgr)
  {
    _digital_input_mgr = opcua::DigitalInputManager::create(_server, _node_id);
    if (!_digital_input_mgr)
      UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "ArduinoOpta::digital_input_mgr: DigitalInputManager::create(...) failed.");
  }

  return _digital_input_mgr;
}

RelayManager::SharedPtr ArduinoOpta::relay_mgr()
{
  if (!_relay_mgr)
  {
    _relay_mgr = opcua::RelayManager::create(_server, _node_id);
    if (!_relay_mgr)
      UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "ArduinoOpta::relay_mgr: RelayManager::create(...) failed.");
  }

  return _relay_mgr;
}

LedManager::SharedPtr ArduinoOpta::led_mgr()
{
  if (!_led_mgr)
  {
    _led_mgr = opcua::LedManager::create(_server, _node_id);
    if (!_led_mgr)
      UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "ArduinoOpta::led_mgr: LedManager::create(...) failed.");
  }

  return _led_mgr;
}

ArduinoOptaDigitalMechExpansion::SharedPtr ArduinoOpta::create_digital_mechanical_expansion(uint8_t const exp_num)
{
  auto const exp_mech_opcua = opcua::ArduinoOptaDigitalMechExpansion::create(_server, _node_id, exp_num);
  _dig_mech_exp_list.push_back(exp_mech_opcua);
  return exp_mech_opcua;
}

ArduinoOptaDigitalStSolidExpansion::SharedPtr ArduinoOpta::create_digital_solid_state_expansion(uint8_t const exp_num)
{
  auto const exp_solid_state_opcua = opcua::ArduinoOptaDigitalStSolidExpansion::create(_server, _node_id, exp_num);
  _dig_solid_state_exp_list.push_back(exp_solid_state_opcua);
  return exp_solid_state_opcua;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
