// Kernel entry point
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <string.h>

#include "vga.h"

static vga_t vga;

void kernel_main(void)
{
    vga_init(&vga);
    const char *s = "Hello, world!";
    vga_write(&vga, s, strlen(s));
}
