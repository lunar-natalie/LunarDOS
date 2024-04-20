// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include "idt.h"

#include "gdt.h"

static uint64_t idt[IDT_NUM_ENTRIES];
static idt_info_t idt_info[IDT_NUM_ENTRIES];
extern uint32_t isr_stub_table[IDT_NUM_ENTRIES];

void idt_init(void)
{
    // Fill IDT and encode metadata
    for (uint16_t i = 0; i < 32; ++i) {
        set_isr(i, IDT_TYPE_INT32);
        encode_idt_entry(idt + i, idt_info + i);
    }

    // Load into IDTR and enable interrupts
    load_idt((uint32_t)idt, IDT_SIZE);
}

void set_isr(uint16_t index, uint8_t entry_type)
{
    idt_info[index].offset = isr_stub_table[index];
    idt_info[index].selector = GDT_INDEX_RING0_CODE;
    idt_info[index].type_attributes = entry_type;
}

void encode_idt_entry(uint64_t *dest __attribute__((unused)), const idt_info_t *source __attribute__((unused)))
{
    // Unimplemented
}
