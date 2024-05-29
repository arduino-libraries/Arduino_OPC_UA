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

#include "open62541.h"

/**************************************************************************************
 * FUNCTION DECLARATION
 **************************************************************************************/

UA_StatusCode opc_ua_define_relay_obj(UA_Server * server,
                                      UA_NodeId const opta_node_id,
                                      UA_NodeId * opta_relay_node_id);

UA_StatusCode opc_ua_define_relay(UA_Server * server,
                                  UA_NodeId const opta_relay_node_id,
                                  unsigned int const relay_num);
