// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    size_t base;
    size_t size;
} block_t;

// Initializes the virtual memory manager
void init_vm(void);
