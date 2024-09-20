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

#include "open62541.h"

#include "util/o1heap/o1heap.h"
#include "util/o1heap/o1heap_wrapper.h"
#include "util/time/timeToStr.h"
#include "util/time/NTPUtils.h"
#include "util/toStr/ExpansionType.h"

#include "Opta.h"
#include "OptaVariant.h"
#include "OptaExpansionManager.h"

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

#if !defined(ARDUINO_OPTA)
# error "This library does only support Arduino Opta"
#endif

/* Note: exposing properties via OPC UA is extremely
 * RAM hungry. We therefore need to limit the number
 * of supported Opta expansion modules via OPC UA.
 */
#define OPCUA_MAX_OPTA_EXPANSION_NUM (2u)
