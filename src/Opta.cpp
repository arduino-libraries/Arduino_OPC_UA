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

#include "Opta.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

Opta::Opta(
  UA_Server * server,
  UA_NodeId const & node_id,
  OptaVariant::Type const opta_type)
: _server{server}
, _node_id{node_id}
, _usr_button{opcua::UserButton::create(_server, _node_id)}
, _analog_input_mgr{opcua::AnalogInputManager::create(_server, _node_id)}
, _digital_input_mgr{opcua::DigitalInputManager::create(_server, _node_id)}
, _relay_mgr{opcua::RelayManager::create(_server, _node_id)}
, _led_mgr{(opta_type == OptaVariant::Type::WiFi) ? opcua::LedManager::create(_server, _node_id) : nullptr}
{
  if (!_usr_button)
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: UserButton::create(...) failed.", __PRETTY_FUNCTION__);
  if (!_analog_input_mgr)
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: AnalogInputManager::create(...) failed.", __PRETTY_FUNCTION__);
  if (!_digital_input_mgr)
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: DigitalInputManager::create(...) failed.", __PRETTY_FUNCTION__);
  if (!_relay_mgr)
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: RelayManager::create(...) failed.", __PRETTY_FUNCTION__);
  if ((opta_type == OptaVariant::Type::WiFi) && !_led_mgr)
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: LedManager::create(...) failed.", __PRETTY_FUNCTION__);
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

Opta::SharedPtr
Opta::create(
  UA_Server * server,
  OptaVariant::Type const opta_type)
{
  UA_StatusCode rc = UA_STATUSCODE_GOOD;

  UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
  oAttr.displayName = UA_LOCALIZEDTEXT("en-US", (char *)OptaVariant::toString(opta_type).c_str());
  UA_NodeId node_id;
  rc = UA_Server_addObjectNode(server,
                               UA_NODEID_NULL,
                               UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                               UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                               UA_QUALIFIEDNAME(1, "Opta"),
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
                 "%s: UA_Server_addVariableNode(..., \"ManufacturerName\", ...) failed with %s", __PRETTY_FUNCTION__, UA_StatusCode_name(rc));
    return nullptr;
  }

  UA_VariableAttributes modelAttr = UA_VariableAttributes_default;
  UA_String modelName = UA_STRING((char *)OptaVariant::toSKUString(opta_type).c_str());
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
                 "%s: UA_Server_addVariableNode(..., \"ModelName\", ...) failed with %s", __PRETTY_FUNCTION__, UA_StatusCode_name(rc));
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
                 "%s: UA_Server_addVariableNode(..., \"Status\", ...) failed with %s", __PRETTY_FUNCTION__, UA_StatusCode_name(rc));
    return nullptr;
  }

  auto const instance_ptr = std::make_shared<Opta>(server, node_id, opta_type);
  return instance_ptr;
}

void
Opta::addAnalogInput(
  UA_Server * server,
  const char * display_name,
  AnalogInput::OnReadRequestFunc const on_read_request)
{
  _analog_input_mgr->addAnalogInput(server, display_name, on_read_request);
}

void
Opta::addDigitalInput(
  UA_Server * server,
  const char * display_name,
  DigitalInput::OnReadRequestFunc const on_read_request)
{
  _digital_input_mgr->addDigitalInput(server, display_name, on_read_request);
}

void
Opta::addRelayOutput(
  UA_Server * server,
  const char * display_name,
  Relay::OnSetRelayStateFunc const on_set_relay_state)
{
  _relay_mgr->addRelayOutput(server, display_name, on_set_relay_state);
}

void
Opta::addLedOutput(
  UA_Server * server,
  const char * display_name,
  Led::OnSetLedStateFunc const on_set_led_state)
{
  if (_led_mgr) /* Only available for Arduino Opta WiFi. */
    _led_mgr->addLedOutput(server, display_name, on_set_led_state);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
