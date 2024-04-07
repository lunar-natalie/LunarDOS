// Global Descriptor Table
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "tss.h"
#include <stdint.h>

// GDT entry metadata
typedef struct {
    uint32_t base;  // Linear 32-bit address of the start of the segment
    uint32_t limit; // Maximum 20-bit unit addressable by the segment
    uint8_t  access;
    uint8_t  flags;
} gdt_info_t;

#define GDT_MAX_LIMIT 0xFFFFF

// GDT entry data
typedef struct {
    unsigned int limit_low  : 16; // Limit bits 0-15
    unsigned int base_low   : 24; // Base bits 0-15
    unsigned int access     : 8;  // Access byte
    unsigned int limit_high : 4;  // Limit bits 16-19
    unsigned int reserved   : 1;
    unsigned int flags      : 3; // Flags byte
    unsigned int base_high  : 8; // Base bits 24-31
} __attribute__((packed, aligned(4))) gdt_entry_t;

typedef uint8_t gdt_index_t;
enum gdt_index : gdt_index_t {
    GDT_INDEX_NULL       = 0,
    GDT_INDEX_RING0_CODE = 1,
    GDT_INDEX_RING0_DATA = 2,
    GDT_INDEX_RING3_CODE = 3,
    GDT_INDEX_RING3_DATA = 4,
    GDT_INDEX_RING0_TSS  = 5,
    GDT_LENGTH           = 6
};

enum gdt_access_bits {
    // Present bit (must be set for any valid segment)
    GDT_ACCESS_P = 0b10000000,
    // Descriptor privilege level (ring 0-3)
    GDT_ACCESS_DPL_1 = 0b00100000,
    GDT_ACCESS_DPL_2 = 0b01000000,
    GDT_ACCESS_DPL_3 = 0b01100000,
    // Descriptor type bit: clear to define a system segment, set for code or data segments.
    GDT_ACCESS_S = 0b00010000,
    // Executable bit
    GDT_ACCESS_E = 0b00001000,
    // Direction/conforming bit:
    // Data selectors: if clear, the segment grows up; if set, the segment grows down.
    // Code selectors: if clear, the segment can only be executed from the ring set in the DPL. If set, the segment can
    // be executed from any privilege level.
    GDT_ACCESS_DC = 0b00000100,
    // Read-write bit: clear for read-only (code), set for read-write (data).
    GDT_ACCESS_RW = 0b00000010,
    // Accessed bit (set by CPU)
    GDT_ACCESS_A = 0b00000001
};

enum gdt_flag_bits {
    // Granularity flag. Scales the segment limit: clear for 1 byte blocks, set for 4K blocks.
    GDT_FLAG_G = 0b00001000,
    // Size flag: clear to define a 16-bit protected mode segment, set to define a 32-bit protected mode segment.
    GDT_FLAG_DB = 0b00000100,
    // Long-mode flag: set to define a 64-bit code segment. For all other segment types this flag should be clear.
    GDT_FLAG_L = 0b00000010,
};

// Encodes the default GDT entries and loads the GDT.
// tss - Pointer to the TSS for ring 0.
void gdt_init(const tss_t *tss);

// Encodes the metadata describing a GDT descriptor into a valid entry.
void encode_gdt_entry(gdt_entry_t *dest, const gdt_info_t *source);

// Loads the GDT into the GDTR.
// base - Linear 32-bit address of the start of the table.
// limit - 16-bit length of the table in bytes minus 1 to allow for 65536 entries in 16 bits.
// Returns 0 if the GDT is valid.
extern int load_gdt(gdt_entry_t *base, uint16_t limit);
