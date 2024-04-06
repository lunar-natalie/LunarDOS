// Kernel entry point
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>

#include "kernel/tty.h"
// #include "version.h"

void kernel_main(void)
{
    tty_init();
    printf("%s\n", "Hello, world!");
    //    printf("Version %d.%d.%d", KERNEL_VERSION.major, KERNEL_VERSION.minor, KERNEL_VERSION.patch);
}
