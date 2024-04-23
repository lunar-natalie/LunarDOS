// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/i386/mm/alloc.h>

#include <kernel/defs.h>
#include <string.h>
#include <stdbool.h>

static size_t kalloc_next_frame(void);

extern const size_t heap;
uint8_t frame_map[NUM_FRAME_PAGES];
size_t pre_frames[NUM_HEAP_PAGES];

void kalloc_init(void)
{
    memset(frame_map, PAGE_FREE, NUM_FRAME_PAGES);
}

size_t kalloc_frame(void)
{
    static bool alloc = true;
    static size_t p_frame = 0;

    // Allocate a new set of pre-frames every 20 pages
    if (p_frame == PRE_FRAME_LIMIT) {
        alloc = true;
    }
    if (alloc) {
        for (size_t i = 0; i < PRE_FRAME_LIMIT; ++i) {
            pre_frames[i] = kalloc_next_frame();
        }
        p_frame = 0;
        alloc = false;
    }

    size_t frame = pre_frames[p_frame]; // Return first free frame
    ++p_frame; // Next frame
    return frame;
}

static size_t kalloc_next_frame(void)
{
    // Traverse frame map
    size_t p_frame = 0;
    uint8_t bit = 0;
    while ((frame_map[p_frame] | bit) == 0) {
        ++bit;
        if (bit == sizeof(uint8_t)) {
            ++p_frame;
        }
        if (p_frame == NUM_HEAP_PAGES) {
            return ERROR_FAILURE;
        }
    }

    frame_map[p_frame] |= PAGE_USED << bit; // Mark page as used
    return heap + (p_frame * PAGE_SIZE); // Return the address of the next frame
}

void kfree_frame(size_t frame)
{
    frame -= heap; // Get offset from first frame
    size_t p_frame = frame / PAGE_SIZE;
    frame_map[p_frame] = PAGE_FREE;
}
