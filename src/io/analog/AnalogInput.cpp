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

#include "AnalogInput.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * FUNCTION DEFINITION
 **************************************************************************************/

static void
analog_input_on_read_request(
  UA_Server *server,
  const UA_NodeId *sessionId,
  void *sessionContext,
  const UA_NodeId *nodeid,
  void *nodeContext,
  const UA_NumericRange *range,
  const UA_DataValue *data)
{
  AnalogInput * this_ptr = reinterpret_cast<AnalogInput *>(nodeContext);
  this_ptr->onReadRequest(server, nodeid);
}

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

AnalogInput::AnalogInput(
  UA_NodeId const & node_id,
  OnReadRequestFunc const on_read_request)
: _node_id{node_id}
, _on_read_request{on_read_request}
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

AnalogInput::SharedPtr
AnalogInput::create(
  UA_Server * server,
  UA_NodeId const & parent_node_id,
  const char * display_name,
  OnReadRequestFunc const on_read_request)
{
  UA_VariableAttributes analog_input_value_attr = UA_VariableAttributes_default;

  /* Obtain the current value of the input pin. */
  UA_Float analog_input_value = on_read_request();
  UA_Variant_setScalar(&analog_input_value_attr.value, &analog_input_value, &UA_TYPES[UA_TYPES_FLOAT]);

  analog_input_value_attr.displayName = UA_LOCALIZEDTEXT("en-US", (char *)display_name);
  analog_input_value_attr.dataType = UA_TYPES[UA_TYPES_FLOAT].typeId;
  analog_input_value_attr.accessLevel = UA_ACCESSLEVELMASK_READ;

  /* Add the variable node. */
  UA_StatusCode rc = UA_STATUSCODE_GOOD;
  UA_NodeId node_id;
  rc = UA_Server_addVariableNode(server,
                                 UA_NODEID_NULL,
                                 parent_node_id,
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                 UA_QUALIFIEDNAME(1, "Value"),
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                 analog_input_value_attr,
                                 NULL,
                                 &node_id);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "%s: UA_Server_addVariableNode(...) failed with %s", __PRETTY_FUNCTION__, UA_StatusCode_name(rc));
    return nullptr;
  }

  /* Create an instance of AnalogInput here. */
  auto const instance_ptr = std::make_shared<AnalogInput>(node_id, on_read_request);

  rc = UA_Server_setNodeContext(server, node_id, reinterpret_cast<void *>(instance_ptr.get()));
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "%s: UA_Server_setNodeContext(...) failed with %s", __PRETTY_FUNCTION__, UA_StatusCode_name(rc));
    return nullptr;
  }

  UA_ValueCallback callback;
  callback.onRead = analog_input_on_read_request;
  callback.onWrite = NULL;
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
AnalogInput::onReadRequest(
  UA_Server * server,
  UA_NodeId const * node_id)
{
  /* Obtain the value of the analog input pin. */
  float const in_x_val = _on_read_request();
  /* Update the variable node. */
  UA_Float in_x_val_opcua_value = in_x_val;
  UA_Variant in_x_val_opcua_variant;
  UA_Variant_init(&in_x_val_opcua_variant);
  UA_Variant_setScalar(&in_x_val_opcua_variant, &in_x_val_opcua_value, &UA_TYPES[UA_TYPES_FLOAT]);
  UA_Server_writeValue(server, *node_id, in_x_val_opcua_variant);
  /* Some debug output. */
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: value = %f", __PRETTY_FUNCTION__, in_x_val);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
