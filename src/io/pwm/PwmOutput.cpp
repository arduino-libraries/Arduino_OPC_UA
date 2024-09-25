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
pwm_output_on_read_request_pwm_period(
  UA_Server *server,
  const UA_NodeId *sessionId,
  void *sessionContext,
  const UA_NodeId *nodeid,
  void *nodeContext,
  const UA_NumericRange *range,
  const UA_DataValue *data)
{
  PwmOutput * this_ptr = reinterpret_cast<PwmOutput *>(nodeContext);
  this_ptr->onReadRequestPwmPeriod(server, nodeid);
}

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
  uint32_t const pwm_period_us = *(UA_UInt32 *)(data->value.data);
  this_ptr->onWriteRequestPwmPeriod(server, nodeid, pwm_period_us);
}

static void
pwm_output_on_read_request_pwm_pulse_width(
  UA_Server *server,
  const UA_NodeId *sessionId,
  void *sessionContext,
  const UA_NodeId *nodeid,
  void *nodeContext,
  const UA_NumericRange *range,
  const UA_DataValue *data)
{
  PwmOutput * this_ptr = reinterpret_cast<PwmOutput *>(nodeContext);
  this_ptr->onReadRequestPwmPulseWidth(server, nodeid);
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
  uint32_t const pwm_pulse_width_us = *(UA_UInt32 *)(data->value.data);
  this_ptr->onWriteRequestPwmPulseWidth(server, nodeid, pwm_pulse_width_us);
}

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

PwmOutput::PwmOutput(
  UA_NodeId const & pwm_period_node_id,
  UA_NodeId const & pwm_pulse_width_node_id,
  SetPwmFunc const set_pwm_func,
  GetPwmPeriodFunc const get_pwm_period_func,
  GetPwmPulseWidthFunc const get_pwm_pulse_width_func)
  : _pwm_period_node_id{pwm_period_node_id}
  , _pwm_pulse_width_node_id{pwm_pulse_width_node_id}
  , _set_pwm_func{set_pwm_func}
  , _get_pwm_period_func{get_pwm_period_func}
  , _get_pwm_pulse_width_func{get_pwm_pulse_width_func}
  , _pwm_period_us{0}
  , _pwm_pulse_width_us{0}
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
  SetPwmFunc const set_pwm_func,
  GetPwmPeriodFunc const get_pwm_period_func,
  GetPwmPulseWidthFunc const get_pwm_pulse_width_func)
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

  UA_Boolean pwm_output_period_value = get_pwm_period_func();
  UA_Variant_setScalar(&pwm_out_period_value_attr.value, &pwm_output_period_value, &UA_TYPES[UA_TYPES_UINT32]);

  pwm_out_period_value_attr.displayName = UA_LOCALIZEDTEXT("en-US", "PWM Period / us");
  pwm_out_period_value_attr.dataType = UA_TYPES[UA_TYPES_UINT32].typeId;
  pwm_out_period_value_attr.accessLevel =
    UA_ACCESSLEVELMASK_READ |
    UA_ACCESSLEVELMASK_WRITE | UA_ACCESSLEVELMASK_STATUSWRITE |
    UA_ACCESSLEVELMASK_TIMESTAMPWRITE; /* Status and timestamp write access necessary for opcua-client. */

  UA_NodeId pwm_period_node_id;
  rc = UA_Server_addVariableNode(server,
                                 UA_NODEID_NULL,
                                 pwm_obj_node_id,
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                 UA_QUALIFIEDNAME(1, "pwm_period_us"),
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                 pwm_out_period_value_attr,
                                 NULL,
                                 &pwm_period_node_id);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "%s: failed with %s", __PRETTY_FUNCTION__, UA_StatusCode_name(rc));
    return nullptr;
  }

  UA_ValueCallback pwm_period_callback;
  pwm_period_callback.onRead = pwm_output_on_read_request_pwm_period;
  pwm_period_callback.onWrite = pwm_output_on_write_request_pwm_period;
  rc = UA_Server_setVariableNode_valueCallback(server, pwm_period_node_id, pwm_period_callback);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "%s: UA_Server_setVariableNode_valueCallback(pwm_period_node_id, ...) failed with %s", __PRETTY_FUNCTION__, UA_StatusCode_name(rc));
    return nullptr;
  }

  UA_VariableAttributes pwm_out_pulse_width_value_attr = UA_VariableAttributes_default;

  UA_Boolean pwm_output_pulse_width_value = get_pwm_pulse_width_func();
  UA_Variant_setScalar(&pwm_out_pulse_width_value_attr.value, &pwm_output_pulse_width_value, &UA_TYPES[UA_TYPES_UINT32]);

  pwm_out_pulse_width_value_attr.displayName = UA_LOCALIZEDTEXT("en-US", "PWM Pulse Width / us");
  pwm_out_pulse_width_value_attr.dataType = UA_TYPES[UA_TYPES_UINT32].typeId;
  pwm_out_pulse_width_value_attr.accessLevel =
    UA_ACCESSLEVELMASK_READ |
    UA_ACCESSLEVELMASK_WRITE | UA_ACCESSLEVELMASK_STATUSWRITE |
    UA_ACCESSLEVELMASK_TIMESTAMPWRITE; /* Status and timestamp write access necessary for opcua-client. */

  UA_NodeId pwm_pulse_width_node_id;
  rc = UA_Server_addVariableNode(server,
                                 UA_NODEID_NULL,
                                 pwm_obj_node_id,
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                 UA_QUALIFIEDNAME(1, "pwm_pulse_width_us"),
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                 pwm_out_pulse_width_value_attr,
                                 NULL,
                                 &pwm_pulse_width_node_id);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "%s: failed with %s", __PRETTY_FUNCTION__, UA_StatusCode_name(rc));
    return nullptr;
  }

  UA_ValueCallback pwm_pulse_width_callback;
  pwm_pulse_width_callback.onRead = pwm_output_on_read_request_pwm_pulse_width;
  pwm_pulse_width_callback.onWrite = pwm_output_on_write_request_pwm_pulse_width;
  rc = UA_Server_setVariableNode_valueCallback(server, pwm_pulse_width_node_id, pwm_pulse_width_callback);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "%s: UA_Server_setVariableNode_valueCallback(pwm_pulse_width_node_id, ...) failed with %s", __PRETTY_FUNCTION__, UA_StatusCode_name(rc));
    return nullptr;
  }

  auto const instance_ptr = std::make_shared<PwmOutput>(pwm_period_node_id, pwm_pulse_width_node_id, set_pwm_func, get_pwm_period_func, get_pwm_pulse_width_func);

  rc = UA_Server_setNodeContext(server, pwm_period_node_id, reinterpret_cast<void *>(instance_ptr.get()));
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "%s: UA_Server_setNodeContext(pwm_period_node_id, ...) failed with %s", __PRETTY_FUNCTION__, UA_StatusCode_name(rc));
    return nullptr;
  }

  rc = UA_Server_setNodeContext(server, pwm_pulse_width_node_id, reinterpret_cast<void *>(instance_ptr.get()));
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "%s: UA_Server_setNodeContext(pwm_pulse_width_node_id, ...) failed with %s", __PRETTY_FUNCTION__, UA_StatusCode_name(rc));
    return nullptr;
  }

  return instance_ptr;
}

