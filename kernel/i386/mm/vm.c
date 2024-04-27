// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/i386/mm/vm.h>
#include <kernel/mm.h>

#include <kernel/i386/mm/pm.h>
#include <string.h>

static block_t block_map[NUM_HEAP_PAGES]; // Maximum size of 1 page per block

void vm_init(void)
{
    memset(block_map, 0, NUM_HEAP_PAGES * sizeof(block_t));
}

void *kmalloc(size_t size)
{
    // Find the next free block
    size_t next_free_block = 0;
    while (block_map[next_free_block].base != 0) {
        ++next_free_block;
        if (next_free_block == sizeof(block_map)) {
            return (void *)0; // Out of blocks
        }
    }

    // Allocate the first frame
    size_t first_frame = alloc_frame();
    if (first_frame == 0) {
        return (void *)0; // Failed to allocate
    }
    block_map[next_free_block].base = first_frame;
    block_map[next_free_block].size = size;

    // Allocate enough frames to store the rest of the buffer
    while (size > 0) {
        if (alloc_frame() == 0) {
            return (void *)0; // End of memory
        }
        size -= PAGE_SIZE;

        // Last page
        if (size < PAGE_SIZE) {
            size = 0;
        }
    }

    return (void *)first_frame;
}

void kfree(void *ptr)
{
    // Find the block containing the given address
    size_t block = 0;
    while (block_map[block].base != (size_t)ptr) {
        ++block;
        if (block == sizeof(block_map)) {
            return; // Block not found
        }
    }

    // Free the corresponding frames
    while (block_map[block].size > 0) {
        free_frame(block_map[block].base);
        block_map[block].base -= PAGE_SIZE;
        block_map[block].size -= PAGE_SIZE;
    }

    // Mark the block as free
    memset(block_map + block, 0, sizeof(block_t));
}
