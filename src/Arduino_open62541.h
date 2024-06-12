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
#include "o1heap/o1heap.h"

#include "ArduinoOpta.h"
#include "ArduinoOptaVariant.h"

/**************************************************************************************
 * DEFINES
 **************************************************************************************/

#if !defined(ARDUINO_OPTA)
# error "This library does only support Arduino Opta"
#endif
