// Task State Segment
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <stdint.h>

typedef struct {
    uint32_t link; // Segment selector of the previous TSS (low 16 bits)

    // Segment selectors for privilege transfer (low 16 bits)
    uint32_t esp0; // Kernel mode stack pointer
    uint32_t ss0;  // Kernel mode stack segment
    // Unused: esp1,esp2,ss1,ss2 are used when switching to rings 1 or 2
    uint32_t esp1;
    uint32_t ss1;
    uint32_t esp2;
    uint32_t ss2;

    // General purpose and flag registers
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;

    // Segment registers (low 16 bits)
    uint32_t es;
    uint32_t cs;
    uint32_t ss;
    uint32_t ds;
    uint32_t fs;
    uint32_t gs;
    uint32_t ldtr;

    uint32_t iopb; // IO map base address (high 16 bits)
    uint32_t ssp;  // Shadow stack pointer
} __attribute__((packed)) tss_t;

// Initializes the kernel TSS
// tss - Pointer to uninitialized data
void tss_init(tss_t *tss);

// Loads the TSS at the given index into the GDT into the task register
// rpl - Requested Privilege Level
// Must be called after the GDT has been loaded
extern void load_tss(uint8_t gdt_index, uint16_t rpl);
