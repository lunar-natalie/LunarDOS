// Global Descriptor Table
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "tss.h"
#include <stdint.h>

typedef uint32_t gdt_index_t;

// GDT entry metadata
typedef struct {
    uint32_t base;  // Linear 32-bit address of the start of the segment
    uint32_t limit; // Maximum 20-bit unit addressable by the segment
    uint8_t  access;
    uint8_t  flags;
} gdt_info_t;

// GDT entry data
typedef struct {
    unsigned int limit_low  : 16; // Bits 0-15
    unsigned int base_low   : 24; // Bits 0-15
    unsigned int access     : 8;
    unsigned int limit_high : 4;  // Bits 16-19
    unsigned int reserved   : 1;
    unsigned int flags      : 3;
    unsigned int base_high  : 8; // Bits 24-31
} __attribute__((packed, aligned(4))) gdt_entry_t;

enum { GDT_MAX_LIMIT = 0xFFFFF };

enum GDT_INDEX {
    GDT_INDEX_NULL       = 0,
    GDT_INDEX_RING0_CODE = 1,
    GDT_INDEX_RING0_DATA = 2,
    GDT_INDEX_RING3_CODE = 3,
    GDT_INDEX_RING3_DATA = 4,
    GDT_INDEX_RING0_TSS  = 5,
    GDT_LENGTH           = 6
};

enum GDT_ACCESS {
    GDT_ACCESS_A  = 1 << 0, // Accessed (set by CPU)
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

enum gdt_flags {
    // Granularity - scales the segment limit: clear for 1 byte blocks, set for 4K blocks
    GDT_FLAG_G = 1 << 4,
    // Size flag: clear to define a 16-bit protected mode segment, set to define a 32-bit protected mode segment
    GDT_FLAG_DB = 1 << 3,
    // Long-mode flag: set to define a 64-bit code segment, for all other segment types this flag should be clear
    GDT_FLAG_L = 1 << 2,
};

// Encodes the default GDT entries and loads the GDT
// tss - Pointer to the ring 0 TSS
void init_gdt(const tss_t *tss);

// Encodes the metadata describing a GDT descriptor into a valid entry
void encode_gdt_entry(gdt_entry_t *dest, const gdt_info_t *source);

// Loads the GDT into the GDTR and resets the current segment
// base - Linear 32-bit address of the start of the table
// limit - 16-bit length of the table in bytes minus 1 to allow for 65536 entries in 16 bits
// code_selector - Index of the kernel code segment selector
// data_selector - Index of the kernel data segment selector
extern int load_gdt(gdt_entry_t *base, uint16_t limit, gdt_index_t code_selector, gdt_index_t data_selector);
