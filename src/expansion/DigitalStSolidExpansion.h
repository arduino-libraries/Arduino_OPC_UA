/*
 * Copyright (c) 2024 Arduino
 *
 * SPDX-License-Identifier: MPL-2.0
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include "DigitalExpansion.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class DigitalStSolidExpansion : public DigitalExpansion
{
public:
  typedef std::shared_ptr<DigitalStSolidExpansion> SharedPtr;


  static SharedPtr create(UA_Server *server, UA_NodeId const parent_node_id, uint8_t const exp_num)
  {
    char display_name[64] = {0};
    snprintf(display_name, sizeof(display_name), "Arduino Opta Expansion %d: Digital (Solid State)", exp_num);

    char node_name[32] = {0};
    snprintf(node_name, sizeof(node_name), "DigExpSoli_%d", exp_num);

    char model_name[] = {"AFX00006"};

    auto const instance_ptr = std::make_shared<DigitalStSolidExpansion>(server, parent_node_id, display_name, node_name, model_name);
    return instance_ptr;
  }


  DigitalStSolidExpansion(UA_Server * server,
                          UA_NodeId const parent_node_id,
                          char * display_name,
                          char * node_name,
                          char * model_name)
    : DigitalExpansion{server, parent_node_id, display_name, node_name, model_name}
  {}
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
