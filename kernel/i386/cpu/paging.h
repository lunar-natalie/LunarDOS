// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <stdint.h>

typedef struct {
    unsigned int address   : 20; // 4K-aligned physical address of the page (bits 31-12)
    unsigned int available : 4;  // Unused
    unsigned int flags     : 8;
} __attribute__((packed)) page_dir_entry_t;

typedef struct {
    unsigned int address   : 20; // 4K-aligned physical address mapped to an empty 4K block (bits 31-12)
    unsigned int available : 3;  // Unused
    unsigned int flags     : 9;
} __attribute__((packed)) page_table_entry_t;

enum PAGE_DIRECTORY_FLAG {
    PAGE_DIRECTORY_FLAG_P   = 1 << 0, // Present
    PAGE_DIRECTORY_FLAG_RW  = 1 << 1, // Read/write
    PAGE_DIRECTORY_FLAG_US  = 1 << 2, // User/supervisor (unset for supervisor only)
    PAGE_DIRECTORY_FLAG_PWT = 1 << 3, // Write-through
    PAGE_DIRECTORY_FLAG_PCD = 1 << 4, // Cache disable
    PAGE_DIRECTORY_FLAG_A   = 1 << 5, // Accessed
    PAGE_DIRECTORY_FLAG_AVL = 1 << 6, // Available
    PAGE_DIRECTORY_FLAG_PS  = 1 << 7  // Page size (set for 4M pages)
};

enum PAGE_TABLE_FLAG {
    PAGE_TABLE_FLAG_P   = PAGE_DIRECTORY_FLAG_P,
    PAGE_TABLE_FLAG_RW  = PAGE_DIRECTORY_FLAG_RW,
    PAGE_TABLE_FLAG_US  = PAGE_DIRECTORY_FLAG_US,
    PAGE_TABLE_FLAG_PWT = PAGE_DIRECTORY_FLAG_PWT,
    PAGE_TABLE_FLAG_PCD = PAGE_DIRECTORY_FLAG_PCD,
    PAGE_TABLE_FLAG_A   = PAGE_DIRECTORY_FLAG_A,
    PAGE_TABLE_FLAG_D   = 1 << 6, // Dirty
    PAGE_TABLE_FLAG_PAT = 1 << 7, // Page Attribute Table
    PAGE_TABLE_FLAG_G   = 1 << 8  // Global
};

enum { NUM_PAGES = 1024, PAGE_SIZE = 0x1000 };

void init_paging(void);
