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

#include "Led.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * FUNCTION DEFINITION
 **************************************************************************************/

static void
led_on_write_request(
  UA_Server *server,
  const UA_NodeId *sessionId,
  void *sessionContext,
  const UA_NodeId *nodeid,
  void *nodeContext,
  const UA_NumericRange *range,
  const UA_DataValue *data)
{
  bool const value = *(UA_Boolean *)(data->value.data) == true;
  Led * this_ptr = reinterpret_cast<Led *>(nodeContext);
  this_ptr->onWriteRequest(server, nodeid, value);
}

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

Led::Led(
  UA_NodeId const & node_id,
  OnSetLedStateFunc const on_set_led_state)
  : _node_id{node_id}
  , _on_set_led_state{on_set_led_state}
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

Led::SharedPtr
Led::create(
  UA_Server *server,
  UA_NodeId const &parent_node_id,
  const char *display_name,
  OnSetLedStateFunc const on_set_led_state)
{
  UA_StatusCode rc = UA_STATUSCODE_GOOD;

  UA_VariableAttributes led_value_attr = UA_VariableAttributes_default;

  UA_Boolean led_value = false;
  UA_Variant_setScalar(&led_value_attr.value, &led_value, &UA_TYPES[UA_TYPES_BOOLEAN]);

  led_value_attr.displayName = UA_LOCALIZEDTEXT("en-US", (char *)display_name);
  led_value_attr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId;
  led_value_attr.accessLevel =
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
                                 led_value_attr,
                                 NULL,
                                 &node_id);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "%s: UA_Server_addVariableNode(...) failed with %s", __PRETTY_FUNCTION__, UA_StatusCode_name(rc));
    return nullptr;
  }

  /* Create an instance of Led here. */
  auto const instance_ptr = std::make_shared<Led>(node_id, on_set_led_state);

  rc = UA_Server_setNodeContext(server, node_id, reinterpret_cast<void *>(instance_ptr.get()));
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "%s: UA_Server_setNodeContext(...) failed with %s", __PRETTY_FUNCTION__, UA_StatusCode_name(rc));
    return nullptr;
  }

  UA_ValueCallback callback;
  callback.onRead = NULL;
  callback.onWrite = led_on_write_request;
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
Led::onWriteRequest(
  UA_Server * server,
  UA_NodeId const * node_id,
  bool const value)
{
  UA_LOG_DEBUG(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: value = %d", __PRETTY_FUNCTION__, value);
  _on_set_led_state(value);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
