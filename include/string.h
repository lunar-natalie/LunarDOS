// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <stddef.h>

size_t strlen(const char *str);

void *memset(void *dest, int ch, size_t count);
void *memcpy(void *restrict dest, const void *restrict src, size_t count);
