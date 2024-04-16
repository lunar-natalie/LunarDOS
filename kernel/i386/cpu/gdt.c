// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include "gdt.h"

#include "tss.h"
#include <kernel/error.h>

// GDT with one null descriptor, two ring 0 segments, two ring 3 segments and the kernel TSS
static gdt_entry_t gdt[GDT_LENGTH];
static const gdt_entry_t GDT_NULL = {}; // Null descriptor

// Array of pointers to GDT info structures describing the entry for each segment, excluding the null descriptor
static gdt_info_t *gdt_info[GDT_LENGTH - 1];
static gdt_info_t  gdt_ring0_code; // Kernel code segment
static gdt_info_t  gdt_ring0_data; // Kernel data segment
static gdt_info_t  gdt_ring3_code; // Userspace code segment
static gdt_info_t  gdt_ring3_data; // Userspace data segment
static gdt_info_t  gdt_ring0_tss;  // Task state segment

void init_gdt(const tss_t *tss)
{
    // Null descriptor
    gdt[GDT_INDEX_NULL] = GDT_NULL;

    // Kernel code segment
    gdt_ring0_code.base                = 0;
    gdt_ring0_code.limit               = GDT_MAX_LIMIT;
    gdt_ring0_code.access              = (uint8_t)(GDT_ACCESS_P | GDT_ACCESS_S | GDT_ACCESS_E | GDT_ACCESS_RW);
    gdt_ring0_code.flags               = (uint8_t)(GDT_FLAG_G | GDT_FLAG_DB);
    gdt_info[GDT_INDEX_RING0_CODE - 1] = &gdt_ring0_code;

    // Kernel data segment
    gdt_ring0_data.base                = 0;
    gdt_ring0_data.limit               = GDT_MAX_LIMIT;
    gdt_ring0_data.access              = (uint8_t)(GDT_ACCESS_P | GDT_ACCESS_S | GDT_ACCESS_RW);
    gdt_ring0_data.flags               = (uint8_t)(GDT_FLAG_G | GDT_FLAG_DB);
    gdt_info[GDT_INDEX_RING0_DATA - 1] = &gdt_ring0_data;

    // Userspace code segment
    gdt_ring3_code.base   = 0;
    gdt_ring3_code.limit  = 0xFFFFF;
    gdt_ring3_code.access = (uint8_t)(GDT_ACCESS_P | GDT_ACCESS_DPL_3 | GDT_ACCESS_S | GDT_ACCESS_E | GDT_ACCESS_RW);
    gdt_ring3_code.flags  = (uint8_t)(GDT_FLAG_G | GDT_FLAG_DB);
    gdt_info[GDT_INDEX_RING3_CODE - 1] = &gdt_ring3_code;

    // Userspace data segment
    gdt_ring3_data.base                = 0;
    gdt_ring3_data.limit               = GDT_MAX_LIMIT;
    gdt_ring3_data.access              = (uint8_t)(GDT_ACCESS_P | GDT_ACCESS_DPL_3 | GDT_ACCESS_S | GDT_ACCESS_RW);
    gdt_ring3_data.flags               = (uint8_t)(GDT_FLAG_G | GDT_FLAG_DB);
    gdt_info[GDT_INDEX_RING3_DATA - 1] = &gdt_ring3_data;

    // Task state segment (attribute functionality differs from other segment types)
    gdt_ring0_tss.base                = (uint32_t)tss;
    gdt_ring0_tss.limit               = sizeof(tss_t);
    gdt_ring0_tss.access              = (uint8_t)(GDT_ACCESS_P | // Required
                                     GDT_ACCESS_E | // 32-bit
                                     GDT_ACCESS_A); // System segment
    gdt_ring0_tss.flags               = 0;
    gdt_info[GDT_INDEX_RING0_TSS - 1] = &gdt_ring0_tss;

    // Encode entries
    for (gdt_index_t i = 1; i < GDT_LENGTH; ++i) {
        encode_gdt_entry(&gdt[i], gdt_info[i - 1]);
    }

    // Load into GDTR and update the current segment
    load_gdt(gdt, GDT_LENGTH - 1, GDT_INDEX_RING0_CODE, GDT_INDEX_RING0_DATA);
}

void encode_gdt_entry(gdt_entry_t *dest, const gdt_info_t *source)
{
    if (source->limit > GDT_MAX_LIMIT) {
        kernel_error("Invalid GDT entry limit");
    }
    dest->limit_low  = source->limit & 0xFFFF;       // Bits 0-15
    dest->limit_high = (source->limit >> 16) & 0x0F; // Bits 16-19

    dest->base_low  = source->base & 0xFFFFFF;       // Bits 0-24
    dest->base_high = source->base >> 24;            // Bits 24-31

    dest->access = source->access;
    dest->flags  = source->flags;
}
