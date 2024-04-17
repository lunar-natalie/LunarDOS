// Global Descriptor Table
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "tss.h"
#include <stdint.h>

typedef uint8_t  gdt_entry_t;
typedef uint32_t gdt_index_t;

typedef struct {
    uint32_t base;   // 32-bit physical address of the start of the segment
    uint32_t limit;  // Maximum 20-bit offset addressable by the segment
    uint8_t  access; // Access byte
    uint8_t  flags;  // 4-bit flags attribute
} gdt_info_t;

enum { GDT_MAX_LIMIT = 0xFFFFF };

enum GDT_INDEX {
    GDT_INDEX_NULL = 0,
    GDT_INDEX_RING0_CODE,
    GDT_INDEX_RING0_DATA,
    GDT_INDEX_RING3_CODE,
    GDT_INDEX_RING3_DATA,
    GDT_INDEX_RING0_TSS,
    GDT_LENGTH
};

enum GDT_ACCESS {
    GDT_ACCESS_A = 1 << 0,  // Accessed (set by CPU)
    GDT_ACCESS_RW = 1 << 1, // Read-write: clear for read-only (code), set for read-write (data)

    // Direction/conforming
    // Data selectors: if clear, the segment grows up; if set, the segment grows down.
    // Code selectors: if clear, the segment can only be executed from the ring set in the DPL. If set, the segment can
    // be executed from any privilege level.
    GDT_ACCESS_DC = 1 << 2,

    GDT_ACCESS_E = 1 << 3, // Executable
    GDT_ACCESS_S = 1 << 4, // Descriptor type: clear to define a system segment, set for code or data segments

    // Descriptor privilege level (ring 0-3)
    GDT_ACCESS_DPL_1 = 1 << 5,
    GDT_ACCESS_DPL_2 = 1 << 6,
    GDT_ACCESS_DPL_3 = GDT_ACCESS_DPL_1 | GDT_ACCESS_DPL_2,

    GDT_ACCESS_P = 1 << 7 // Present (must be set for any valid segment)
};

enum GDT_FLAG {
    // Long-mode: set to define a 64-bit code segment, for all other segment types this flag should be clear
    GDT_FLAG_L = 1 << 1,
    // Size: clear to define a 16-bit protected mode segment, set to define a 32-bit protected mode segment
    GDT_FLAG_DB = 1 << 2,
    // Granularity: scales the segment limit - clear for 1 byte blocks, set for 4K blocks
    GDT_FLAG_G = 1 << 3
};

// Encodes the default GDT entries and loads the GDT
// tss - Pointer to the kernel TSS
void init_gdt(const tss_t *tss);

// Encodes the metadata describing a GDT descriptor into a valid entry
void encode_gdt_entry(gdt_entry_t *dest, const gdt_info_t *source);

// Loads the GDT into the GDTR and resets the current segment
// base - Linear 32-bit address of the start of the table
// limit - 16-bit length of the table in bytes minus 1 to allow for 65536 entries in 16 bits
// code_selector - Index of the kernel code segment selector
// data_selector - Index of the kernel data segment selector
extern int load_gdt(uint32_t base, uint16_t limit, uint32_t code_selector, uint32_t data_selector);