void
PwmOutput::onReadRequestPwmPeriod(
  UA_Server * server,
  UA_NodeId const * node_id)
{
  /* Obtain the value of the analog input pin. */
  _pwm_period_us = _get_pwm_period_func();
  /* Update the variable node. */
  UA_UInt32 in_x_val_opcua_value = _pwm_period_us;
  UA_Variant in_x_val_opcua_variant;
  UA_Variant_init(&in_x_val_opcua_variant);
  UA_Variant_setScalar(&in_x_val_opcua_variant, &in_x_val_opcua_value, &UA_TYPES[UA_TYPES_UINT32]);
  UA_Server_writeValue(server, *node_id, in_x_val_opcua_variant);
  /* Some debug output. */
  UA_LOG_DEBUG(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: pwm period = %d us", __PRETTY_FUNCTION__, _pwm_period_us);
}

void
PwmOutput::onWriteRequestPwmPeriod(
  UA_Server * server,
  UA_NodeId const * pwm_period_node_id,
  uint32_t const pwm_period_us)
{
  _pwm_period_us = pwm_period_us;
  UA_LOG_DEBUG(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: pwm period = %d us, pulse width = %d us", __PRETTY_FUNCTION__, _pwm_period_us, _pwm_pulse_width_us);
  _set_pwm_func(_pwm_period_us, _pwm_pulse_width_us);
}

void
PwmOutput::onReadRequestPwmPulseWidth(
  UA_Server * server,
  UA_NodeId const * node_id)
{
  /* Obtain the value of the analog input pin. */
  _pwm_pulse_width_us = _get_pwm_pulse_width_func();
  /* Update the variable node. */
  UA_UInt32 in_x_val_opcua_value = _pwm_pulse_width_us;
  UA_Variant in_x_val_opcua_variant;
  UA_Variant_init(&in_x_val_opcua_variant);
  UA_Variant_setScalar(&in_x_val_opcua_variant, &in_x_val_opcua_value, &UA_TYPES[UA_TYPES_UINT32]);
  UA_Server_writeValue(server, *node_id, in_x_val_opcua_variant);
  /* Some debug output. */
  UA_LOG_DEBUG(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: pwm pulse width = %d us", __PRETTY_FUNCTION__, _pwm_pulse_width_us);
}

void
PwmOutput::onWriteRequestPwmPulseWidth(
  UA_Server * server,
  UA_NodeId const * pwm_pulse_width_node_id,
  uint32_t const pwm_pulse_width_us)
{
  _pwm_pulse_width_us = pwm_pulse_width_us;
  UA_LOG_DEBUG(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: pwm period = %d us, pulse width = %d us", __PRETTY_FUNCTION__, _pwm_period_us, _pwm_pulse_width_us);
  _set_pwm_func(_pwm_period_us, _pwm_pulse_width_us);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
