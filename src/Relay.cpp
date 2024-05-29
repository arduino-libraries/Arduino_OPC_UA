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
 * INTERNAL FUNCTION DECLARATION
 **************************************************************************************/

static UA_StatusCode
relay_n_close_MethodCallback(UA_Server *server,
                             const UA_NodeId *sessionId, void *sessionHandle,
                             const UA_NodeId *methodId, void *methodContext,
                             const UA_NodeId *objectId, void *objectContext,
                             size_t inputSize, const UA_Variant *input,
                             size_t outputSize, UA_Variant *output);

static UA_StatusCode
relay_n_open_MethodCallback(UA_Server *server,
                            const UA_NodeId *sessionId, void *sessionHandle,
                            const UA_NodeId *methodId, void *methodContext,
                            const UA_NodeId *objectId, void *objectContext,
                            size_t inputSize, const UA_Variant *input,
                            size_t outputSize, UA_Variant *output);

/**************************************************************************************
 * FUNCTION DEFINITION
 **************************************************************************************/

UA_StatusCode opc_ua_define_relay_obj(UA_Server * server,
                                      UA_NodeId const opta_node_id,
                                      UA_NodeId * opta_relay_node_id)
{
  UA_StatusCode rc = UA_STATUSCODE_GOOD;

  UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
  oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Relays");
  rc = UA_Server_addObjectNode(server,
                               UA_NODEID_NULL,
                               opta_node_id,
                               UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                               UA_QUALIFIEDNAME(1, "Relays"),
                               UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                               oAttr,
                               NULL,
                               opta_relay_node_id);
  if (UA_StatusCode_isBad(rc))
  {
    UA_ServerConfig * config = UA_Server_getConfig(server);
    UA_LOG_ERROR(config->logging,
                 UA_LOGCATEGORY_SERVER,
                 "UA_Server_addObjectNode(...) failed with %s",
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
                               *opta_relay_node_id,
                               UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                               UA_QUALIFIEDNAME(1, "close"),
                               relay_close_attr, relay_n_close_MethodCallback,
                               0, NULL, 0, NULL, NULL, NULL);
  if (UA_StatusCode_isBad(rc))
  {
    UA_ServerConfig * config = UA_Server_getConfig(server);
    UA_LOG_ERROR(config->logging,
                 UA_LOGCATEGORY_SERVER,
                 "UA_Server_addMethodNode(..., \"relay_n_close_func\", ...) failed with %s",
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
                               *opta_relay_node_id,
                               UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                               UA_QUALIFIEDNAME(1, "open"),
                               relay_open_attr, relay_n_open_MethodCallback,
                               0, NULL, 0, NULL, NULL, NULL);
  if (UA_StatusCode_isBad(rc))
  {
    UA_ServerConfig * config = UA_Server_getConfig(server);
    UA_LOG_ERROR(config->logging,
                 UA_LOGCATEGORY_SERVER,
                 "UA_Server_addMethodNode(..., \"relay_n_open_MethodCallback\", ...) failed with %s",
                 UA_StatusCode_name(rc));
    return rc;
  }
}

UA_StatusCode opc_ua_define_relay(UA_Server * server,
                                  UA_NodeId const opta_relay_node_id,
                                  unsigned int const relay_num)
{
  UA_StatusCode rc = UA_STATUSCODE_GOOD;

  UA_VariableAttributes relay_value_attr = UA_VariableAttributes_default;
  UA_Boolean relay_value = true;
  UA_Variant_setScalar(&relay_value_attr.value, &relay_value, &UA_TYPES[UA_TYPES_BOOLEAN]);

  char relay_value_display_name[32] = {0};
  snprintf(relay_value_display_name, sizeof(relay_value_display_name), "Relay %d Value", relay_num);

  relay_value_attr.displayName = UA_LOCALIZEDTEXT("en-US", relay_value_display_name);
  relay_value_attr.accessLevel =
    UA_ACCESSLEVELMASK_READ |
    UA_ACCESSLEVELMASK_WRITE | UA_ACCESSLEVELMASK_STATUSWRITE | UA_ACCESSLEVELMASK_TIMESTAMPWRITE; /* Status and timestamp write access necessary for opcua-client. */

  char relay_value_node_id[32] = {0};
  snprintf(relay_value_node_id, sizeof(relay_value_node_id), "relay-value-%d", relay_num);

  rc = UA_Server_addVariableNode(server,
                                 UA_NODEID_STRING(1, relay_value_node_id),
                                 opta_relay_node_id,
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                 UA_QUALIFIEDNAME(1, "Value"),
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                 relay_value_attr,
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

  return UA_STATUSCODE_GOOD;
}

/**************************************************************************************
 * INTERNAL FUNCTION DEFINITION
 **************************************************************************************/

UA_StatusCode
relay_n_close_MethodCallback(UA_Server *server,
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
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"relay_n_close_MethodCallback\" was called");
  return UA_STATUSCODE_GOOD;
}

UA_StatusCode
relay_n_open_MethodCallback(UA_Server *server,
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
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "\"relay_n_open_MethodCallback\" was called");
  return UA_STATUSCODE_GOOD;
}
