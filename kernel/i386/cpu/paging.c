// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include "paging.h"

#include "control.h"
#include <stddef.h>

static page_dir_entry_t   page_directory[NUM_PAGES] __attribute__((aligned(PAGE_SIZE)));
static page_table_entry_t page_table[NUM_PAGES] __attribute__((aligned(PAGE_SIZE)));

void init_paging(void)
{
    // Set first entry in the page directory to the page table
    page_directory[0].address = (uint32_t)page_table;
    page_directory[0].flags = PAGE_DIRECTORY_FLAG_P | PAGE_DIRECTORY_FLAG_RW;

    // Fill the remaining empty entries in the page directory
    for (size_t i = 1; i < NUM_PAGES; ++i) {
        page_directory[i].flags = PAGE_DIRECTORY_FLAG_RW;
    }

    // Map the first 4M of memory to 4K pages in the page table
    uint32_t address = 0;
    for (size_t i = 0; i < NUM_PAGES; ++i) {
        page_table[i].address = address;
        page_table[i].flags = PAGE_DIRECTORY_FLAG_P | PAGE_DIRECTORY_FLAG_RW;
        address += PAGE_SIZE;
    }

    // Enable paging
    write_cr3((uint32_t)page_directory);
    write_cr0(read_cr0() | (uint32_t)CR0_FLAG_PG);
}
