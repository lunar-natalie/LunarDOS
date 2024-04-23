// Page frame allocator
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <kernel/i386/mm/paging.h>
#include <stddef.h>
#include <stdint.h>

enum {
    PAGE_FREE = 0,
    PAGE_USED = 1,

    // 1M heap of 4K pages split into 8 pages per frame (1 page per bit)
    NUM_FRAME_PAGES = NUM_HEAP_PAGES / sizeof(uint8_t),

    // Maximum number of frames which can be allocated before allocating a new set of pre-frames
    PRE_FRAME_LIMIT = 20
};

void kalloc_init(void);
size_t kalloc_frame(void);
void kfree_frame(size_t frame);
