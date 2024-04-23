// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/i386/mm/alloc.h>

#include <kernel/defs.h>
#include <string.h>
#include <stdbool.h>

// 1M heap of 4K pages split into 8 frames per map entry (1 frame per bit)
extern const size_t heap;
uint8_t frame_map[NUM_HEAP_PAGES / sizeof(uint8_t)];
size_t pre_frames[NUM_HEAP_PAGES];

static size_t kalloc_next_frame(void);

void kalloc_init(void)
{
    memset(frame_map, FRAME_FREE, sizeof(frame_map));
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

    size_t frame = pre_frames[p_frame];
    ++p_frame; // Next frame
    return frame; // Return first free frame
}

static size_t kalloc_next_frame(void)
{
    // Traverse frame map
    size_t p_frame = 0;
    uint8_t bit = 0;
    while ((frame_map[p_frame] | bit) == 0) {
        ++bit; // Next bit
        if (bit == sizeof(uint8_t)) {
            ++p_frame; // Next frame
        }
        if (p_frame == NUM_HEAP_PAGES) {
            return ERROR_FAILURE; // Heap full
        }
    }

    frame_map[p_frame] |= FRAME_USED << bit; // Mark frame as used
    return heap + (p_frame * PAGE_SIZE); // Return the address of the next frame
}

void kfree_frame(size_t frame)
{
    frame -= heap; // Get offset from the first frame on the heap
    size_t p_frame = frame / PAGE_SIZE;
    frame_map[p_frame] = FRAME_FREE;
}
