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

#include "OptaExpansionManager.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

DigitalMechExpansion::SharedPtr OptaExpansionManager::create_digital_mechanical_expansion(uint8_t const exp_num)
{
  auto const exp_mech_opcua = opcua::DigitalMechExpansion::create(
    _server,
    UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
    exp_num);

  _dig_mech_exp_list.push_back(exp_mech_opcua);
  return exp_mech_opcua;
}

DigitalStSolidExpansion::SharedPtr OptaExpansionManager::create_digital_solid_state_expansion(uint8_t const exp_num)
{
  auto const exp_solid_state_opcua = opcua::DigitalStSolidExpansion::create(
    _server,
    UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
    exp_num);

  _dig_solid_state_exp_list.push_back(exp_solid_state_opcua);
  return exp_solid_state_opcua;
}

AnalogExpansion::SharedPtr OptaExpansionManager::create_analog_expansion(uint8_t const exp_num)
{
  auto const exp_analog_opcua = opcua::AnalogExpansion::create(
    _server,
    UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
    exp_num);

  _analog_exp_list.push_back(exp_analog_opcua);
  return exp_analog_opcua;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
