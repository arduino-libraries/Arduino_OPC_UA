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

#include "expansion/AnalogExpansion.h"
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

/**
 * @class OptaExpansionManager
 * @brief High-level class to create OPC UA representations for Arduino Opta digital and analog expansion boards.
 *
 * This class allows the user to create OPC UA representations of digital (mechanical and solid-state relays) as
 * well as analog expansion boards connected to the Arduino Opta.
 */
class OptaExpansionManager
{
public:
  /**
   * SharedPtr is std::shared_ptr of an OptaExpansionManager class.
   */
  typedef std::shared_ptr<OptaExpansionManager> SharedPtr;


  /**
   * Creates a new instance of the opcua::OptaExpansionManager class.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   * @return std::shared_ptr holding the newly allocated instance of opcua::OptaExpansionManager.
   */
  static SharedPtr
  create(
    UA_Server * server) {
    return std::make_shared<OptaExpansionManager>(server);
  }


  /**
   * Constructor of the opcua::OptaExpansionManager class.
   * @param server Pointer to the OPC UA server implementation of the open62541 library.
   */
  OptaExpansionManager(
    UA_Server * server)
  : _server{server}
  { }


  /**
   * Creates a new instance of the opcua::DigitalMechExpansion (digital expansion with mechanical relays) class.
   * @param exp_num A numerical identifier provided by the Arduino_Opta_Blueprint library and identifying the number of the expansion module in the daisy-chain of expansion modules, i.e. exp_num = 2 refers to the second connect expansion module.
   * @return std::shared_ptr holding the newly allocated instance of opcua::DigitalMechExpansion.
   */
  DigitalMechExpansion::SharedPtr
  create_digital_mechanical_expansion(
    uint8_t const exp_num);

  /**
   * Creates a new instance of the opcua::DigitalStSolidExpansion (digital expansion with solid-state relays) class.
   * @param exp_num A numerical identifier provided by the Arduino_Opta_Blueprint library and identifying the number of the expansion module in the daisy-chain of expansion modules, i.e. exp_num = 2 refers to the second connect expansion module.
   * @return std::shared_ptr holding the newly allocated instance of opcua::DigitalStSolidExpansion.
   */
  DigitalStSolidExpansion::SharedPtr
  create_digital_solid_state_expansion(
    uint8_t const exp_num);

  /**
   * Creates a new instance of the opcua::AnalogExpansion class.
   * @param exp_num A numerical identifier provided by the Arduino_Opta_Blueprint library and identifying the number of the expansion module in the daisy-chain of expansion modules, i.e. exp_num = 2 refers to the second connect expansion module.
   * @return std::shared_ptr holding the newly allocated instance of opcua::AnalogExpansion.
   */
  AnalogExpansion::SharedPtr
  create_analog_expansion(
    uint8_t const exp_num);


private:
  UA_Server * _server;

  std::list<DigitalMechExpansion::SharedPtr> _dig_mech_exp_list;
  std::list<DigitalStSolidExpansion::SharedPtr> _dig_solid_state_exp_list;
  std::list<AnalogExpansion::SharedPtr> _analog_exp_list;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
