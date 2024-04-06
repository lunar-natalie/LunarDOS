// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <string.h>

void *malloc(size_t size)
{
    // TODO
    return 0;
}

void *memcpy(void *restrict dest, const void *restrict src, size_t count)
{
    char       *c_dest = (char *)dest;
    const char *c_src  = (char *)src;
    for (size_t i = 0; i < count; ++i) {
        c_dest[i] = c_src[i];
    }
    return dest;
}
