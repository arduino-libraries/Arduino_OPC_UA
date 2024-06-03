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

#include <Arduino.h>

#include <map>

/**************************************************************************************
 * FUNCTION DEFINITION
 **************************************************************************************/

void before_read_digital_input_1(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data);

void before_read_digital_input_2(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data);

void before_read_digital_input_3(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data);

void before_read_digital_input_4(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data);

void before_read_digital_input_5(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data);

void before_read_digital_input_6(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data);

void before_read_digital_input_7(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data);

void before_read_digital_input_8(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data);

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

typedef void (*onReadCallback)(UA_Server *server, const UA_NodeId *sessionId,
                               void *sessionContext, const UA_NodeId *nodeid,
                               void *nodeContext, const UA_NumericRange *range,
                               const UA_DataValue *value);

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

static std::map<ArduinoOptaDigitalInput, uint16_t> const DIGITAL_INPUT_TO_NUMERIC_VALUE_MAP =
  {
    {ArduinoOptaDigitalInput::I1, 1},
    {ArduinoOptaDigitalInput::I2, 2},
    {ArduinoOptaDigitalInput::I3, 3},
    {ArduinoOptaDigitalInput::I4, 4},
    {ArduinoOptaDigitalInput::I5, 5},
    {ArduinoOptaDigitalInput::I6, 6},
    {ArduinoOptaDigitalInput::I7, 7},
    {ArduinoOptaDigitalInput::I8, 8}
  };

static std::map<ArduinoOptaDigitalInput, UA_NodeId> const DIGITAL_INPUT_TO_OPCUA_NODE_ID_MAP =
  {
    {ArduinoOptaDigitalInput::I1, UA_NODEID_STRING(1, "digital-input-value-1")},
    {ArduinoOptaDigitalInput::I2, UA_NODEID_STRING(1, "digital-input-value-2")},
    {ArduinoOptaDigitalInput::I3, UA_NODEID_STRING(1, "digital-input-value-3")},
    {ArduinoOptaDigitalInput::I4, UA_NODEID_STRING(1, "digital-input-value-4")},
    {ArduinoOptaDigitalInput::I5, UA_NODEID_STRING(1, "digital-input-value-5")},
    {ArduinoOptaDigitalInput::I6, UA_NODEID_STRING(1, "digital-input-value-6")},
    {ArduinoOptaDigitalInput::I7, UA_NODEID_STRING(1, "digital-input-value-7")},
    {ArduinoOptaDigitalInput::I8, UA_NODEID_STRING(1, "digital-input-value-8")}
  };

static std::map<ArduinoOptaDigitalInput, onReadCallback> const DIGITAL_INPUT_TO_INPUT_VALUE_CALLBACK_MAP =
  {
    {ArduinoOptaDigitalInput::I1, before_read_digital_input_1},
    {ArduinoOptaDigitalInput::I2, before_read_digital_input_2},
    {ArduinoOptaDigitalInput::I3, before_read_digital_input_3},
    {ArduinoOptaDigitalInput::I4, before_read_digital_input_4},
    {ArduinoOptaDigitalInput::I5, before_read_digital_input_5},
    {ArduinoOptaDigitalInput::I6, before_read_digital_input_6},
    {ArduinoOptaDigitalInput::I7, before_read_digital_input_7},
    {ArduinoOptaDigitalInput::I8, before_read_digital_input_8}
  };

/**************************************************************************************
 * MODULE INTERNAL FUNCTION DEFINITION
 **************************************************************************************/

static PinStatus read_digital_input_pin(ArduinoOptaDigitalInput const digital_in_pin)
{
  /* Obtain the actual pin value. */
  pinMode(DIGITAL_INPUT_TO_ACTUAL_PIN_MAP.at(digital_in_pin), INPUT);
  PinStatus const in_x_val = digitalRead(DIGITAL_INPUT_TO_ACTUAL_PIN_MAP.at(digital_in_pin));
  return in_x_val;
}

static void update_digital_input_node(UA_Server * server,
                                      ArduinoOptaDigitalInput const digital_in_pin,
                                      PinStatus const in_x_val)
{
  /* Update the corresponding OPC/UA node. */
  UA_Boolean in_x_val_opcua_value = (in_x_val == HIGH) ? true : false;
  UA_Variant in_x_val_opcua_variant;
  UA_Variant_init(&in_x_val_opcua_variant);
  UA_Variant_setScalar(&in_x_val_opcua_variant, &in_x_val_opcua_value, &UA_TYPES[UA_TYPES_BOOLEAN]);
  UA_Server_writeValue(server, DIGITAL_INPUT_TO_OPCUA_NODE_ID_MAP.at(digital_in_pin), in_x_val_opcua_variant);
}

/**************************************************************************************
 * FUNCTION DEFINITION
 **************************************************************************************/

UA_StatusCode opc_ua_define_digital_input_obj(UA_Server * server,
                                              UA_NodeId const opta_node_id,
                                              UA_NodeId * opta_digital_input_node_id)
{
  UA_StatusCode rc = UA_STATUSCODE_GOOD;

  UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
  oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Digital Inputs");
  rc = UA_Server_addObjectNode(server,
                               UA_NODEID_NULL,
                               opta_node_id,
                               UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                               UA_QUALIFIEDNAME(1, "DigitalInputs"),
                               UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                               oAttr,
                               NULL,
                               opta_digital_input_node_id);
  if (UA_StatusCode_isBad(rc))
  {
    UA_ServerConfig * config = UA_Server_getConfig(server);
    UA_LOG_ERROR(config->logging,
                 UA_LOGCATEGORY_SERVER,
                 "UA_Server_addObjectNode(...) failed with %s",
                 UA_StatusCode_name(rc));
    return rc;
  }
}

