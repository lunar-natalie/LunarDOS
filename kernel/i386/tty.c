// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/tty.h>

#include "video/vga.h"
#include <string.h>

static vga_t vga;

void init_tty(void)
{
    init_vga(&vga);
}

void tty_putc(char ch)
{
    vga_write_ch(&vga, ch);
}

size_t tty_puts(const char *str)
{
    size_t len = strlen(str);
    vga_write_str(&vga, str, len);
    return len;
}
