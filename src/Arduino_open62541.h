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
#include "o1heap/o1heap.h"
#include "add_variable.hpp"
#include "Relay.h"
#include "DigitalInput.h"

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

#if !defined(ARDUINO_OPTA)
# error "This library does only support Arduino Opta"
#endif

/**************************************************************************************
 * FUNCTION DECLARATIONS
 **************************************************************************************/

UA_StatusCode opc_ua_define_opta_obj(UA_Server * server,
                                     UA_NodeId * opta_node_id);

UA_StatusCode opc_ua_define_digital_input_obj(UA_Server * server,
                                              UA_NodeId const opta_node_id,
                                              UA_NodeId * opta_digital_input_node_id);

UA_StatusCode opc_ua_define_relay_obj(UA_Server * server,
                                      UA_NodeId const opta_node_id,
                                      UA_NodeId * opta_relay_node_id);
