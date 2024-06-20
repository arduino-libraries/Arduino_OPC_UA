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

#include "NTPUtils.h"

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

unsigned long NTPUtils::getTime(UDP & udp)
{
  udp.begin(NTP_LOCAL_PORT);

  sendNTPpacket(udp);

  bool is_timeout = false;
  unsigned long const start = millis();
  do
  {
    is_timeout = (millis() - start) >= NTP_TIMEOUT_MS;
  } while(!is_timeout && !udp.parsePacket());

  if(is_timeout) {
    udp.stop();
    return 0;
  }
  
  uint8_t ntp_packet_buf[NTP_PACKET_SIZE];
  udp.read(ntp_packet_buf, NTP_PACKET_SIZE);
  udp.stop();

  unsigned long const highWord      = word(ntp_packet_buf[40], ntp_packet_buf[41]);
  unsigned long const lowWord       = word(ntp_packet_buf[42], ntp_packet_buf[43]);
  unsigned long const secsSince1900 = highWord << 16 | lowWord;
  unsigned long const seventyYears  = 2208988800UL;
  unsigned long const epoch         = secsSince1900 - seventyYears;

  return epoch;
}

/**************************************************************************************
 * PRIVATE MEMBER FUNCTIONS
 **************************************************************************************/

void NTPUtils::sendNTPpacket(UDP & udp)
{
  uint8_t ntp_packet_buf[NTP_PACKET_SIZE] = {0};
  
  ntp_packet_buf[0]  = 0b11100011;
  ntp_packet_buf[1]  = 0;
  ntp_packet_buf[2]  = 6;
  ntp_packet_buf[3]  = 0xEC;
  ntp_packet_buf[12] = 49;
  ntp_packet_buf[13] = 0x4E;
  ntp_packet_buf[14] = 49;
  ntp_packet_buf[15] = 52;
  
  udp.beginPacket(NTP_TIME_SERVER, NTP_TIME_SERVER_PORT);
  udp.write(ntp_packet_buf, NTP_PACKET_SIZE);
  udp.endPacket();
}
