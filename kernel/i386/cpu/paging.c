// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include "paging.h"

#include "control.h"
#include <stddef.h>

static page_dir_entry_t   page_directory[NUM_PAGES];
static page_table_entry_t page_table[NUM_PAGES];

void paging_init(void)
{
    // Add first page directory entry pointing to the page table
    encode_page_dir_entry(
        page_directory, (uint32_t)page_table, (uint8_t)(PAGE_DIRECTORY_FLAG_P | PAGE_DIRECTORY_FLAG_RW));

    // Fill remaining entries
    for (size_t i = 1; i < NUM_PAGES; ++i) {
        encode_page_dir_entry(page_directory + i, (uint32_t)0, (uint8_t)PAGE_DIRECTORY_FLAG_RW);
    }

    // Map the first 4M of memory to 4K pages in the page table
    uint32_t address = 0;
    for (size_t i = 0; i < NUM_PAGES; ++i) {
        encode_page_table_entry(page_table + i, address, (uint16_t)(PAGE_DIRECTORY_FLAG_P | PAGE_DIRECTORY_FLAG_RW));
        address += PAGE_SIZE;
    }

    // Enable paging
    write_cr3((uint32_t)page_directory);
    write_cr0(read_cr0() | (uint32_t)(CR0_FLAG_PG));
}
