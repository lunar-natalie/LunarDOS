// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/i386/cpu/gdt.h>

#include <kernel/error.h>
#include <string.h>

// Flat GDT mapping where the entire virtual address space is mapped for each segment
// Consists of the null descriptor, two kernel segments, two userspace segments and the kernel TSS
static uint8_t __attribute__((aligned(GDT_ENTRY_SIZE))) gdt[GDT_SIZE];

void gdt_init(const tss_t *tss)
{
    // Null descriptor
    memset(gdt, 0, GDT_ENTRY_SIZE);

    // Kernel code segment
    encode_gdt_entry(GDT_SEL_CODE_PL0, 0, GDT_MAX_ENTRY_LIMIT, GDT_CODE_PL0_ACCESS, GDT_CODE_PL0_FLAGS);
    // Kernel data segment
    encode_gdt_entry(GDT_SEL_DATA_PL0, 0, GDT_MAX_ENTRY_LIMIT, GDT_DATA_PL0_ACCESS, GDT_DATA_PL0_FLAGS);
    // Userspace code segment
    encode_gdt_entry(GDT_SEL_CODE_PL3, 0, GDT_MAX_ENTRY_LIMIT, GDT_CODE_PL3_ACCESS, GDT_CODE_PL3_FLAGS);
    // Userspace data segment
    encode_gdt_entry(GDT_SEL_DATA_PL3, 0, GDT_MAX_ENTRY_LIMIT, GDT_DATA_PL3_ACCESS, GDT_DATA_PL3_FLAGS);
    // Task state segment
    encode_gdt_entry(GDT_SEL_TSS_PL0, (uint32_t)tss, sizeof(tss_t) - 1, GDT_TSS_PL0_ACCESS, GDT_TSS_PL0_FLAGS);

    // Load entries into the GDTR and update the segment registers
    load_gdt((uint32_t)gdt, GDT_SIZE - 1, GDT_SEL_CODE_PL0, GDT_SEL_DATA_PL0);
}

void encode_gdt_entry(uint16_t selector, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
    if (limit > GDT_MAX_ENTRY_LIMIT) {
        kerror("Invalid GDT entry limit");
    }

    // Destination entry (8 bytes)
    uint8_t *entry = gdt + selector;

    // Encode limit
    entry[0] = limit & 0xFF;         // Bits 0-7
    entry[1] = (limit >> 8) & 0xFF;  // Bits 8-15
    entry[6] = (limit >> 16) & 0x0F; // Bits 16-19

    // Encode base
    entry[2] = base & 0xFF;         // Bits 0-7
    entry[3] = (base >> 8) & 0xFF;  // Bits 8-15
    entry[4] = (base >> 16) & 0xFF; // Bits 16-23
    entry[7] = (base >> 24) & 0xFF; // Bits 24-31

    // Encode access
    entry[5] = access;

    // Encode flags
    entry[6] |= (flags << 4); // Bits 0-3
}
