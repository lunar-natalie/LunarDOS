// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include "idt.h"

#include "gdt.h"
#include <kernel/error.h>

static idt_entry_t idt[IDT_LENGTH];
static idt_info_t  idt_info[IDT_LENGTH];
extern uint32_t    isr_stub_table[IDT_LENGTH];

void idt_init(void)
{
    /* Add exception ISRs */
    for (int i = 0; i < 32; ++i) {
        idt_info[i].offset          = isr_stub_table[i];
        idt_info[i].selector        = GDT_INDEX_RING0_CODE;
        idt_info[i].type_attributes = IDT_TYPE_RING0_INT32;
        encode_idt_entry(idt + i, idt_info + i);
    }

    if (load_idt(idt, IDT_LENGTH) != 0) {
        kernel_error("Failed to load IDT\n");
    }
}

void encode_idt_entry(idt_entry_t *dest, const idt_info_t *source)
{
    dest->offset_low      = source->offset & 0xFFFF; // Bits 0-15
    dest->offset_high     = source->offset >> 16;    // Bits 16-31
    dest->selector        = source->selector;
    dest->type_attributes = source->type_attributes;
}
