// Global Descriptor Table
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <stdint.h>
#include <kernel/i386/cpu/tss.h>

enum GDT_INDEX {
    GDT_INDEX_NULL,
    GDT_INDEX_CODE_PL0,
    GDT_INDEX_DATA_PL0,
    GDT_INDEX_CODE_PL3,
    GDT_INDEX_DATA_PL3,
    GDT_INDEX_TSS_PL0,
    GDT_NUM_ENTRIES
};

enum {
    GDT_MAX_ENTRY_LIMIT = 0xFFFFF,              // Maximum limit for a GDT entry
    GDT_ENTRY_SIZE = sizeof(uint64_t),          // Size of each GDT entry in bytes
    GDT_SIZE = GDT_NUM_ENTRIES * GDT_ENTRY_SIZE // Size of the GDT in bytes
};

enum GDT_ACCESS {
    GDT_ACCESS_A = 1 << 0,  // Accessed (set by CPU)
    GDT_ACCESS_RW = 1 << 1, // Read-write: clear for read-only (code), set for read-write (data)

    // Direction/conforming
    // Data selectors: if clear, the segment grows up; if set, the segment grows down
    // Code selectors: if clear, the segment can only be executed from the ring set in the DPL; if set, the segment can
    // be executed from any privilege level
    GDT_ACCESS_DC = 1 << 2,

    GDT_ACCESS_E = 1 << 3, // Executable
    GDT_ACCESS_S = 1 << 4, // Descriptor type: clear to define a system segment, set for code or data segments

    // Descriptor privilege level (ring 0-3)
    GDT_ACCESS_DPL_1 = 1 << 5,
    GDT_ACCESS_DPL_2 = 1 << 6,
    GDT_ACCESS_DPL_3 = GDT_ACCESS_DPL_1 | GDT_ACCESS_DPL_2,

    GDT_ACCESS_P = 1 << 7 // Present (must be set for any valid segment)
};

// Access flags for system segments
enum GDT_ACCESS_SYSTEM {
    // Types (protected mode)
    GDT_ACCESS_SYSTEM_TSS16_AVL = 0x1,  // 16-bit TSS (available)
    GDT_ACCESS_SYSTEM_LDT = 0x2,        // LDT
    GDT_ACCESS_SYSTEM_TSS16_BUSY = 0x3, // 16-bit TSS (busy)
    GDT_ACCESS_SYSTEM_TSS32_AVL = 0x9,  // 32-bit TSS (available)
    GDT_ACCESS_SYSTEM_TSS32_BUSY = 0xB, // 32-bit TSS (busy)

    GDT_ACCESS_SYSTEM_DPL_1 = GDT_ACCESS_DPL_1,
    GDT_ACCESS_SYSTEM_DPL_2 = GDT_ACCESS_DPL_2,
    GDT_ACCESS_SYSTEM_DPL_3 = GDT_ACCESS_DPL_3,
    GDT_ACCESS_SYSTEM_P = GDT_ACCESS_P
};

enum GDT_FLAG {
    // Long-mode: set to define a 64-bit code segment, clear for all other segment types
    GDT_FLAG_L = 1 << 1,
    // Size: set to define a 32-bit protected mode segment, clear to define a 16-bit protected mode segment
    GDT_FLAG_DB = 1 << 2,
    // Granularity: scales the segment limit - set for 4K blocks, clear for 1 byte blocks
    GDT_FLAG_G = 1 << 3
};

// Entry types
enum GDT_TYPE {
    GDT_CODE_PL0_ACCESS = GDT_ACCESS_P | GDT_ACCESS_S | GDT_ACCESS_RW | GDT_ACCESS_E,
    GDT_CODE_PL0_FLAGS = GDT_FLAG_G | GDT_FLAG_DB,

    GDT_DATA_PL0_ACCESS = GDT_ACCESS_P | GDT_ACCESS_S | GDT_ACCESS_RW,
    GDT_DATA_PL0_FLAGS = GDT_FLAG_G | GDT_FLAG_DB,

    GDT_CODE_PL3_ACCESS = GDT_ACCESS_P | GDT_ACCESS_S | GDT_ACCESS_RW | GDT_ACCESS_E | GDT_ACCESS_DPL_3,
    GDT_CODE_PL3_FLAGS = GDT_FLAG_G | GDT_FLAG_DB,

    GDT_DATA_PL3_ACCESS = GDT_ACCESS_P | GDT_ACCESS_S | GDT_ACCESS_RW | GDT_ACCESS_DPL_3,
    GDT_DATA_PL3_FLAGS = GDT_FLAG_G | GDT_FLAG_DB,

    GDT_TSS_PL0_ACCESS = GDT_ACCESS_SYSTEM_P | GDT_ACCESS_SYSTEM_TSS32_AVL,
    GDT_TSS_PL0_FLAGS = 0
};

// Segment selectors
enum GDT_SEL {
    GDT_SEL_CODE_PL0 = GDT_ENTRY_SIZE * GDT_INDEX_CODE_PL0,
    GDT_SEL_DATA_PL0 = GDT_ENTRY_SIZE * GDT_INDEX_DATA_PL0,

    GDT_SEL_CODE_PL3 = GDT_ENTRY_SIZE * GDT_INDEX_CODE_PL3,
    GDT_SEL_DATA_PL3 = GDT_ENTRY_SIZE * GDT_INDEX_DATA_PL3,

    GDT_SEL_TSS_PL0 = GDT_ENTRY_SIZE * GDT_INDEX_TSS_PL0
};

// Encodes the GDT entries, loads the GDTR and updates the current segment
// tss - Pointer to the kernel TSS
void gdt_init(const tss_t *tss);

// Encodes the attributes describing a GDT descriptor into a valid entry
// selector - Segment selector of the destination entry in the GDT
// base - Physical address of the start of the segment
// limit - Maximum 20-bit offset addressable by the segment
// access - Access byte
// flags - Flags attribute (4 bits)
void encode_gdt_entry(uint16_t selector, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);

// Loads the GDT into the GDTR and updates the current segment
// base - Linear address of the start of the table
// limit - Length of the table in bytes minus 1 to allow for a maximum effective limit of 65536 bytes (8192 entries)
// code_selector - Kernel code segment selector
// data_selector - Kernel data segment selector
extern void load_gdt(uint32_t base, uint16_t limit, uint16_t code_selector, uint16_t data_selector);