UA_StatusCode opc_ua_define_digital_input(UA_Server * server,
                                          UA_NodeId const opta_digital_input_node_id,
                                          ArduinoOptaDigitalInput const digital_in_pin)
{
  UA_StatusCode rc = UA_STATUSCODE_GOOD;

  UA_VariableAttributes digital_input_value_attr = UA_VariableAttributes_default;
  UA_Boolean digital_input_value = true;
  UA_Variant_setScalar(&digital_input_value_attr.value, &digital_input_value, &UA_TYPES[UA_TYPES_BOOLEAN]);

  char digital_input_value_display_name[32] = {0};
  snprintf(digital_input_value_display_name, sizeof(digital_input_value_display_name), "Digital Input %d Value", DIGITAL_INPUT_TO_NUMERIC_VALUE_MAP.at(digital_in_pin));

  digital_input_value_attr.displayName = UA_LOCALIZEDTEXT("en-US", digital_input_value_display_name);
  digital_input_value_attr.accessLevel = UA_ACCESSLEVELMASK_READ;

  rc = UA_Server_addVariableNode(server,
                                 DIGITAL_INPUT_TO_OPCUA_NODE_ID_MAP.at(digital_in_pin),
                                 opta_digital_input_node_id,
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                 UA_QUALIFIEDNAME(1, "Value"),
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                 digital_input_value_attr,
                                 NULL,
                                 NULL);
  if (UA_StatusCode_isBad(rc))
  {
    UA_ServerConfig * config = UA_Server_getConfig(server);
    UA_LOG_ERROR(config->logging,
                 UA_LOGCATEGORY_SERVER,
                 "UA_Server_addVariableNode(..., \"Value\", ...) failed with %s",
                 UA_StatusCode_name(rc));
    return rc;
  }

  UA_ValueCallback callback;
  callback.onRead = DIGITAL_INPUT_TO_INPUT_VALUE_CALLBACK_MAP.at(digital_in_pin);
  callback.onWrite = NULL;
  rc = UA_Server_setVariableNode_valueCallback(server,
                                               DIGITAL_INPUT_TO_OPCUA_NODE_ID_MAP.at(digital_in_pin),
                                               callback);
  if (UA_StatusCode_isBad(rc))
  {
    UA_ServerConfig * config = UA_Server_getConfig(server);
    UA_LOG_ERROR(config->logging,
                 UA_LOGCATEGORY_SERVER,
                 "UA_Server_setVariableNode_valueCallback(..., \"%d\", ...) failed with %s",
                 DIGITAL_INPUT_TO_NUMERIC_VALUE_MAP.at(digital_in_pin),
                 UA_StatusCode_name(rc));
    return rc;
  }

  return UA_STATUSCODE_GOOD;
}

void before_read_digital_input_1(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data)
{
  ArduinoOptaDigitalInput const digital_in_pin = ArduinoOptaDigitalInput::I1;
  PinStatus const in_x_val = read_digital_input_pin(digital_in_pin);
  update_digital_input_node(server, digital_in_pin, in_x_val);
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"before_read_digital_input_1\" was called: %d", in_x_val);
}

void before_read_digital_input_2(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data)
{
  ArduinoOptaDigitalInput const digital_in_pin = ArduinoOptaDigitalInput::I2;
  PinStatus const in_x_val = read_digital_input_pin(digital_in_pin);
  update_digital_input_node(server, digital_in_pin, in_x_val);
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"before_read_digital_input_2\" was called: %d", in_x_val);
}

void before_read_digital_input_3(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data)
{
  ArduinoOptaDigitalInput const digital_in_pin = ArduinoOptaDigitalInput::I3;
  PinStatus const in_x_val = read_digital_input_pin(digital_in_pin);
  update_digital_input_node(server, digital_in_pin, in_x_val);
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"before_read_digital_input_3\" was called: %d", in_x_val);
}

void before_read_digital_input_4(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data)
{
  ArduinoOptaDigitalInput const digital_in_pin = ArduinoOptaDigitalInput::I4;
  PinStatus const in_x_val = read_digital_input_pin(digital_in_pin);
  update_digital_input_node(server, digital_in_pin, in_x_val);
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"before_read_digital_input_4\" was called: %d", in_x_val);
}

void before_read_digital_input_5(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data)
{
  ArduinoOptaDigitalInput const digital_in_pin = ArduinoOptaDigitalInput::I5;
  PinStatus const in_x_val = read_digital_input_pin(digital_in_pin);
  update_digital_input_node(server, digital_in_pin, in_x_val);
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"before_read_digital_input_5\" was called: %d", in_x_val);
}

void before_read_digital_input_6(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data)
{
  ArduinoOptaDigitalInput const digital_in_pin = ArduinoOptaDigitalInput::I6;
  PinStatus const in_x_val = read_digital_input_pin(digital_in_pin);
  update_digital_input_node(server, digital_in_pin, in_x_val);
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"before_read_digital_input_6\" was called: %d", in_x_val);
}

void before_read_digital_input_7(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data)
{
  ArduinoOptaDigitalInput const digital_in_pin = ArduinoOptaDigitalInput::I7;
  PinStatus const in_x_val = read_digital_input_pin(digital_in_pin);
  update_digital_input_node(server, digital_in_pin, in_x_val);
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"before_read_digital_input_7\" was called: %d", in_x_val);
}

void before_read_digital_input_8(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data)
{
  ArduinoOptaDigitalInput const digital_in_pin = ArduinoOptaDigitalInput::I8;
  PinStatus const in_x_val = read_digital_input_pin(digital_in_pin);
  update_digital_input_node(server, digital_in_pin, in_x_val);
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"before_read_digital_input_8\" was called: %d", in_x_val);
}
