/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information.
 *
 *    Copyright 2016-2017 (c) Fraunhofer IOSB (Author: Julius Pfrommer)
 *    Copyright 2017 (c) Stefan Profanter, fortiss GmbH
 *    Copyright 2017 (c) Thomas Stalder, Blue Time Concept SA
 */

#include "../../open62541.h"

#include <time.h>

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

int clock_gettime(clockid_t clk_id, struct timespec *tp)
{
  tp->tv_sec = millis() / 1000;
  tp->tv_nsec = (millis() % 1000) * 1000000;
  return 0;
}

UA_DateTime UA_DateTime_now(void)
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * UA_DATETIME_SEC) + (tv.tv_usec * UA_DATETIME_USEC) + UA_DATETIME_UNIX_EPOCH;
}

/* Credit to https://stackoverflow.com/questions/13804095/get-the-time-zone-gmt-offset-in-c */
UA_Int64 UA_DateTime_localTimeUtcOffset(void)
{
  time_t gmt, rawtime = time(NULL);
  struct tm *ptm;
  struct tm gbuf;
  ptm = gmtime_r(&rawtime, &gbuf);
  // Request that mktime() looksup dst in timezone database
  ptm->tm_isdst = -1;
  gmt = mktime(ptm);
  return (UA_Int64) (difftime(rawtime, gmt) * UA_DATETIME_SEC);
}

UA_DateTime UA_DateTime_nowMonotonic(void)
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * UA_DATETIME_SEC) + (tv.tv_usec * UA_DATETIME_USEC) + UA_DATETIME_UNIX_EPOCH;
}

#ifdef __cplusplus
}
#endif
