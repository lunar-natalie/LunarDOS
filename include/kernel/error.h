// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <kernel/console.h>

extern void __attribute__((noreturn)) kexit(void);

static inline void kerror(const char *msg)
{
    puts(msg);
    kexit();
}
