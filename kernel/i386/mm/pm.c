// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/i386/mm/pm.h>

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

static size_t alloc_next_frame(void);

// 1M heap of 4K pages split into 8 frames per map entry (1 frame per bit)
extern const size_t heap;
static uint8_t frame_map[NUM_HEAP_PAGES / sizeof(uint8_t)];
static size_t pre_frames[NUM_HEAP_PAGES];

void pm_init(void)
{
    memset(frame_map, 0, sizeof(frame_map));
}

size_t alloc_frame(void)
{
    static bool alloc = true;
    static size_t frame_index = 0;

    // Allocate a new set of pre-frames every 20 pages
    if (frame_index == PRE_FRAME_LIMIT) {
        alloc = true;
    }
    if (alloc) {
        for (size_t i = 0; i < PRE_FRAME_LIMIT; ++i) {
            pre_frames[i] = alloc_next_frame();
            if (pre_frames[i] == 0) {
                return 0; // Failed to allocate
            }
        }
        frame_index = 0;
        alloc = false;
    }

    size_t frame = pre_frames[frame_index]; // Address of the first free frame
    ++frame_index;                          // Next frame
    return frame;
}

static size_t alloc_next_frame(void)
{
    // Traverse the bitmap for the next free frame
    size_t entry_index = 0;
    uint8_t bit = 0;
    while ((frame_map[entry_index] | bit) == 0) {
        ++bit;
        if (bit == sizeof(uint8_t)) {
            ++entry_index;
        }
        if (entry_index == sizeof(frame_map)) {
            return 0; // Heap full
        }
    }

    frame_map[entry_index] |= 1 << bit;            // Mark frame as used
    return heap + (entry_index * bit * PAGE_SIZE); // Return the address
}

void free_frame(size_t frame)
{
    frame -= heap;      // Get offset from the first frame on the heap
    frame /= PAGE_SIZE; // Get index from address

    size_t entry_index = frame / sizeof(uint8_t);          // Frame index to the nearest 8 pages
    uint8_t bit = frame - (entry_index * sizeof(uint8_t)); // Remainder of integer division

    frame_map[entry_index] &= ~(1 << bit); // Mark frame as free
}
