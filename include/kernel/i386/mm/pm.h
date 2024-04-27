// Physical memory manager
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <kernel/i386/mm/defs.h>
#include <stddef.h>

// Initializes the page frame allocator
void pm_init(void);

// Allocates a frame on the kernel heap
// Returns the base address of the allocated frame, or 0 if allocation failed
size_t alloc_frame(void);

// Marks the pages in the given frame as free on the kernel heap
// frame - Base address of a previously allocated frame
void free_frame(size_t frame);
