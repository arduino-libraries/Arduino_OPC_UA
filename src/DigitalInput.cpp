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

#include "DigitalInput.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * FUNCTION DEFINITION
 **************************************************************************************/

static void digital_input_on_read_request(UA_Server *server,
                                          const UA_NodeId *sessionId,
                                          void *sessionContext,
                                          const UA_NodeId *nodeid,
                                          void *nodeContext,
                                          const UA_NumericRange *range,
                                          const UA_DataValue *data)
{
  DigitalInput * this_ptr = reinterpret_cast<DigitalInput *>(nodeContext);
  this_ptr->onReadRequest(server, nodeid);
}

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

DigitalInput::DigitalInput(UA_NodeId const & node_id, OnReadRequestFunc const on_read_request)
: _node_id{node_id}
, _on_read_request{on_read_request}
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

DigitalInput::SharedPtr DigitalInput::create(UA_Server * server,
                                             UA_NodeId const & parent_node_id,
                                             const char * display_name,
                                             OnReadRequestFunc const on_read_request)
{
  UA_VariableAttributes digital_input_value_attr = UA_VariableAttributes_default;

  /* Obtain the current value of the input pin. */
  PinStatus const in_x_val = on_read_request();
  UA_Boolean digital_input_value = (in_x_val == HIGH) ? true : false;
  UA_Variant_setScalar(&digital_input_value_attr.value, &digital_input_value, &UA_TYPES[UA_TYPES_BOOLEAN]);

  digital_input_value_attr.displayName = UA_LOCALIZEDTEXT("en-US", (char *)display_name);
  digital_input_value_attr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId;
  digital_input_value_attr.accessLevel = UA_ACCESSLEVELMASK_READ;

  /* Add the variable node. */
  UA_StatusCode rc = UA_STATUSCODE_GOOD;
  UA_NodeId node_id;
  rc = UA_Server_addVariableNode(server,
                                 UA_NODEID_NULL,
                                 parent_node_id,
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                 UA_QUALIFIEDNAME(1, "Value"),
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                 digital_input_value_attr,
                                 NULL,
                                 &node_id);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "DigitalInput::create: UA_Server_addVariableNode(...) failed with %s",
                 UA_StatusCode_name(rc));
    return nullptr;
  }

  /* Create an instance of DigitalInput here. */
  auto const instance_ptr = std::make_shared<DigitalInput>(node_id, on_read_request);

  rc = UA_Server_setNodeContext(server, node_id, reinterpret_cast<void *>(instance_ptr.get()));
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "DigitalInput::create: UA_Server_setNodeContext(...) failed with %s",
                 UA_StatusCode_name(rc));
    return nullptr;
  }

  UA_ValueCallback callback;
  callback.onRead = digital_input_on_read_request;
  callback.onWrite = NULL;
  rc = UA_Server_setVariableNode_valueCallback(server, node_id, callback);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "DigitalInput::create: UA_Server_setVariableNode_valueCallback(...) failed with %s",
                 UA_StatusCode_name(rc));
    return nullptr;
  }

  return instance_ptr;
}

void DigitalInput::onReadRequest(UA_Server * server, UA_NodeId const * node_id)
{
  /* Obtain the value of the digital input pin. */
  PinStatus const in_x_val = _on_read_request();
  /* Update the variable node. */
  UA_Boolean in_x_val_opcua_value = (in_x_val == HIGH) ? true : false;
  UA_Variant in_x_val_opcua_variant;
  UA_Variant_init(&in_x_val_opcua_variant);
  UA_Variant_setScalar(&in_x_val_opcua_variant, &in_x_val_opcua_value, &UA_TYPES[UA_TYPES_BOOLEAN]);
  UA_Server_writeValue(server, *node_id, in_x_val_opcua_variant);
  /* Some debug output. */
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "DigitalInput::onReadRequest: value = %d", in_x_val);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
