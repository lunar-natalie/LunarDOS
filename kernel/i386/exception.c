// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/runtime.h>

void __attribute__((noreturn)) kernel_exception_handler(void)
{
    kernel_exit();
}
