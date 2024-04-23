// Page frame allocator
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <kernel/i386/mm/paging.h>
#include <stddef.h>

enum {
    FREE = 0,
    USED = 1,

    // Maximum number of frames which can be allocated before allocating a new set of pre-frames
    PRE_FRAME_LIMIT = 20
};

// Allocates a frame on the kernel heap
// Returns the base address of the allocated frame, or -1 if the heap is full
size_t kalloc_frame(void);

// Marks the pages in the given frame as free on the kernel heap
// frame - Base address of a previously allocated frame
void kfree_frame(size_t frame);
