// Interrupt Descriptor Table
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <stdint.h>

typedef uint8_t idt_entry_t;
typedef uint32_t idt_index_t;

typedef struct {
    uint32_t offset;   // ISR entry point
    uint16_t selector; // Code segment selector pointing to a valid entry in the GDT/LDT
    uint8_t type_attributes;
} idt_info_t;

enum { IDT_LENGTH = 256 };
enum { IDT_SIZE = sizeof(idt_entry_t) * (IDT_LENGTH - 1) };

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

// Encodes the default IDT entries and loads the IDTR
// Must be called after the GDT has been loaded
void idt_init(void);

// Registers the stub for the given ISR in the IDT
// entry_type - Type attributes for the IDT entry
void set_isr(idt_index_t index, uint8_t entry_type);

// Encodes the metadata describing an IDT descriptor into a valid entry
void encode_idt_entry(idt_entry_t *dest, const idt_info_t *source);

// Loads the IDT into the IDTR
// offset - Linear 32-bit address of the start of the table
// size - 16-bit length of the table in bytes
// Returns 0 and sets the interrupt flag if the IDT is valid
extern int load_idt(uint32_t offset, uint16_t size);
