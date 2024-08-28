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

#include "AnalogOutput.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * FUNCTION DEFINITION
 **************************************************************************************/

static void analog_output_on_write_request(UA_Server *server,
                                           const UA_NodeId *sessionId,
                                           void *sessionContext,
                                           const UA_NodeId *nodeid,
                                           void *nodeContext,
                                           const UA_NumericRange *range,
                                           const UA_DataValue *data)
{
  AnalogOutput * this_ptr = reinterpret_cast<AnalogOutput *>(nodeContext);
  bool const voltage = *(UA_Float *)(data->value.data);
  this_ptr->onWriteRequest(server, nodeid, voltage);
}

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

AnalogOutput::AnalogOutput(UA_NodeId const & node_id, OnWriteRequestFunc const on_write_request)
: _node_id{node_id}
, _on_write_request{on_write_request}
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

AnalogOutput::SharedPtr AnalogOutput::create(UA_Server * server,
                                             UA_NodeId const & parent_node_id,
                                             const char * display_name,
                                             OnWriteRequestFunc const on_write_request)
{
  UA_StatusCode rc = UA_STATUSCODE_GOOD;

  UA_VariableAttributes analog_output_value_attr = UA_VariableAttributes_default;

  UA_Boolean analog_output_value = 0.;
  UA_Variant_setScalar(&analog_output_value_attr.value, &analog_output_value, &UA_TYPES[UA_TYPES_FLOAT]);

  analog_output_value_attr.displayName = UA_LOCALIZEDTEXT("en-US", (char *)display_name);
  analog_output_value_attr.dataType = UA_TYPES[UA_TYPES_FLOAT].typeId;
  analog_output_value_attr.accessLevel =
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
                                 analog_output_value_attr,
                                 NULL,
                                 &node_id);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "AnalogOutput::create: UA_Server_addVariableNode(...) failed with %s", UA_StatusCode_name(rc));
    return nullptr;
  }

  /* Create an instance of AnalogOutput here. */
  auto const instance_ptr = std::make_shared<AnalogOutput>(node_id, on_write_request);

  rc = UA_Server_setNodeContext(server, node_id, reinterpret_cast<void *>(instance_ptr.get()));
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "AnalogOutput::create: UA_Server_setNodeContext(...) failed with %s",
                 UA_StatusCode_name(rc));
    return nullptr;
  }

  UA_ValueCallback callback;
  callback.onRead = NULL;
  callback.onWrite = analog_output_on_write_request;
  rc = UA_Server_setVariableNode_valueCallback(server, node_id, callback);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "AnalogOutput::create: UA_Server_setVariableNode_valueCallback(...) failed with %s",
                 UA_StatusCode_name(rc));
    return nullptr;
  }

  return instance_ptr;
}

void AnalogOutput::onWriteRequest(UA_Server * server, UA_NodeId const * node_id, float const voltage)
{
  /* Some debug output. */
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "AnalogOutput::onWriteRequest: voltage = %0.2f", voltage);
  _on_write_request(voltage);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
