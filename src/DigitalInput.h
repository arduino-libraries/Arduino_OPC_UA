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

#include <Arduino.h>

#include <list>
#include <functional>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class DigitalInput
{
public:
  DigitalInput();

  UA_StatusCode begin(UA_Server * server,
                      UA_NodeId const parent_node_id);

  typedef void (*onReadRequestFunc)(UA_Server *server,
                                    const UA_NodeId *sessionId,
                                    void *sessionContext,
                                    const UA_NodeId *nodeid,
                                    void *nodeContext,
                                    const UA_NumericRange *range,
                                    const UA_DataValue *value);

  UA_StatusCode add_digital_input_pin(UA_Server * server,
                                      UA_NodeId const digital_input_pin_node_id,
                                      char const * digital_input_pin_display_name,
                                      onReadRequestFunc const on_read_request);


private:
  bool _is_initialized;
  UA_NodeId _digital_input_node_id;
};

/**************************************************************************************
 * FREE FUNCTION DEFINITION
 **************************************************************************************/

void on_read_request_opta_digital_input_1(UA_Server *server, const UA_NodeId *sessionId, void *sessionContext, const UA_NodeId *nodeid, void *nodeContext, const UA_NumericRange *range, const UA_DataValue *data);
void on_read_request_opta_digital_input_2(UA_Server *server, const UA_NodeId *sessionId, void *sessionContext, const UA_NodeId *nodeid, void *nodeContext, const UA_NumericRange *range, const UA_DataValue *data);
void on_read_request_opta_digital_input_3(UA_Server *server, const UA_NodeId *sessionId, void *sessionContext, const UA_NodeId *nodeid, void *nodeContext, const UA_NumericRange *range, const UA_DataValue *data);
void on_read_request_opta_digital_input_4(UA_Server *server, const UA_NodeId *sessionId, void *sessionContext, const UA_NodeId *nodeid, void *nodeContext, const UA_NumericRange *range, const UA_DataValue *data);
void on_read_request_opta_digital_input_5(UA_Server *server, const UA_NodeId *sessionId, void *sessionContext, const UA_NodeId *nodeid, void *nodeContext, const UA_NumericRange *range, const UA_DataValue *data);
void on_read_request_opta_digital_input_6(UA_Server *server, const UA_NodeId *sessionId, void *sessionContext, const UA_NodeId *nodeid, void *nodeContext, const UA_NumericRange *range, const UA_DataValue *data);
void on_read_request_opta_digital_input_7(UA_Server *server, const UA_NodeId *sessionId, void *sessionContext, const UA_NodeId *nodeid, void *nodeContext, const UA_NumericRange *range, const UA_DataValue *data);
void on_read_request_opta_digital_input_8(UA_Server *server, const UA_NodeId *sessionId, void *sessionContext, const UA_NodeId *nodeid, void *nodeContext, const UA_NumericRange *range, const UA_DataValue *data);

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class ArduinoOptaDigitalInput
{
  I1, I2, I3, I4, I5, I6, I7, I8
};

/**************************************************************************************
 * CONSTANT
 **************************************************************************************/

static std::list <ArduinoOptaDigitalInput> const ArduinoOptaDigitalInputList =
  {
    ArduinoOptaDigitalInput::I1,
    ArduinoOptaDigitalInput::I2,
    ArduinoOptaDigitalInput::I3,
    ArduinoOptaDigitalInput::I4,
    ArduinoOptaDigitalInput::I5,
    ArduinoOptaDigitalInput::I6,
    ArduinoOptaDigitalInput::I7,
    ArduinoOptaDigitalInput::I8
  };

UA_StatusCode opc_ua_define_digital_input_obj(UA_Server *server,
                                              UA_NodeId const opta_node_id,
                                              UA_NodeId *opta_digital_input_node_id);

UA_StatusCode opc_ua_define_digital_input(UA_Server *server,
                                          UA_NodeId const opta_digital_input_node_id,
                                          ArduinoOptaDigitalInput const digital_in_pin);
