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

#include "PwmOutput.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * FUNCTION DEFINITION
 **************************************************************************************/

static void
pwm_output_on_write_request_pwm_period(
  UA_Server *server,
  const UA_NodeId *sessionId,
  void *sessionContext,
  const UA_NodeId *nodeid,
  void *nodeContext,
  const UA_NumericRange *range,
  const UA_DataValue *data)
{
  PwmOutput * this_ptr = reinterpret_cast<PwmOutput *>(nodeContext);
  uint32_t const pwm_period_ms = *(UA_UInt32 *)(data->value.data);
  this_ptr->onWriteRequestPwmPeriod(server, nodeid, pwm_period_ms);
}

static void
pwm_output_on_write_request_pwm_pulse_width(
  UA_Server *server,
  const UA_NodeId *sessionId,
  void *sessionContext,
  const UA_NodeId *nodeid,
  void *nodeContext,
  const UA_NumericRange *range,
  const UA_DataValue *data)
{
  PwmOutput * this_ptr = reinterpret_cast<PwmOutput *>(nodeContext);
  uint32_t const pwm_pulse_width_ms = *(UA_UInt32 *)(data->value.data);
  this_ptr->onWriteRequestPwmPulseWidth(server, nodeid, pwm_pulse_width_ms);
}

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

PwmOutput::PwmOutput(
  UA_NodeId const & node_id,
  SetPwmFunc const set_pwm_func)
  : _node_id{node_id}
  , _set_pwm_func{set_pwm_func}
  , _pwm_period_ms{0}
  , _pwm_pulse_width_ms{0}
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

PwmOutput::SharedPtr
PwmOutput::create(
  UA_Server * server,
  UA_NodeId const & parent_node_id,
  const char * display_name,
  SetPwmFunc const set_pwm_func)
{
  UA_StatusCode rc = UA_STATUSCODE_GOOD;

  UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
  oAttr.displayName = UA_LOCALIZEDTEXT("en-US", (char *)display_name);
  UA_NodeId pwm_obj_node_id;
  rc = UA_Server_addObjectNode(server,
                               UA_NODEID_NULL,
                               parent_node_id,
                               UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                               UA_QUALIFIEDNAME(1, (char *)display_name),
                               UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                               oAttr,
                               NULL,
                               &pwm_obj_node_id);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "%s: UA_Server_addObjectNode(...) failed with %s", __PRETTY_FUNCTION__, UA_StatusCode_name(rc));
    return nullptr;
  }

  UA_VariableAttributes pwm_out_period_value_attr = UA_VariableAttributes_default;

  UA_Boolean pwm_output_period_value = 0;
  UA_Variant_setScalar(&pwm_out_period_value_attr.value, &pwm_output_period_value, &UA_TYPES[UA_TYPES_UINT32]);

  pwm_out_period_value_attr.displayName = UA_LOCALIZEDTEXT("en-US", (char *)display_name);
  pwm_out_period_value_attr.dataType = UA_TYPES[UA_TYPES_UINT32].typeId;
  pwm_out_period_value_attr.accessLevel =
    UA_ACCESSLEVELMASK_READ |
    UA_ACCESSLEVELMASK_WRITE | UA_ACCESSLEVELMASK_STATUSWRITE |
    UA_ACCESSLEVELMASK_TIMESTAMPWRITE; /* Status and timestamp write access necessary for opcua-client. */

  UA_NodeId node_id;
  rc = UA_Server_addVariableNode(server,
                                 UA_NODEID_NULL,
                                 pwm_obj_node_id,
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                 UA_QUALIFIEDNAME(1, "Value"),
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                 pwm_out_period_value_attr,
                                 NULL,
                                 &node_id);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "%s: failed with %s", __PRETTY_FUNCTION__, UA_StatusCode_name(rc));
    return nullptr;
  }

  /* Create an instance of AnalogOutput here. */
  auto const instance_ptr = std::make_shared<PwmOutput>(node_id, set_pwm_func);

  rc = UA_Server_setNodeContext(server, node_id, reinterpret_cast<void *>(instance_ptr.get()));
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "%s: UA_Server_setNodeContext(...) failed with %s", __PRETTY_FUNCTION__, UA_StatusCode_name(rc));
    return nullptr;
  }

  UA_ValueCallback callback;
  callback.onRead = NULL;
  callback.onWrite = pwm_output_on_write_request_pwm_period;
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
PwmOutput::onWriteRequestPwmPeriod(
  UA_Server * server,
  UA_NodeId const * node_id,
  uint32_t const pwm_period_ms)
{
  _pwm_period_ms = pwm_period_ms;
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: pwm period = %d ms", __PRETTY_FUNCTION__, _pwm_period_ms);
  _set_pwm_func(_pwm_period_ms, _pwm_pulse_width_ms);
}

void
PwmOutput::onWriteRequestPwmPulseWidth(
  UA_Server * server,
  UA_NodeId const * node_id,
  uint32_t const pwm_pulse_width_ms)
{
  _pwm_pulse_width_ms = pwm_pulse_width_ms;
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: pwm pulse width = %d ms", __PRETTY_FUNCTION__, _pwm_pulse_width_ms);
  _set_pwm_func(_pwm_period_ms, _pwm_pulse_width_ms);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
