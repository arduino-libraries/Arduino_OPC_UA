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

#include <Arduino.h>

/**************************************************************************************
 * FUNCTION DEFINITION
 **************************************************************************************/

UA_StatusCode opc_ua_define_relay(UA_Server * server,
                                  unsigned int const relay_num,
                                  UA_MethodCallback relay_close_func,
                                  UA_MethodCallback relay_open_func)
{
  UA_StatusCode rc = UA_STATUSCODE_GOOD;
  UA_NodeId relayId; /* get the nodeid assigned by the server */

  UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
  char object_node_relay_name[16] = {0};
  snprintf(object_node_relay_name, sizeof(object_node_relay_name), "Relay %d", relay_num);
  oAttr.displayName = UA_LOCALIZEDTEXT("en-US", object_node_relay_name);
  rc = UA_Server_addObjectNode(server,
                               UA_NODEID_NULL,
                               UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                               UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                               UA_QUALIFIEDNAME(1, "Relay 1"),
                               UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                               oAttr,
                               NULL,
                               &relayId);
  if (UA_StatusCode_isBad(rc))
  {
    UA_ServerConfig * config = UA_Server_getConfig(server);
    UA_LOG_ERROR(config->logging,
                 UA_LOGCATEGORY_SERVER,
                 "UA_Server_addObjectNode(...) failed with %s",
                 UA_StatusCode_name(rc));
    return rc;
  }

  UA_VariableAttributes mnAttr = UA_VariableAttributes_default;
  UA_String manufacturerName = UA_STRING("Arduino");
  UA_Variant_setScalar(&mnAttr.value, &manufacturerName, &UA_TYPES[UA_TYPES_STRING]);
  mnAttr.displayName = UA_LOCALIZEDTEXT("en-US", "ManufacturerName");
  rc = UA_Server_addVariableNode(server,
                                 UA_NODEID_NULL,
                                 relayId,
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                 UA_QUALIFIEDNAME(1, "ManufacturerName"),
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                 mnAttr,
                                 NULL,
                                 NULL);
  if (UA_StatusCode_isBad(rc))
  {
    UA_ServerConfig * config = UA_Server_getConfig(server);
    UA_LOG_ERROR(config->logging,
                 UA_LOGCATEGORY_SERVER,
                 "UA_Server_addVariableNode(..., \"ManufacturerName\", ...) failed with %s",
                 UA_StatusCode_name(rc));
    return rc;
  }

  UA_VariableAttributes modelAttr = UA_VariableAttributes_default;
  UA_String modelName = UA_STRING("Relay 1");
  UA_Variant_setScalar(&modelAttr.value, &modelName, &UA_TYPES[UA_TYPES_STRING]);
  modelAttr.displayName = UA_LOCALIZEDTEXT("en-US", "ModelName");
  rc = UA_Server_addVariableNode(server,
                                 UA_NODEID_NULL,
                                 relayId,
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                 UA_QUALIFIEDNAME(1, "ModelName"),
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                 modelAttr,
                                 NULL,
                                 NULL);
  if (UA_StatusCode_isBad(rc))
  {
    UA_ServerConfig * config = UA_Server_getConfig(server);
    UA_LOG_ERROR(config->logging,
                 UA_LOGCATEGORY_SERVER,
                 "UA_Server_addVariableNode(..., \"ModelName\", ...) failed with %s",
                 UA_StatusCode_name(rc));
    return rc;
  }

  UA_VariableAttributes statusAttr = UA_VariableAttributes_default;
  UA_Boolean status = true;
  UA_Variant_setScalar(&statusAttr.value, &status, &UA_TYPES[UA_TYPES_BOOLEAN]);
  statusAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Status");
  rc = UA_Server_addVariableNode(server,
                                 UA_NODEID_NULL,
                                 relayId,
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                 UA_QUALIFIEDNAME(1, "Status"),
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                 statusAttr,
                                 NULL,
                                 NULL);
  if (UA_StatusCode_isBad(rc))
  {
    UA_ServerConfig * config = UA_Server_getConfig(server);
    UA_LOG_ERROR(config->logging,
                 UA_LOGCATEGORY_SERVER,
                 "UA_Server_addVariableNode(..., \"Status\", ...) failed with %s",
                 UA_StatusCode_name(rc));
    return rc;
  }

  UA_VariableAttributes relay_status_attr = UA_VariableAttributes_default;
  UA_Boolean relay_open = true;
  UA_Variant_setScalar(&relay_status_attr.value, &relay_open, &UA_TYPES[UA_TYPES_BOOLEAN]);
  relay_status_attr.displayName = UA_LOCALIZEDTEXT("en-US", "Relay Open");
  rc = UA_Server_addVariableNode(server,
                                 UA_NODEID_NULL,
                                 relayId,
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                 UA_QUALIFIEDNAME(1, "Relay Open"),
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                 relay_status_attr,
                                 NULL,
                                 NULL);
  if (UA_StatusCode_isBad(rc))
  {
    UA_ServerConfig * config = UA_Server_getConfig(server);
    UA_LOG_ERROR(config->logging,
                 UA_LOGCATEGORY_SERVER,
                 "UA_Server_addVariableNode(..., \"Relay Open\", ...) failed with %s",
                 UA_StatusCode_name(rc));
    return rc;
  }

  UA_MethodAttributes relay_close_attr = UA_MethodAttributes_default;
  relay_close_attr.description = UA_LOCALIZEDTEXT("en-US","Close the relay");
  relay_close_attr.displayName = UA_LOCALIZEDTEXT("en-US","Close");
  relay_close_attr.executable = true;
  relay_close_attr.userExecutable = true;
  rc = UA_Server_addMethodNode(server,
                               UA_NODEID_NULL,
                               relayId,
                               UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                               UA_QUALIFIEDNAME(1, "close"),
                               relay_close_attr, relay_close_func,
                               0, NULL, 0, NULL, NULL, NULL);
  if (UA_StatusCode_isBad(rc))
  {
    UA_ServerConfig * config = UA_Server_getConfig(server);
    UA_LOG_ERROR(config->logging,
                 UA_LOGCATEGORY_SERVER,
                 "UA_Server_addMethodNode(..., \"relay_%d_close_func\", ...) failed with %s",
                 relay_num,
                 UA_StatusCode_name(rc));
    return rc;
  }

  UA_MethodAttributes relay_open_attr = UA_MethodAttributes_default;
  relay_open_attr.description = UA_LOCALIZEDTEXT("en-US","Open the relay");
  relay_open_attr.displayName = UA_LOCALIZEDTEXT("en-US","Open");
  relay_open_attr.executable = true;
  relay_open_attr.userExecutable = true;
  rc = UA_Server_addMethodNode(server,
                               UA_NODEID_NULL,
                               relayId,
                               UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                               UA_QUALIFIEDNAME(1, "open"),
                               relay_open_attr, relay_open_func,
                               0, NULL, 0, NULL, NULL, NULL);
  if (UA_StatusCode_isBad(rc))
  {
    UA_ServerConfig * config = UA_Server_getConfig(server);
    UA_LOG_ERROR(config->logging,
                 UA_LOGCATEGORY_SERVER,
                 "UA_Server_addMethodNode(..., \"relay_%d_open_MethodCallback\", ...) failed with %s",
                 relay_num,
                 UA_StatusCode_name(rc));
    return rc;
  }

  return UA_STATUSCODE_GOOD;
}

