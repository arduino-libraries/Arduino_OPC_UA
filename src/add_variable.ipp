/*
 * Copyright (c) 2024 Arduino
 *
 * SPDX-License-Identifier: MPL-2.0
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

/**************************************************************************************
 * TEMPLATE FUNCTION DEFINITION
 **************************************************************************************/

template <typename T>
UA_DataType to_UA_DataType() { }

template <>
UA_DataType to_UA_DataType<bool>() { return UA_TYPES[UA_TYPES_BOOLEAN]; }

template <>
UA_DataType to_UA_DataType<uint32_t>() { return UA_TYPES[UA_TYPES_INT32]; }

template <typename T>
void UA_Variant_setScalar(UA_VariableAttributes * attr, T const value);

template <>
void UA_Variant_setScalar<bool>(UA_VariableAttributes * attr, bool const value)
{
  UA_Boolean myBoolean = value;
  UA_Variant_setScalar(&(attr->value), &myBoolean, &UA_TYPES[UA_TYPES_BOOLEAN]);
}

template <>
void UA_Variant_setScalar<uint32_t>(UA_VariableAttributes * attr, uint32_t const value)
{
  UA_Int32 myInteger = value;
  UA_Variant_setScalar(&(attr->value), &myInteger, &UA_TYPES[UA_TYPES_INT32]);
}

template <typename T>
void add_variable(UA_Server * server,
                  UA_LocalizedText const displayName,
                  UA_LocalizedText const description,
                  UA_Byte const accessLevel,
                  UA_NodeId const nodeId,
                  UA_NodeId const parentNodeId,
                  UA_NodeId const parentReferenceNodeId,
                  UA_QualifiedName const browseName,
                  T const value)
{
  /* 1) Define the variable attributes */
  UA_VariableAttributes attr = UA_VariableAttributes_default;
  UA_Variant_setScalar(&attr, value);
  attr.description = displayName;
  attr.displayName = description;
  attr.dataType    = to_UA_DataType<T>().typeId;
  attr.accessLevel = accessLevel;

  /* 2) Define where the node shall be added with which browsename */
  UA_Server_addVariableNode(server,
                            nodeId,
                            parentNodeId,
                            parentReferenceNodeId,
                            browseName,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                            attr,
                            NULL,
                            NULL);
}
