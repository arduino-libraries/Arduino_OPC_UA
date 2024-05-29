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
 * TEMPLATE FUNCTION DECLARATION
 **************************************************************************************/

template <typename T>
UA_StatusCode add_variable(UA_Server * server,
                           UA_LocalizedText const displayName,
                           UA_LocalizedText const description,
                           UA_Byte const accessLevel,
                           UA_NodeId const nodeId,
                           UA_NodeId const parentNodeId,
                           UA_NodeId const parentReferenceNodeId,
                           UA_QualifiedName const browseName,
                           T const value);

/**************************************************************************************
 * TEMPLATE FUNCTION IMPLEMENTATION
 **************************************************************************************/

//#include "add_variable.ipp"