/**************************************************************************************
 * INTERNAL FUNCTION DEFINITION
 **************************************************************************************/

UA_StatusCode
relay_1_close_MethodCallback(UA_Server *server,
                             const UA_NodeId *sessionId, void *sessionHandle,
                             const UA_NodeId *methodId, void *methodContext,
                             const UA_NodeId *objectId, void *objectContext,
                             size_t inputSize, const UA_Variant *input,
                             size_t outputSize, UA_Variant *output)
{
  /* Close the default-open switch. */
  digitalWrite(RELAY1, HIGH);
  digitalWrite(LED_D0, HIGH);
  /* Write some debug output. */
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"relay_1_close_MethodCallback\" was called");
  return UA_STATUSCODE_GOOD;
}

UA_StatusCode
relay_1_open_MethodCallback(UA_Server *server,
                            const UA_NodeId *sessionId, void *sessionHandle,
                            const UA_NodeId *methodId, void *methodContext,
                            const UA_NodeId *objectId, void *objectContext,
                            size_t inputSize, const UA_Variant *input,
                            size_t outputSize, UA_Variant *output)
{
  /* Close the default-open switch. */
  digitalWrite(RELAY1, LOW);
  digitalWrite(LED_D0, LOW);
  /* Write some debug output. */
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"relay_1_open_MethodCallback\" was called");
  return UA_STATUSCODE_GOOD;
}

