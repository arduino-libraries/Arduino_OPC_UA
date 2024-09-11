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

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

/**
 * @class OptaVariant
 * @brief Enables determination of Opta variant (WiFi, RS485, Lite) on which the OPC UA firmware is running on.
 *
 * This class allows the user to determine the concrete Opta variant (WiFi, RS485, Lite) on which the OPC UA
 * firmware is running on. This is archived by interrogating information stored by the bootloader.
 */
class OptaVariant
{
public:
  /**
   * The constructor of OptaVariant is deleted because this object shall not be instantiated.
   */
  OptaVariant() = delete;
  /**
   * The copy constructor of OptaVariant is deleted because this object shall not be copied.
   */
  OptaVariant(OptaVariant const &) = delete;


  /**
   * Type is an enumeration type to describe the various different Arduino Opta variants.
   */
  enum class Type
  {
    /** Arduino Opta Lite */
    Lite,
    /** Arduino Opta RS485 */
    RS485,
    /** Arduino Opta WiFi */
    WiFi
  };


  /**
   * Determines the current Opta variant by reading information provided by the bootloader.
   * @param type Output parameter containing the current Opta variant.
   * @return True if the Opta variant could be obtained successfully.
   */
  static bool
  get_opta_variant(
    Type & type);

  /**
   * Convert enumerated variant type to variant product name.
   * @param type Enumerated type describing an Opta variant.
   * @return String describing the Opta variant's product name, i.e. Type::Lite -> "Arduino Opta Lite"
   */
  static std::string
    toString(
      Type const type);

  /**
   * Convert enumerated variant type to variant product SKU number.
   * @param type Enumerated type describing an Opta variant.
   * @return String describing the Opta variant's SKU number, i.e. Type::Lite -> "AFX00003"
   */
  static std::string
    toSKUString(
      Type const type);
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
