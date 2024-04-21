// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/error.h>

__attribute__((noreturn)) void exception_handler(void)
{
    kexit();
}
