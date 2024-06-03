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

#include <map>

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static std::map<ArduinoOptaDigitalInput, pin_size_t> const DIGITAL_INPUT_TO_ACTUAL_PIN_MAP =
  {
    {ArduinoOptaDigitalInput::I1, A0},
    {ArduinoOptaDigitalInput::I2, A1},
    {ArduinoOptaDigitalInput::I3, A2},
    {ArduinoOptaDigitalInput::I4, A3},
    {ArduinoOptaDigitalInput::I5, A4},
    {ArduinoOptaDigitalInput::I6, A5},
    {ArduinoOptaDigitalInput::I7, A6},
    {ArduinoOptaDigitalInput::I8, A7}
  };

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

DigitalInput::DigitalInput()
: _is_initialized{false}
{
  /* Nothing happens here. */
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

UA_StatusCode DigitalInput::begin(UA_Server * server,
                                  UA_NodeId const parent_node_id)
{
  UA_StatusCode rc = UA_STATUSCODE_GOOD;

  UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
  oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Digital Inputs");
  rc = UA_Server_addObjectNode(server,
                               UA_NODEID_NULL,
                               parent_node_id,
                               UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                               UA_QUALIFIEDNAME(1, "DigitalInputs"),
                               UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                               oAttr,
                               NULL,
                               &_digital_input_node_id);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,  "DigitalInput::begin: UA_Server_addObjectNode(...) failed with %s", UA_StatusCode_name(rc));
    return rc;
  }

  _is_initialized = true;
  return rc;
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

UA_StatusCode DigitalInput::add_digital_input_pin(UA_Server * server,
                                                  UA_NodeId const digital_input_pin_node_id,
                                                  char const * digital_input_pin_display_name,
                                                  onReadRequestFunc const on_read_request)
{
  if (!_is_initialized)
    return UA_STATUSCODE_BAD;

  UA_StatusCode rc = UA_STATUSCODE_GOOD;

  UA_VariableAttributes digital_input_value_attr = UA_VariableAttributes_default;
  UA_Boolean digital_input_value = true;
  UA_Variant_setScalar(&digital_input_value_attr.value, &digital_input_value, &UA_TYPES[UA_TYPES_BOOLEAN]);

  digital_input_value_attr.displayName = UA_LOCALIZEDTEXT("en-US", (char *)digital_input_pin_display_name);
  digital_input_value_attr.accessLevel = UA_ACCESSLEVELMASK_READ;

  rc = UA_Server_addVariableNode(server,
                                 digital_input_pin_node_id,
                                 _digital_input_node_id,
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                 UA_QUALIFIEDNAME(1, "Value"),
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                 digital_input_value_attr,
                                 NULL,
                                 NULL);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "DigitalInput::add_digital_input_pin: UA_Server_addVariableNode(...) failed with %s",
                 UA_StatusCode_name(rc));
    return rc;
  }

  UA_ValueCallback callback;
  callback.onRead = on_read_request;
  callback.onWrite = NULL;
  rc = UA_Server_setVariableNode_valueCallback(server, digital_input_pin_node_id, callback);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "DigitalInput::add_digital_input_pin: UA_Server_setVariableNode_valueCallback(...) failed with %s",
                 UA_StatusCode_name(rc));
    return rc;
  }

  return UA_STATUSCODE_GOOD;
}

/**************************************************************************************
 * MODULE INTERNAL FUNCTION DEFINITION
 **************************************************************************************/

static void read_digital_input_pin(ArduinoOptaDigitalInput const digital_in_pin, PinStatus & in_x_val)
{
  /* Obtain the actual pin value. */
  pinMode(DIGITAL_INPUT_TO_ACTUAL_PIN_MAP.at(digital_in_pin), INPUT);
  in_x_val = digitalRead(DIGITAL_INPUT_TO_ACTUAL_PIN_MAP.at(digital_in_pin));
}

