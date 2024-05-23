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

UA_StatusCode opc_ua_define_relay_1(UA_Server * server)
{
  UA_StatusCode rc = UA_STATUSCODE_GOOD;
  UA_NodeId relayId; /* get the nodeid assigned by the server */

  UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
  oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Relay 1");
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

  UA_VariableAttributes rpmAttr = UA_VariableAttributes_default;
  UA_Double rpm = 50.0;
  UA_Variant_setScalar(&rpmAttr.value, &rpm, &UA_TYPES[UA_TYPES_DOUBLE]);
  rpmAttr.displayName = UA_LOCALIZEDTEXT("en-US", "MotorRPM");
  rc = UA_Server_addVariableNode(server,
                                 UA_NODEID_NULL,
                                 relayId,
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                 UA_QUALIFIEDNAME(1, "MotorRPMs"),
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                 rpmAttr,
                                 NULL,
                                 NULL);
  if (UA_StatusCode_isBad(rc))
  {
    UA_ServerConfig * config = UA_Server_getConfig(server);
    UA_LOG_ERROR(config->logging,
                 UA_LOGCATEGORY_SERVER,
                 "UA_Server_addVariableNode(..., \"MotorRPMs\", ...) failed with %s",
                 UA_StatusCode_name(rc));
    return rc;
  }

  return UA_STATUSCODE_GOOD;
}
