// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/i386/mm/vm.h>
#include <kernel/vm.h>

#include <kernel/i386/mm/defs.h>
#include <string.h>

static block_t blocks[NUM_HEAP_PAGES]; // Maximum size of 1 page per block

void init_vm(void)
{
    memset(blocks, 0, NUM_HEAP_PAGES * sizeof(block_t));
}

void *kmalloc(size_t size)
{
    // Unimplemented
    return (void *)0;
}

void kfree(void *ptr)
{
    // Unimplemented
}
