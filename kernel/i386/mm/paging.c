// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/i386/mm/paging.h>

#include <kernel/i386/cpu/cr.h>
#include <kernel/i386/mm/defs.h>

// Identity paging for the first 4M, split into 4K pages
static uint32_t page_directory[NUM_PAGES] __attribute__((aligned(PAGE_SIZE)));
static uint32_t page_table[NUM_PAGES] __attribute__((aligned(PAGE_SIZE)));

void paging_init(void)
{
    // Set the first page directory entry to point to the page table
    page_directory[0] = (uint32_t)page_table | PAGE_DIRECTORY_FLAG_P | PAGE_DIRECTORY_FLAG_RW;

    // Fill the remaining entries in the page directory
    for (uint32_t i = 1; i < NUM_PAGES; ++i) {
        page_directory[i] = 0 | PAGE_DIRECTORY_FLAG_RW;
    }

    // Fill the page table
    for (uint32_t i = 0, address = 0; i < NUM_PAGES; ++i) {
        page_table[i] = address | PAGE_TABLE_FLAG_P | PAGE_DIRECTORY_FLAG_RW;
        address += PAGE_SIZE;
    }

    // Enable paging
    write_cr3((uint32_t)page_directory);
    write_cr0(read_cr0() | CR0_FLAG_PG);
}