static void update_digital_input_node(UA_Server * server,
                                      UA_NodeId const digital_input_pin_node_id,
                                      PinStatus const in_x_val)
{
  /* Update the corresponding OPC/UA node. */
  UA_Boolean in_x_val_opcua_value = (in_x_val == HIGH) ? true : false;
  UA_Variant in_x_val_opcua_variant;
  UA_Variant_init(&in_x_val_opcua_variant);
  UA_Variant_setScalar(&in_x_val_opcua_variant, &in_x_val_opcua_value, &UA_TYPES[UA_TYPES_BOOLEAN]);
  UA_Server_writeValue(server, digital_input_pin_node_id, in_x_val_opcua_variant);
}

/**************************************************************************************
 * FUNCTION DEFINITION
 **************************************************************************************/

void on_read_request_opta_digital_input_1(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data)
{
  ArduinoOptaDigitalInput const digital_in_pin = ArduinoOptaDigitalInput::I1;
  PinStatus in_x_val = LOW;
  read_digital_input_pin(digital_in_pin, in_x_val);
  update_digital_input_node(server, UA_NODEID_STRING(1, "digital-input-value-1"), in_x_val);
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"on_read_request_opta_digital_input_1\" was called: %d", in_x_val);
}

void on_read_request_opta_digital_input_2(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data)
{
  ArduinoOptaDigitalInput const digital_in_pin = ArduinoOptaDigitalInput::I2;
  PinStatus in_x_val = LOW;
  read_digital_input_pin(digital_in_pin, in_x_val);
  update_digital_input_node(server, UA_NODEID_STRING(1, "digital-input-value-2"), in_x_val);
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"on_read_request_opta_digital_input_2\" was called: %d", in_x_val);
}

void on_read_request_opta_digital_input_3(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data)
{
  ArduinoOptaDigitalInput const digital_in_pin = ArduinoOptaDigitalInput::I3;
  PinStatus in_x_val = LOW;
  read_digital_input_pin(digital_in_pin, in_x_val);
  update_digital_input_node(server, UA_NODEID_STRING(1, "digital-input-value-3"), in_x_val);
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"on_read_request_opta_digital_input_3\" was called: %d", in_x_val);
}

void on_read_request_opta_digital_input_4(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data)
{
  ArduinoOptaDigitalInput const digital_in_pin = ArduinoOptaDigitalInput::I4;
  PinStatus in_x_val = LOW;
  read_digital_input_pin(digital_in_pin, in_x_val);
  update_digital_input_node(server, UA_NODEID_STRING(1, "digital-input-value-4"), in_x_val);
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"on_read_request_opta_digital_input_4\" was called: %d", in_x_val);
}

void on_read_request_opta_digital_input_5(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data)
{
  ArduinoOptaDigitalInput const digital_in_pin = ArduinoOptaDigitalInput::I5;
  PinStatus in_x_val = LOW;
  read_digital_input_pin(digital_in_pin, in_x_val);
  update_digital_input_node(server, UA_NODEID_STRING(1, "digital-input-value-5"), in_x_val);
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"on_read_request_opta_digital_input_5\" was called: %d", in_x_val);
}

void on_read_request_opta_digital_input_6(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data)
{
  ArduinoOptaDigitalInput const digital_in_pin = ArduinoOptaDigitalInput::I6;
  PinStatus in_x_val = LOW;
  read_digital_input_pin(digital_in_pin, in_x_val);
  update_digital_input_node(server, UA_NODEID_STRING(1, "digital-input-value-6"), in_x_val);
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"on_read_request_opta_digital_input_6\" was called: %d", in_x_val);
}

void on_read_request_opta_digital_input_7(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data)
{
  ArduinoOptaDigitalInput const digital_in_pin = ArduinoOptaDigitalInput::I7;
  PinStatus in_x_val = LOW;
  read_digital_input_pin(digital_in_pin, in_x_val);
  update_digital_input_node(server, UA_NODEID_STRING(1, "digital-input-value-7"), in_x_val);
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"on_read_request_opta_digital_input_7\" was called: %d", in_x_val);
}

void on_read_request_opta_digital_input_8(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data)
{
  ArduinoOptaDigitalInput const digital_in_pin = ArduinoOptaDigitalInput::I8;
  PinStatus in_x_val = LOW;
  read_digital_input_pin(digital_in_pin, in_x_val);
  update_digital_input_node(server, UA_NODEID_STRING(1, "digital-input-value-8"), in_x_val);
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"on_read_request_opta_digital_input_8\" was called: %d", in_x_val);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
