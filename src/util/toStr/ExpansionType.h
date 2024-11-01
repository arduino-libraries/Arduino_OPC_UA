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

#include <string>

#include "OptaBlue.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

/**
 * @class ExpansionType
 * @brief Provides a method for converting Arduino_Opta_Blueprint's ExpansionType_t to a human readable string.
 */
class ExpansionType
{
public:
  /**
   * The constructor of ExpansionType is deleted because this object shall not be instantiated.
   */
  ExpansionType() = delete;
  /**
   * The copy constructor of ExpansionType is deleted because this object shall not be copied.
   */
  ExpansionType(ExpansionType const &) = delete;

  /**
   * Converts Arduino_Opta_Blueprint's ExpansionType_t into a human readable string.
   * @param type Numeric identifier identifying the type of connected expansion board.
   * @return Human readable string describing the concrete expansion module.
   */
  static std::string toStr(ExpansionType_t const type)
  {
    if(type == EXPANSION_NOT_VALID)
      return std::string("Invalid");
    else if(type == EXPANSION_OPTA_DIGITAL_MEC)
      return std::string("Digital [Mech.]");
    else if(type == EXPANSION_OPTA_DIGITAL_STS)
      return std::string("Digital [Solid]");
    else if(type == EXPANSION_DIGITAL_INVALID)
      return std::string("Digital [Inva.]");
    else if(type == EXPANSION_OPTA_ANALOG)
      return std::string("Analog");
    else
      return std::string("Unknown");
  }
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

}
