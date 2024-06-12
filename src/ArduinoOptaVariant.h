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
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class ArduinoOptaVariant
{
public:
  ArduinoOptaVariant() = delete;
  ArduinoOptaVariant(ArduinoOptaVariant const &) = delete;

  enum class Type { Lite, RS485, WiFi };

  static bool get_opta_variant(Type & type);
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
