// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/i386/mm/frame.h>

#include <stdbool.h>

static uint8_t frame_map[FRAME_MAP_SIZE];

static size_t kalloc_next_frame(void);

size_t kalloc_frame(void)
{
    static bool alloc = true;
    static size_t p_frame = 0;
    static size_t pre_frames[NUM_HEAP_PAGES];

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

    size_t frame = pre_frames[p_frame];
    ++p_frame;    // Next frame
    return frame; // Return first free frame
}

static size_t kalloc_next_frame(void)
{
    // Traverse frame map
    size_t p_entry = 0;
    uint8_t bit = 0;
    while ((frame_map[p_entry] | bit) == 0) {
        ++bit;
        if (bit == sizeof(uint8_t)) {
            ++p_entry;
        }
        if (p_entry == sizeof(frame_map)) {
            return 0; // Heap full (null address)
        }
    }

    frame_map[p_entry] |= USED << bit;         // Mark frame as used
    return heap + (p_entry * bit * PAGE_SIZE); // Return the address of the next frame
}

void kfree_frame(size_t frame)
{
    frame -= heap; // Get offset from the first frame on the heap
    size_t p_frame = frame / PAGE_SIZE;
    frame_map[p_frame] = FREE;
}
