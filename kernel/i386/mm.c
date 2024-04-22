// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/i386/mm.h>

#include <stdint.h>
#include <string.h>

extern const uint32_t *kernel_end;

// 1M Heap
uint8_t frame_map[NUM_HEAP_PAGES];

void kalloc_init(void)
{
    // TODO: Implement page frame allocator
    memset(frame_map, PAGE_FREE, NUM_HEAP_PAGES);
}
