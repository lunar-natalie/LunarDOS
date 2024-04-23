// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include "kernel/mm.h"

#include <kernel/i386/mm/frame.h>

void *kmalloc(size_t size)
{
    return (void *)0;
}

void kfree(void *ptr)
{
}
