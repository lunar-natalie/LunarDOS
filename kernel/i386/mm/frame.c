// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/i386/mm/frame.h>

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

static size_t alloc_next_frame(void);

// 1M heap of 4K pages split into 8 frames per map entry (1 frame per bit)
extern const size_t heap;
static uint8_t frame_map[NUM_HEAP_PAGES / sizeof(uint8_t)];
static size_t pre_frames[NUM_HEAP_PAGES];

void init_page_frames(void)
{
    memset(frame_map, 0, sizeof(frame_map));
}

size_t alloc_frame(void)
{
    static bool alloc = true;
    static size_t p_frame = 0;

    // Allocate a new set of pre-frames every 20 pages
    if (p_frame == PRE_FRAME_LIMIT) {
        alloc = true;
    }
    if (alloc) {
        for (size_t i = 0; i < PRE_FRAME_LIMIT; ++i) {
            pre_frames[i] = alloc_next_frame();
            if (pre_frames[i] == 0) {
                return 0; // Failed to allocate
            }
        }
        p_frame = 0;
        alloc = false;
    }

    size_t frame = pre_frames[p_frame]; // First free frame
    ++p_frame;                          // Next frame
    return frame;
}

static size_t alloc_next_frame(void)
{
    size_t p_entry = 0;
    uint8_t bit = 0;

    // Traverse the bitmap for the next free frame
    while ((frame_map[p_entry] | bit) == 0) {
        ++bit;
        if (bit == sizeof(uint8_t)) {
            ++p_entry;
        }
        if (p_entry == sizeof(frame_map)) {
            return 0; // Heap full
        }
    }

    frame_map[p_entry] |= 1 << bit;            // Mark frame as used
    return heap + (p_entry * bit * PAGE_SIZE); // Return the address
}

void free_frame(size_t frame)
{
    size_t p_entry;
    uint8_t bit;

    frame -= heap;                             // Get offset from the first frame on the heap
    frame /= PAGE_SIZE;                        // Get index from address
    p_entry = frame / sizeof(uint8_t);         // Entry index is the frame index to the nearest 8 pages
    bit = frame - (p_entry * sizeof(uint8_t)); // Bit number within the entry is the remainder of integer division

    frame_map[p_entry] &= ~(1 << bit); // Mark frame as free
}
