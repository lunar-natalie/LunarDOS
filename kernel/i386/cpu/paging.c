// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include "paging.h"

#include "control.h"

static page_entry_t page_directory[NUM_PAGES] __attribute__((aligned(PAGE_SIZE)));
static page_entry_t page_table[NUM_PAGES] __attribute__((aligned(PAGE_SIZE)));

void init_paging(void)
{
    // Set the first entry in the page directory to point to the page table
    page_directory[0] = (uint32_t)page_table | PAGE_DIRECTORY_FLAG_P | PAGE_DIRECTORY_FLAG_RW;

    // Fill the remaining entries in the page directory
    for (page_entry_t i = 1; i < NUM_PAGES; ++i) {
        page_directory[i] = 0 | PAGE_DIRECTORY_FLAG_RW;
    }

    // Map the first 4M of memory to 4K pages in the page table
    uint32_t address = 0;
    for (page_entry_t i = 0; i < NUM_PAGES; ++i) {
        page_table[i] = address | PAGE_TABLE_FLAG_P | PAGE_DIRECTORY_FLAG_RW;
        address += PAGE_SIZE;
    }

    // Enable paging
    write_cr3((uint32_t)page_directory);
    write_cr0(read_cr0() | CR0_FLAG_PG);
}
