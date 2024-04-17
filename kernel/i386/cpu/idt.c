// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include "idt.h"

#include "gdt.h"
#include <kernel/error.h>

static idt_entry_t idt[IDT_LENGTH];
static idt_info_t  idt_info[IDT_LENGTH];
extern idt_index_t isr_stub_table[IDT_LENGTH];

void init_idt(void)
{
    // Fill IDT and encode metadata
    for (idt_index_t i = 0; i < 32; ++i) {
        set_isr(i, IDT_TYPE_INT32);
        encode_idt_entry(idt + i, idt_info + i);
    }

    // Load into IDTR
    if (load_idt((uint32_t)idt, IDT_SIZE) != 0) {
        kernel_error("Failed to load IDT\n");
    }
}

void set_isr(idt_index_t index, uint8_t entry_type)
{
    idt_info[index].offset          = isr_stub_table[index];
    idt_info[index].selector        = GDT_INDEX_RING0_CODE;
    idt_info[index].type_attributes = entry_type;
}

void encode_idt_entry(idt_entry_t *dest, const idt_info_t *source)
{
    // Unimplemented
}
