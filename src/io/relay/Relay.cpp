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

#include "Relay.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * FUNCTION DEFINITION
 **************************************************************************************/

static void
relay_on_write_request(
  UA_Server *server,
  const UA_NodeId *sessionId,
  void *sessionContext,
  const UA_NodeId *nodeid,
  void *nodeContext,
  const UA_NumericRange *range,
  const UA_DataValue *data)
{
  bool const value = *(UA_Boolean *)(data->value.data) == true;
  Relay * this_ptr = reinterpret_cast<Relay *>(nodeContext);
  this_ptr->onWriteRequest(server, nodeid, value);
}

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

Relay::Relay(
  UA_NodeId const & node_id,
  OnSetRelayStateFunc const on_set_relay_state)
  : _node_id{node_id}
  , _on_set_relay_state{on_set_relay_state}
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

Relay::SharedPtr
Relay::create(
  UA_Server *server,
  UA_NodeId const &parent_node_id,
  const char *display_name,
  OnSetRelayStateFunc const on_set_relay_state)
{
  UA_StatusCode rc = UA_STATUSCODE_GOOD;

  UA_VariableAttributes relay_value_attr = UA_VariableAttributes_default;

  UA_Boolean relay_value = false;
  UA_Variant_setScalar(&relay_value_attr.value, &relay_value, &UA_TYPES[UA_TYPES_BOOLEAN]);

  relay_value_attr.displayName = UA_LOCALIZEDTEXT("en-US", (char *)display_name);
  relay_value_attr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId;
  relay_value_attr.accessLevel =
    UA_ACCESSLEVELMASK_READ |
    UA_ACCESSLEVELMASK_WRITE | UA_ACCESSLEVELMASK_STATUSWRITE |
    UA_ACCESSLEVELMASK_TIMESTAMPWRITE; /* Status and timestamp write access necessary for opcua-client. */

  UA_NodeId node_id;
  rc = UA_Server_addVariableNode(server,
                                 UA_NODEID_NULL,
                                 parent_node_id,
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                 UA_QUALIFIEDNAME(1, "Value"),
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                 relay_value_attr,
                                 NULL,
                                 &node_id);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "%s: UA_Server_addVariableNode(...) failed with %s", __PRETTY_FUNCTION__, UA_StatusCode_name(rc));
    return nullptr;
  }

  /* Create an instance of Relay here. */
  auto const instance_ptr = std::make_shared<Relay>(node_id, on_set_relay_state);

  rc = UA_Server_setNodeContext(server, node_id, reinterpret_cast<void *>(instance_ptr.get()));
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "%s: UA_Server_setNodeContext(...) failed with %s", __PRETTY_FUNCTION__, UA_StatusCode_name(rc));
    return nullptr;
  }

  UA_ValueCallback callback;
  callback.onRead = NULL;
  callback.onWrite = relay_on_write_request;
  rc = UA_Server_setVariableNode_valueCallback(server, node_id, callback);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "%s: UA_Server_setVariableNode_valueCallback(...) failed with %s", __PRETTY_FUNCTION__, UA_StatusCode_name(rc));
    return nullptr;
  }

  return instance_ptr;
}

void
Relay::onWriteRequest(
  UA_Server * server,
  UA_NodeId const * node_id,
  bool const value)
{
  UA_LOG_DEBUG(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: value = %d", __PRETTY_FUNCTION__, value);
  _on_set_relay_state(value);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
