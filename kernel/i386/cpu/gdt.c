// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include "gdt.h"

#include "tss.h"
#include <kernel/error.h>

// Flat GDT mapping where the entire virtual address space is mapped for each segment
// Consists of the null descriptor, two kernel segments, two userspace segments and the kernel TSS
static gdt_entry_t gdt[GDT_SIZE] __attribute__((aligned(4)));

// Array of pointers to GDT info structures describing the entry for each segment, excluding the null descriptor
static gdt_info_t *gdt_info[GDT_LENGTH - 1];
static gdt_info_t gdt_ring0_code; // Kernel code segment
static gdt_info_t gdt_ring0_data; // Kernel data segment
static gdt_info_t gdt_ring3_code; // Userspace code segment
static gdt_info_t gdt_ring3_data; // Userspace data segment
static gdt_info_t gdt_ring0_tss;  // Task state segment

void init_gdt(const tss_t *tss)
{
    // Kernel code segment
    gdt_ring0_code.base = 0;
    gdt_ring0_code.limit = GDT_MAX_ENTRY_LIMIT;
    gdt_ring0_code.access = GDT_ACCESS_P | GDT_ACCESS_S | GDT_ACCESS_RW | GDT_ACCESS_E;
    gdt_ring0_code.flags = GDT_FLAG_G | GDT_FLAG_DB;
    gdt_info[GDT_INDEX_RING0_CODE - 1] = &gdt_ring0_code;

    // Kernel data segment
    gdt_ring0_data.base = 0;
    gdt_ring0_data.limit = GDT_MAX_ENTRY_LIMIT;
    gdt_ring0_data.access = GDT_ACCESS_P | GDT_ACCESS_S | GDT_ACCESS_RW;
    gdt_ring0_data.flags = GDT_FLAG_G | GDT_FLAG_DB;
    gdt_info[GDT_INDEX_RING0_DATA - 1] = &gdt_ring0_data;

    // Userspace code segment
    gdt_ring3_code.base = 0;
    gdt_ring3_code.limit = GDT_MAX_ENTRY_LIMIT;
    gdt_ring3_code.access = GDT_ACCESS_P | GDT_ACCESS_S | GDT_ACCESS_RW | GDT_ACCESS_E | GDT_ACCESS_DPL_3;
    gdt_ring3_code.flags = GDT_FLAG_G | GDT_FLAG_DB;
    gdt_info[GDT_INDEX_RING3_CODE - 1] = &gdt_ring3_code;

    // Userspace data segment
    gdt_ring3_data.base = 0;
    gdt_ring3_data.limit = GDT_MAX_ENTRY_LIMIT;
    gdt_ring3_data.access = GDT_ACCESS_P | GDT_ACCESS_S | GDT_ACCESS_RW | GDT_ACCESS_DPL_3;
    gdt_ring3_data.flags = GDT_FLAG_G | GDT_FLAG_DB;
    gdt_info[GDT_INDEX_RING3_DATA - 1] = &gdt_ring3_data;

    // Task state segment
    gdt_ring0_tss.base = (uint32_t)tss;
    gdt_ring0_tss.limit = sizeof(tss_t) - 1;
    gdt_ring0_tss.access = GDT_ACCESS_SYSTEM_P | GDT_ACCESS_SYSTEM_TSS32_AVL;
    gdt_ring0_tss.flags = 0;
    gdt_info[GDT_INDEX_RING0_TSS - 1] = &gdt_ring0_tss;

    // Encode entries
    for (gdt_index_t i = 1; i < GDT_LENGTH; ++i) {
        encode_gdt_entry(gdt + (i * GDT_ENTRY_SIZE), gdt_info[i - 1]);
    }

    // Load into GDTR and update the current segment
    load_gdt((uint32_t)gdt, GDT_LENGTH - 1, GDT_INDEX_RING0_CODE * GDT_ENTRY_SIZE, GDT_INDEX_RING0_DATA * GDT_ENTRY_SIZE);
}

void encode_gdt_entry(gdt_entry_t *dest, const gdt_info_t *source)
{
    // Limit
    if (source->limit > GDT_MAX_ENTRY_LIMIT) {
        kernel_error("Invalid GDT entry limit");
    }
    dest[0] = source->limit & 0xFF;         // Bits 0-7
    dest[1] = (source->limit >> 8) & 0xFF;  // Bits 8-15
    dest[6] = (source->limit >> 16) & 0x0F; // Bits 16-19

    // Base
    dest[2] = source->base & 0xFF;         // Bits 0-7
    dest[3] = (source->base >> 8) & 0xFF;  // Bits 8-15
    dest[4] = (source->base >> 16) & 0xFF; // Bits 16-23
    dest[7] = (source->base >> 24) & 0xFF; // Bits 24-31

    // Access
    dest[5] = source->access;

    // Flags
    dest[6] |= (source->flags << 4); // Bits 0-3
}
