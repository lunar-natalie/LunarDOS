// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <stdlib.h>
#include <string.h>

#include <kernel/vm.h>

void *memset(void *dest, int ch, size_t count)
{
    char *ch_dest = (char *)dest;
    for (size_t i = 0; i < count; ++i) {
        ch_dest[i] = ch;
    }
    return dest;
}

void *memcpy(void *restrict dest, const void *restrict src, size_t count)
{
    char *ch_dest = (char *)dest;
    const char *ch_src = (char *)src;
    for (size_t i = 0; i < count; ++i) {
        ch_dest[i] = ch_src[i];
    }
    return dest;
}

void *malloc(size_t size)
{
    return kmalloc(size);
}

void free(void *ptr)
{
    kfree(ptr);
}
