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

#include <PortentaEthernet.h>
#include "../open62541.h"

/**************************************************************************************
 * GLUE CODE
 **************************************************************************************/

extern "C"
{

  int gethostname(char *str, size_t len)
  {
    String ip = Ethernet.localIP().toString();
    memset(str, 0, len);
    memcpy(str, ip.c_str(), ip.length());
    return 0;
  }

  UA_StatusCode registerFakeInterrupt(UA_InterruptManager *im, uintptr_t interruptHandle, const UA_KeyValueMap *params,  UA_InterruptCallback callback, void *interruptContext)
  {
    return UA_STATUSCODE_GOOD;
  }

  void deregisterFakeInterrupt(UA_InterruptManager *im, uintptr_t interruptHandle)
  {
    return;
  }

  UA_StatusCode startFakeInterruptManager(UA_EventSource *es)
  {
    return UA_STATUSCODE_GOOD;
  }

  void stopFakeInterruptManager(UA_EventSource *es)
  {
    return;
  }

  UA_StatusCode freeFakeInterruptManager(UA_EventSource *es)
  {
    return UA_STATUSCODE_GOOD;
  }

  UA_InterruptManager *UA_InterruptManager_new_POSIX(const UA_String eventSourceName)
  {
    static UA_InterruptManager im;
    static UA_String name = UA_String_fromChars("fakeES");
    im.eventSource.eventSourceType = UA_EVENTSOURCETYPE_INTERRUPTMANAGER;
    UA_String_copy(&eventSourceName, &name);
    im.eventSource.start = startFakeInterruptManager;
    im.eventSource.stop = stopFakeInterruptManager;
    im.eventSource.free = freeFakeInterruptManager;
    im.registerInterrupt = registerFakeInterrupt;
    im.deregisterInterrupt = deregisterFakeInterrupt;
    return &im;
  }

  UA_ConnectionManager *UA_ConnectionManager_new_POSIX_UDP(const UA_String eventSourceName)
  {
    return nullptr;
  }

} /* extern "C" */