UA_StatusCode
relay_2_close_MethodCallback(UA_Server *server,
                             const UA_NodeId *sessionId, void *sessionHandle,
                             const UA_NodeId *methodId, void *methodContext,
                             const UA_NodeId *objectId, void *objectContext,
                             size_t inputSize, const UA_Variant *input,
                             size_t outputSize, UA_Variant *output)
{
  /* Close the default-open switch. */
  digitalWrite(RELAY2, HIGH);
  digitalWrite(LED_D1, HIGH);
  /* Write some debug output. */
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"relay_2_close_MethodCallback\" was called");
  return UA_STATUSCODE_GOOD;
}

UA_StatusCode
relay_2_open_MethodCallback(UA_Server *server,
                            const UA_NodeId *sessionId, void *sessionHandle,
                            const UA_NodeId *methodId, void *methodContext,
                            const UA_NodeId *objectId, void *objectContext,
                            size_t inputSize, const UA_Variant *input,
                            size_t outputSize, UA_Variant *output)
{
  /* Close the default-open switch. */
  digitalWrite(RELAY2, LOW);
  digitalWrite(LED_D1, LOW);
  /* Write some debug output. */
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"relay_2_open_MethodCallback\" was called");
  return UA_STATUSCODE_GOOD;
}

UA_StatusCode
relay_3_close_MethodCallback(UA_Server *server,
                             const UA_NodeId *sessionId, void *sessionHandle,
                             const UA_NodeId *methodId, void *methodContext,
                             const UA_NodeId *objectId, void *objectContext,
                             size_t inputSize, const UA_Variant *input,
                             size_t outputSize, UA_Variant *output)
{
  /* Close the default-open switch. */
  digitalWrite(RELAY3, HIGH);
  digitalWrite(LED_D2, HIGH);
  /* Write some debug output. */
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"relay_3_close_MethodCallback\" was called");
  return UA_STATUSCODE_GOOD;
}

UA_StatusCode
relay_3_open_MethodCallback(UA_Server *server,
                            const UA_NodeId *sessionId, void *sessionHandle,
                            const UA_NodeId *methodId, void *methodContext,
                            const UA_NodeId *objectId, void *objectContext,
                            size_t inputSize, const UA_Variant *input,
                            size_t outputSize, UA_Variant *output)
{
  /* Close the default-open switch. */
  digitalWrite(RELAY3, LOW);
  digitalWrite(LED_D2, LOW);
  /* Write some debug output. */
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"relay_3_open_MethodCallback\" was called");
  return UA_STATUSCODE_GOOD;
}

UA_StatusCode
relay_4_close_MethodCallback(UA_Server *server,
                             const UA_NodeId *sessionId, void *sessionHandle,
                             const UA_NodeId *methodId, void *methodContext,
                             const UA_NodeId *objectId, void *objectContext,
                             size_t inputSize, const UA_Variant *input,
                             size_t outputSize, UA_Variant *output)
{
  /* Close the default-open switch. */
  digitalWrite(RELAY4, HIGH);
  digitalWrite(LED_D3, HIGH);
  /* Write some debug output. */
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"relay_4_close_MethodCallback\" was called");
  return UA_STATUSCODE_GOOD;
}

UA_StatusCode
relay_4_open_MethodCallback(UA_Server *server,
                            const UA_NodeId *sessionId, void *sessionHandle,
                            const UA_NodeId *methodId, void *methodContext,
                            const UA_NodeId *objectId, void *objectContext,
                            size_t inputSize, const UA_Variant *input,
                            size_t outputSize, UA_Variant *output)
{
  /* Close the default-open switch. */
  digitalWrite(RELAY4, LOW);
  digitalWrite(LED_D3, LOW);
  /* Write some debug output. */
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"relay_4_open_MethodCallback\" was called");
  return UA_STATUSCODE_GOOD;
}
