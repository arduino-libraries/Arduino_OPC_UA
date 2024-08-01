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

#include "OptaVariant.h"

#if __has_include("opta_info.h")
# include <cstdint>
# include "opta_info.h"
OptaBoardInfo * boardInfo();
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

bool OptaVariant::get_opta_variant(Type & type)
{
  OptaBoardInfo * info = boardInfo();

  if (info->_board_functionalities.ethernet && info->_board_functionalities.wifi && info->_board_functionalities.rs485) {
    type = OptaVariant::Type::WiFi;
  }
  else if (info->_board_functionalities.ethernet && info->_board_functionalities.rs485) {
    type = OptaVariant::Type::RS485;
  }
  else if (info->_board_functionalities.ethernet) {
    type = OptaVariant::Type::Lite;
  }
  else
    return false;

  return true;
}

std::string OptaVariant::toString(Type const type)
{
  switch(type)
  {
    case OptaVariant::Type::WiFi:  return std::string("Arduino Opta WiFi");  break;
    case OptaVariant::Type::RS485: return std::string("Arduino Opta RS485"); break;
    case OptaVariant::Type::Lite:  return std::string("Arduino Opta Lite");  break;
    default: __builtin_unreachable(); break;
  }
}

std::string OptaVariant::toSKUString(Type const type)
{
  switch(type)
  {
    case OptaVariant::Type::WiFi:  return std::string("AFX00002");  break;
    case OptaVariant::Type::RS485: return std::string("AFX00001"); break;
    case OptaVariant::Type::Lite:  return std::string("AFX00003");  break;
    default: __builtin_unreachable(); break;
  }
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
