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
 * TYPE DEFINITION
 **************************************************************************************/

typedef void (*onReadCallback)(UA_Server *server, const UA_NodeId *sessionId,
                               void *sessionContext, const UA_NodeId *nodeid,
                                void *nodeContext, const UA_NumericRange *range,
                                const UA_DataValue *value);

/**************************************************************************************
 * FUNCTION DECLARATION
 **************************************************************************************/

UA_StatusCode opc_ua_define_digital_input(UA_Server *server,
                                          UA_NodeId const opta_digital_input_node_id,
                                          unsigned int const digital_input_num,
                                          onReadCallback before_read_digital);

void before_read_digital_input_1(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data);

void before_read_digital_input_2(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data);

void before_read_digital_input_3(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data);

void before_read_digital_input_4(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data);

void before_read_digital_input_5(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data);

void before_read_digital_input_6(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data);

void before_read_digital_input_7(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data);

void before_read_digital_input_8(UA_Server *server,
                                 const UA_NodeId *sessionId, void *sessionContext,
                                 const UA_NodeId *nodeid, void *nodeContext,
                                 const UA_NumericRange *range, const UA_DataValue *data);
