// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/error.h>

void __attribute__((noreturn)) exception_handler(void)
{
    kexit();
}
