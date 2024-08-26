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
#include "util/time/cvt_time.h"
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

#define OPCUA_MAX_OPTA_EXPANSION_NUM (2u)
