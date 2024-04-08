// Interrupt Descriptor Table
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <stdint.h>

typedef uint8_t idt_index_t;
enum { IDT_LENGTH = UINT8_MAX };

// IDT entry metadata
typedef struct {
    uint32_t offset;          // ISR entry point
    uint16_t selector;        // Code segment selector pointing to a valid GDT or LDT entry
    uint8_t  type_attributes; // Type attributes byte
} idt_info_t;

// IDT entry data
typedef struct {
    unsigned int offset_low      : 16; // Offset bits 0-15
    unsigned int selector        : 16; // Segment selector
    unsigned int reserved        : 8;
    unsigned int type_attributes : 8;  // Type attributes byte
    unsigned int offset_high     : 16; // Offset bits 16-31
} __attribute__((packed, aligned(4))) idt_entry_t;

enum idt_attributes {
    // Present bit (must be set for any valid descriptor)
    IDT_ATTRIB_P = 0b10000000,
    // Descriptor privilege level (ring 0-3)
    IDT_ATTRIB_DPL_1 = 0b00100000,
    IDT_ATTRIB_DPL_2 = 0b01000000,
    IDT_ATTRIB_DPL_3 = 0b01100000,
    // Gate types
    IDT_ATTRIB_GATE_TASK   = 0b00000101, // Task gate: IDT offset is unused and should be zero
    IDT_ATTRIB_GATE_INT16  = 0b00000110, // 16-bit interrupt gate
    IDT_ATTRIB_GATE_TRAP16 = 0b00000111, // 16-bit trap gate
    IDT_ATTRIB_GATE_INT32  = 0b00001110, // 32-bit interrupt gate
    IDT_ATTRIB_GATE_TRAP32 = 0b00001111, // 32-bit trap gate
};

enum idt_types {
    IDT_TYPE_RING0_TASK   = IDT_ATTRIB_P | IDT_ATTRIB_GATE_TASK,
    IDT_TYPE_RING0_INT16  = IDT_ATTRIB_P | IDT_ATTRIB_GATE_INT16,
    IDT_TYPE_RING0_TRAP16 = IDT_ATTRIB_P | IDT_ATTRIB_GATE_TRAP16,
    IDT_TYPE_RING0_INT32  = IDT_ATTRIB_P | IDT_ATTRIB_GATE_INT32,
    IDT_TYPE_RING0_TRAP32 = IDT_ATTRIB_P | IDT_ATTRIB_GATE_TRAP32,
    IDT_TYPE_RING3_INT16  = IDT_ATTRIB_P | IDT_ATTRIB_DPL_3 | IDT_ATTRIB_GATE_INT16,
    IDT_TYPE_RING3_TRAP16 = IDT_ATTRIB_P | IDT_ATTRIB_DPL_3 | IDT_ATTRIB_GATE_TRAP16,
    IDT_TYPE_RING3_INT32  = IDT_ATTRIB_P | IDT_ATTRIB_DPL_3 | IDT_ATTRIB_GATE_INT32,
    IDT_TYPE_RING3_TRAP32 = IDT_ATTRIB_P | IDT_ATTRIB_DPL_3 | IDT_ATTRIB_GATE_TRAP32,
};

// Encodes the default IDT entries and loads the IDT.
// Must be called after the GDT has been loaded.
void idt_init(void);

// Encodes the metadata describing an IDT descriptor into a valid entry.
void encode_idt_entry(idt_entry_t *dest, const idt_info_t *source);

// Loads the IDT into the IDTR.
// offset - Linear 32-bit address of the start of the table.
// size - 16-bit length of the table in bytes.
// Returns 0 if the IDT is valid.
extern int load_idt(idt_entry_t *offset, uint16_t size);
