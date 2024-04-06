// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include "string.h"

size_t strlen(const char *str)
{
    size_t len = 0;
    while (str[len]) {
        ++len;
    }
    return len;
}
