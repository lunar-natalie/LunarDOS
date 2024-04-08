// Control registers
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <stdint.h>

extern uint32_t read_cr0(void);
extern uint32_t read_cr3(void);
extern void     write_cr0(uint32_t cr0);
extern void     write_cr3(uint32_t cr3);
