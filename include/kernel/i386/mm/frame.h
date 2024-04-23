// Page frame allocator
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <kernel/i386/mm/defs.h>
#include <stddef.h>
#include <stdint.h>

// Allocates a frame on the kernel heap
// Returns the base address of the allocated frame, or -1 if the heap is full
size_t kalloc_frame(void);

// Marks the pages in the given frame as free on the kernel heap
// frame - Base address of a previously allocated frame
void kfree_frame(size_t frame);

// 1M heap of 4K pages split into 8 frames per map entry (1 frame per bit)
enum {
    FRAME_MAP_SIZE = NUM_HEAP_PAGES / sizeof(uint8_t)
};
extern const size_t heap;
static uint8_t frame_map[FRAME_MAP_SIZE];
