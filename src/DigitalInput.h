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

#include <list>

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class ArduinoOptaDigitalInput { I1, I2, I3, I4, I5, I6, I7, I8 };

/**************************************************************************************
 * CONSTANT
 **************************************************************************************/

static std::list<ArduinoOptaDigitalInput> const ArduinoOptaDigitalInputList =
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

/**************************************************************************************
 * FUNCTION DECLARATION
 **************************************************************************************/

UA_StatusCode opc_ua_define_digital_input_obj(UA_Server * server,
                                              UA_NodeId const opta_node_id,
                                              UA_NodeId * opta_digital_input_node_id);

UA_StatusCode opc_ua_define_digital_input(UA_Server *server,
                                          UA_NodeId const opta_digital_input_node_id,
                                          ArduinoOptaDigitalInput const digital_in_pin);
