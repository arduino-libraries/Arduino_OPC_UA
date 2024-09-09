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

#include "AnalogOutputManager.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

AnalogOutputManager::AnalogOutputManager(
  UA_NodeId const & node_id)
: _node_id{node_id}
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

AnalogOutputManager::SharedPtr
AnalogOutputManager::create(
  UA_Server * server,
  UA_NodeId const parent_node_id)
{
  UA_StatusCode rc = UA_STATUSCODE_GOOD;

  UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
  oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Analog Outputs");
  UA_NodeId node_id;
  rc = UA_Server_addObjectNode(server,
                               UA_NODEID_NULL,
                               parent_node_id,
                               UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                               UA_QUALIFIEDNAME(1, "AnalogOutputs"),
                               UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                               oAttr,
                               NULL,
                               &node_id);
  if (UA_StatusCode_isBad(rc))
  {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                 "%s: UA_Server_addObjectNode(...) failed with %s", __PRETTY_FUNCTION__, UA_StatusCode_name(rc));
    return nullptr;
  }

  auto const instance_ptr = std::make_shared<AnalogOutputManager>(node_id);
  return instance_ptr;
}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void
AnalogOutputManager::add_analog_output(
  UA_Server * server,
  const char * display_name,
  AnalogOutput::OnReadRequestFunc const on_read_request,
  AnalogOutput::OnWriteRequestFunc const on_write_request)
{
  auto const analog_output = AnalogOutput::create(server, _node_id, display_name, on_read_request, on_write_request);
  if (!analog_output) {
    UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "%s: AnalogOutput::create(...) failed: returned nullptr", __PRETTY_FUNCTION__);
    return;
  }
  _analog_output_list.push_back(analog_output);
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
