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

#include "cvt_time.h"

#include <stdio.h>
#include <string.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace opcua
{

/**************************************************************************************
 * FUNCTION DEFINITION
 **************************************************************************************/

time_t cvt_time(char const * time)
{
  static time_t build_time = 0;

  if (!build_time) {
    char s_month[5];
    int month, day, year;
    struct tm t =
      {
        0 /* tm_sec   */,
        0 /* tm_min   */,
        0 /* tm_hour  */,
        0 /* tm_mday  */,
        0 /* tm_mon   */,
        0 /* tm_year  */,
        0 /* tm_wday  */,
        0 /* tm_yday  */,
        0 /* tm_isdst */
      };
    static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";

    sscanf(time, "%s %d %d", s_month, &day, &year);

    month = (strstr(month_names, s_month) - month_names) / 3;

    t.tm_mon = month;
    t.tm_mday = day;
    t.tm_year = year - 1900;
    t.tm_isdst = -1;

    build_time = mktime(&t);
  }

  return build_time;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* opcua */
