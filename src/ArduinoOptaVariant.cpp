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

#include "ArduinoOptaVariant.h"

#if __has_include("opta_info.h")
# include <cstdint>
# include "opta_info.h"
extern "C" OptaBoardInfo * boardInfo();
#else
# error "Can not find include file \"opta_info.h\""
#endif

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool ArduinoOptaVariant::get_opta_variant(Type & type)
{
  OptaBoardInfo * info = boardInfo();

  if (info->_board_functionalities.ethernet && info->_board_functionalities.wifi && info->_board_functionalities.rs485) {
    type = ArduinoOptaVariant::Type::WiFi;
  }
  else if (info->_board_functionalities.ethernet && info->_board_functionalities.rs485) {
    type = ArduinoOptaVariant::Type::RS485;
  }
  else if (info->_board_functionalities.ethernet) {
    type = ArduinoOptaVariant::Type::Lite;
  }
  else
    return false;

  return true;
}

std::string ArduinoOptaVariant::toString(Type const type)
{
  switch(type)
  {
    case ArduinoOptaVariant::Type::WiFi:  return std::string("Arduino Opta WiFi");  break;
    case ArduinoOptaVariant::Type::RS485: return std::string("Arduino Opta RS485"); break;
    case ArduinoOptaVariant::Type::Lite:  return std::string("Arduino Opta Lite");  break;
    default: __builtin_unreachable(); break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
