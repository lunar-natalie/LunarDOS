// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <kernel/tty.h>

extern void __attribute__((noreturn)) kernel_exit(void);

static inline void __attribute__((noreturn)) kernel_error(const char *message)
{
    tty_puts(message);
    kernel_exit();
}
