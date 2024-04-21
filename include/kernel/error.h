// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <kernel/console.h>

extern __attribute__((noreturn)) void kexit(void);

static inline __attribute__((noreturn)) void kerror(const char *msg)
{
    puts(msg);
    kexit();
}
