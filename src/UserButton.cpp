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

#include "UserButton.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * FUNCTION DEFINITION
 **************************************************************************************/

static void user_button_on_read_request(UA_Server *server,
                                        const UA_NodeId *sessionId,
                                        void *sessionContext,
                                        const UA_NodeId *nodeid,
                                        void *nodeContext,
                                        const UA_NumericRange *range,
                                        const UA_DataValue *data)
{
  UserButton * this_ptr = reinterpret_cast<UserButton *>(nodeContext);
  this_ptr->onReadRequest(server, nodeid);
}

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

UserButton::UserButton(UA_NodeId const & node_id)
  : _node_id{node_id}
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

UserButton::SharedPtr UserButton::create(UA_Server * server, UA_NodeId const & parent_node_id)
{
  UA_StatusCode rc = UA_STATUSCODE_GOOD;

  UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
  oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "User Button");
  UA_NodeId obj_node_id;
  rc = UA_Server_addObjectNode(server,
                               UA_NODEID_NULL,
                               parent_node_id,
                               UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                               UA_QUALIFIEDNAME(1, "UserButton"),
                               UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                               oAttr,
                               NULL,
                               &obj_node_id);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "UserButton::create: UA_Server_addObjectNode(...) failed with %s", UA_StatusCode_name(rc));
    return nullptr;
  }


  UA_VariableAttributes user_button_value_attr = UA_VariableAttributes_default;

  /* Obtain the current value of the input pin. */
  pinMode(BTN_USER, INPUT);
  PinStatus const in_x_val = digitalRead(BTN_USER);
  UA_Boolean user_button_value = (in_x_val == HIGH) ? true : false;
  UA_Variant_setScalar(&user_button_value_attr.value, &user_button_value, &UA_TYPES[UA_TYPES_BOOLEAN]);

  user_button_value_attr.displayName = UA_LOCALIZEDTEXT("en-US", "User Button Value");
  user_button_value_attr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId;
  user_button_value_attr.accessLevel = UA_ACCESSLEVELMASK_READ;

  /* Add the variable node. */
  UA_NodeId var_node_id;
  rc = UA_Server_addVariableNode(server,
                                 UA_NODEID_NULL,
                                 obj_node_id,
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                 UA_QUALIFIEDNAME(1, "Value"),
                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                 user_button_value_attr,
                                 NULL,
                                 &var_node_id);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "UserButton::create: UA_Server_addVariableNode(...) failed with %s",
                 UA_StatusCode_name(rc));
    return nullptr;
  }

  /* Create an instance of UserButton here. */
  auto const instance_ptr = std::make_shared<UserButton>(var_node_id);

  rc = UA_Server_setNodeContext(server, var_node_id, reinterpret_cast<void *>(instance_ptr.get()));
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "UserButton::create: UA_Server_setNodeContext(...) failed with %s",
                 UA_StatusCode_name(rc));
    return nullptr;
  }

  UA_ValueCallback callback;
  callback.onRead = user_button_on_read_request;
  callback.onWrite = NULL;
  rc = UA_Server_setVariableNode_valueCallback(server, var_node_id, callback);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "UserButton::create: UA_Server_setVariableNode_valueCallback(...) failed with %s",
                 UA_StatusCode_name(rc));
    return nullptr;
  }

  return instance_ptr;
}

void UserButton::onReadRequest(UA_Server * server, UA_NodeId const * node_id)
{
  /* Obtain the value of the digital input pin. */
  pinMode(BTN_USER, INPUT);
  PinStatus const in_x_val = digitalRead(BTN_USER);
  /* Update the variable node. */
  UA_Boolean in_x_val_opcua_value = (in_x_val == HIGH) ? true : false;
  UA_Variant in_x_val_opcua_variant;
  UA_Variant_init(&in_x_val_opcua_variant);
  UA_Variant_setScalar(&in_x_val_opcua_variant, &in_x_val_opcua_value, &UA_TYPES[UA_TYPES_BOOLEAN]);
  UA_Server_writeValue(server, *node_id, in_x_val_opcua_variant);
  /* Some debug output. */
  UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "UserButton::onReadRequest: value = %d", in_x_val);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
