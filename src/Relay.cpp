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
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

Relay::Relay(UA_NodeId const & node_id)
  : _node_id{node_id}
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

Relay::SharedPtr Relay::create(UA_Server *server,
                               UA_NodeId const &parent_node_id,
                               const char *display_name)
{
  UA_StatusCode rc = UA_STATUSCODE_GOOD;

  UA_VariableAttributes relay_value_attr = UA_VariableAttributes_default;
  UA_Boolean relay_value = true;
  UA_Variant_setScalar(&relay_value_attr.value, &relay_value, &UA_TYPES[UA_TYPES_BOOLEAN]);

  relay_value_attr.displayName = UA_LOCALIZEDTEXT("en-US", (char *)display_name);
  relay_value_attr.accessLevel =
    UA_ACCESSLEVELMASK_READ |
    UA_ACCESSLEVELMASK_WRITE | UA_ACCESSLEVELMASK_STATUSWRITE |
    UA_ACCESSLEVELMASK_TIMESTAMPWRITE; /* Status and timestamp write access necessary for opcua-client. */

  UA_NodeId node_id;
  rc = UA_Server_addVariableNode(server,
                                 UA_NODEID_NULL,
                                 parent_node_id,
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                 UA_QUALIFIEDNAME(1, "Value"),
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                 relay_value_attr,
                                 NULL,
                                 &node_id);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "Relay::create: UA_Server_addVariableNode(...) failed with %s", UA_StatusCode_name(rc));
    return nullptr;
  }

  /* Create an instance of Relay here. */
  auto const instance_ptr = std::make_shared<Relay>(node_id);
  return instance_ptr;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
