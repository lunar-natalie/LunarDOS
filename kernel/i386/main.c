// Kernel entry point
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include "tty.h"

void kernel_main(void)
{
    tty_init();
    tty_puts("Hello, world!\n");
}
