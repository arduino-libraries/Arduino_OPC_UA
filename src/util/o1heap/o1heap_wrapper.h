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

#include <stdlib.h>

/**************************************************************************************
 * FUNCTION DECLARATION
 **************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

void * o1heap_malloc(size_t size);
void o1heap_free(void * ptr);
void * o1heap_calloc(size_t nelem, size_t elsize);
void * o1heap_realloc(void * old_ptr, size_t size);

#ifdef __cplusplus
}
#endif
