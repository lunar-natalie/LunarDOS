// Control registers
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <stdint.h>

enum CR0_FLAG {
    CR0_FLAG_PE = 1 << 0,  // Protected Mode Enable
    CR0_FLAG_MP = 1 << 1,  // Monitor coprocessor
    CR0_FLAG_EM = 1 << 2,  // Emulation
    CR0_FLAG_TS = 1 << 3,  // Task switched
    CR0_FLAG_ET = 1 << 4,  // Extension type
    CR0_FLAG_NE = 1 << 5,  // Numeric error
    CR0_FLAG_WP = 1 << 16, // Write protect
    CR0_FLAG_AM = 1 << 18, // Alignment mask
    CR0_FLAG_NW = 1 << 29, // Not write-through
    CR0_FLAG_CD = 1 << 30, // Cache disable
    CR0_FLAG_PG = 1 << 31, // Paging
};

extern uint32_t read_cr0(void);
extern uint32_t read_cr3(void);
extern void write_cr0(uint32_t cr0);
extern void write_cr3(uint32_t cr3);
