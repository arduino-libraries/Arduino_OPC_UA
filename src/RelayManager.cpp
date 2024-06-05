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

#include "RelayManager.h"

#include <Arduino.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

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
 * CTOR/DTOR
 **************************************************************************************/

RelayManager::RelayManager(UA_NodeId const & node_id)
: _node_id{node_id}
{
  /* Nothing happens here. */
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

RelayManager::SharedPtr RelayManager::create(UA_Server * server, UA_NodeId const parent_node_id)
{
  UA_StatusCode rc = UA_STATUSCODE_GOOD;

  UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
  oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Relays");
  UA_NodeId node_id;
  rc = UA_Server_addObjectNode(server,
                               UA_NODEID_NULL,
                               parent_node_id,
                               UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                               UA_QUALIFIEDNAME(1, "Relays"),
                               UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                               oAttr,
                               NULL,
                               &node_id);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "RelayManager::create: UA_Server_addObjectNode(...) failed with %s", UA_StatusCode_name(rc));
    return nullptr;
  }

  UA_MethodAttributes relay_close_attr = UA_MethodAttributes_default;
  relay_close_attr.description = UA_LOCALIZEDTEXT("en-US","Close the relay");
  relay_close_attr.displayName = UA_LOCALIZEDTEXT("en-US","Close");
  relay_close_attr.executable = true;
  relay_close_attr.userExecutable = true;
  rc = UA_Server_addMethodNode(server,
                               UA_NODEID_NULL,
                               node_id,
                               UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                               UA_QUALIFIEDNAME(1, "close"),
                               relay_close_attr, relay_n_close_MethodCallback,
                               0, NULL, 0, NULL, NULL, NULL);
  if (UA_StatusCode_isBad(rc))
  {
    UA_ServerConfig * config = UA_Server_getConfig(server);
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "UA_Server_addMethodNode(..., \"relay_n_close_func\", ...) failed with %s", UA_StatusCode_name(rc));
    return nullptr;
  }

  UA_MethodAttributes relay_open_attr = UA_MethodAttributes_default;
  relay_open_attr.description = UA_LOCALIZEDTEXT("en-US","Open the relay");
  relay_open_attr.displayName = UA_LOCALIZEDTEXT("en-US","Open");
  relay_open_attr.executable = true;
  relay_open_attr.userExecutable = true;
  rc = UA_Server_addMethodNode(server,
                               UA_NODEID_NULL,
                               node_id,
                               UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                               UA_QUALIFIEDNAME(1, "open"),
                               relay_open_attr, relay_n_open_MethodCallback,
                               0, NULL, 0, NULL, NULL, NULL);
  if (UA_StatusCode_isBad(rc))
  {
    UA_ServerConfig * config = UA_Server_getConfig(server);
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "UA_Server_addMethodNode(..., \"relay_n_open_MethodCallback\", ...) failed with %s", UA_StatusCode_name(rc));
    return nullptr;
  }

  auto const instance_ptr = std::make_shared<RelayManager>(node_id);
  return instance_ptr;
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void RelayManager::add_relay_output(UA_Server * server,
                                    const char * display_name,
                                    Relay::OnSetRelayStateFunc const on_set_relay_state)
{
  auto const relay = Relay::create(server, _node_id, display_name, on_set_relay_state);
  if (!relay) {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "RelayManager::add_relay_output: Relay::create(...) failed: returned nullptr");
    return;
  }
  _relay_list.push_back(relay);
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

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
