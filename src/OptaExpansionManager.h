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

#include <memory>

#include "expansion/DigitalMechExpansion.h"
#include "expansion/DigitalStSolidExpansion.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class OptaExpansionManager
{
public:
  typedef std::shared_ptr<OptaExpansionManager> SharedPtr;


  static SharedPtr create(UA_Server * server) {
    return std::make_shared<OptaExpansionManager>(server);
  }


  OptaExpansionManager(UA_Server * server)
  : _server{server}
  { }


  DigitalMechExpansion::SharedPtr create_digital_mechanical_expansion(uint8_t const exp_num);
  DigitalStSolidExpansion::SharedPtr create_digital_solid_state_expansion(uint8_t const exp_num);


private:
  UA_Server * _server;

  std::list<DigitalMechExpansion::SharedPtr> _dig_mech_exp_list;
  std::list<DigitalStSolidExpansion::SharedPtr> _dig_solid_state_exp_list;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
