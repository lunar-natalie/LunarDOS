// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include "idt.h"

#include "gdt.h"
#include <string.h>

static uint8_t idt[IDT_SIZE] __attribute__((aligned(IDT_ENTRY_SIZE)));
extern uint32_t isr_stub_table[IDT_NUM_ENTRIES];

void idt_init(void)
{
    // Encode exception ISRs
    for (uint16_t i = 0; i < 32; ++i) {
        encode_idt_entry(i * IDT_ENTRY_SIZE, isr_stub_table[i], GDT_SEL_CODE_PL0, IDT_TYPE_INT32);
    }

    // Fill the rest of the IDT with null entries
    memset(idt + (32 * IDT_ENTRY_SIZE), 0, (IDT_NUM_ENTRIES - 32) * IDT_ENTRY_SIZE);

    // Load into IDTR and enable interrupts
    load_idt((uint32_t)idt, IDT_SIZE);
}

void encode_idt_entry(uint16_t selector, uint32_t offset, uint16_t gdt_selector, uint8_t type)
{
    // Destination entry (8 bytes)
    uint8_t *dest = idt + selector;

    // Encode offset
    dest[0] = offset & 0xFF;         // Bits 0-7
    dest[1] = (offset >> 8) & 0xFF;  // Bits 8-15
    dest[6] = (offset >> 16) & 0xFF; // Bits 16-23
    dest[7] = (offset >> 24) & 0xFF; // Bits 23-31

    // Encode GDT selector
    dest[2] = gdt_selector & 0xFF;        // Bits 0-7
    dest[3] = (gdt_selector >> 8) & 0xFF; // Bits 8-15

    // Encode type
    dest[5] = type;
}
