// Interrupt Descriptor Table
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <stdint.h>

typedef struct {
    uint32_t offset;   // ISR entry point
    uint16_t selector; // Code segment selector pointing to a valid entry in the GDT/LDT
    uint8_t type_attributes;
} idt_info_t;

enum {
    IDT_NUM_ENTRIES = 256,
    IDT_ENTRY_SIZE = sizeof(uint64_t),
    IDT_SIZE = IDT_NUM_ENTRIES * IDT_ENTRY_SIZE
};

enum IDT_ATTRIBUTE {
    // Gate types
    IDT_ATTRIBUTE_TASK = 0x05,   // Task gate (offset is unused and should be set to zero)
    IDT_ATTRIBUTE_INT16 = 0x06,  // 16-bit interrupt gate
    IDT_ATTRIBUTE_TRAP16 = 0x07, // 16-bit trap gate
    IDT_ATTRIBUTE_INT32 = 0x0E,  // 32-bit interrupt gate
    IDT_ATTRIBUTE_TRAP32 = 0x0F, // 32-bit trap gate

    // Descriptor privilege level (ring 0-3)
    IDT_ATTRIBUTE_DPL_1 = 1 << 5,
    IDT_ATTRIBUTE_DPL_2 = 1 << 6,
    IDT_ATTRIBUTE_DPL_3 = IDT_ATTRIBUTE_DPL_1 | IDT_ATTRIBUTE_DPL_2,

    IDT_ATTRIBUTE_P = 1 << 7 // Present (must be set for any valid descriptor)
};

enum IDT_TYPE {
    IDT_TYPE_TASK = IDT_ATTRIBUTE_P | IDT_ATTRIBUTE_TASK,
    IDT_TYPE_INT16 = IDT_ATTRIBUTE_P | IDT_ATTRIBUTE_INT16,
    IDT_TYPE_INT32 = IDT_ATTRIBUTE_P | IDT_ATTRIBUTE_INT32,
    IDT_TYPE_TRAP16 = IDT_ATTRIBUTE_P | IDT_ATTRIBUTE_DPL_3 | IDT_ATTRIBUTE_TRAP16,
    IDT_TYPE_TRAP32 = IDT_ATTRIBUTE_P | IDT_ATTRIBUTE_DPL_3 | IDT_ATTRIBUTE_TRAP32
};

// Encodes the default IDT entries, loads the IDTR and enables interrupts
// Must be called after the GDT has been loaded
void idt_init(void);

// Registers the stub for the given ISR in the IDT
// entry_type - Type attributes for the IDT entry
void set_isr(uint16_t index, uint8_t entry_type);

// Encodes the metadata describing an IDT descriptor into a valid entry
void encode_idt_entry(uint64_t *dest, const idt_info_t *source);

// Loads the IDT into the IDTR and sets the interrupt flag
// offset - Linear address of the start of the table
// size - Length of the table in bytes
extern void load_idt(uint32_t offset, uint16_t size);
