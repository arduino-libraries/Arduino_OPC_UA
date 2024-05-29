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

/**************************************************************************************
 * FUNCTION DEFINITION
 **************************************************************************************/

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
