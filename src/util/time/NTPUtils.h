/*
 * Copyright (c) 2024 Arduino
 *
 * SPDX-License-Identifier: MPL-2.0
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

/*
	This Utility Class is derived from the example code found here https://www.arduino.cc/en/Tutorial/UdpNTPClient
	For more information on NTP (Network Time Protocol) you can refer to this Wikipedia article https://en.wikipedia.org/wiki/Network_Time_Protocol
*/

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <Arduino.h>
#include <Udp.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class NTPUtils
{
public:

  static unsigned long getTime(UDP &udp);

private:

  static size_t const NTP_PACKET_SIZE = 48;
  static int const NTP_TIME_SERVER_PORT = 123;
  static int const NTP_LOCAL_PORT = 8888;

  static unsigned long const NTP_TIMEOUT_MS = 1000;
  static constexpr const char *NTP_TIME_SERVER = "time.arduino.cc";

  static void sendNTPpacket(UDP &udp);
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
