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

UA_StatusCode opc_ua_define_digital_input(UA_Server *server,
                                          UA_NodeId const opta_digital_input_node_id,
                                          unsigned int const digital_input_num,
                                          onReadCallback before_read_digital)
{
  UA_StatusCode rc = UA_STATUSCODE_GOOD;

  UA_VariableAttributes digital_input_value_attr = UA_VariableAttributes_default;
  UA_Boolean digital_input_value = true;
  UA_Variant_setScalar(&digital_input_value_attr.value, &digital_input_value, &UA_TYPES[UA_TYPES_BOOLEAN]);

  char digital_input_value_display_name[32] = {0};
  snprintf(digital_input_value_display_name, sizeof(digital_input_value_display_name), "Digital Input %d Value", digital_input_num);

  digital_input_value_attr.displayName = UA_LOCALIZEDTEXT("en-US", digital_input_value_display_name);
  digital_input_value_attr.accessLevel = UA_ACCESSLEVELMASK_READ;

  char digital_input_value_node_id[32] = {0};
  snprintf(digital_input_value_node_id, sizeof(digital_input_value_node_id), "digital-input-value-%d", digital_input_num);

  rc = UA_Server_addVariableNode(server,
                                 UA_NODEID_STRING(1, digital_input_value_node_id),
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
  callback.onRead = before_read_digital;
  callback.onWrite = NULL;
  rc = UA_Server_setVariableNode_valueCallback(server,
                                               UA_NODEID_STRING(1, digital_input_value_node_id),
                                               callback);
  if (UA_StatusCode_isBad(rc))
  {
    UA_ServerConfig * config = UA_Server_getConfig(server);
    UA_LOG_ERROR(config->logging,
                 UA_LOGCATEGORY_SERVER,
                 "UA_Server_setVariableNode_valueCallback(..., \"%d\", ...) failed with %s",
                 digital_input_num,
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
  /* TODO */
  /* Write some debug output. */
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"before_read_digital_input_1\" was called");
}

void before_read_digital_input_2(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data)
{
  /* TODO */
  /* Write some debug output. */
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"before_read_digital_input_2\" was called");
}

void before_read_digital_input_3(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data)
{
  /* TODO */
  /* Write some debug output. */
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"before_read_digital_input_3\" was called");
}

void before_read_digital_input_4(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data)
{
  /* TODO */
  /* Write some debug output. */
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"before_read_digital_input_4\" was called");
}

void before_read_digital_input_5(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data)
{
  /* TODO */
  /* Write some debug output. */
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"before_read_digital_input_5\" was called");
}

void before_read_digital_input_6(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data)
{
  /* TODO */
  /* Write some debug output. */
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"before_read_digital_input_6\" was called");
}

void before_read_digital_input_7(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data)
{
  /* TODO */
  /* Write some debug output. */
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"before_read_digital_input_7\" was called");
}

void before_read_digital_input_8(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data)
{
  /* TODO */
  /* Write some debug output. */
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"before_read_digital_input_8\" was called");
}
