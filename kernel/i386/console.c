// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/console.h>

#include <kernel/i386/vga.h>
#include <string.h>

static vga_t vga;

void console_init(void)
{
    init_vga(&vga);
}

void putc(char ch)
{
    vga_write_ch(&vga, ch);
}

size_t puts(const char *str)
{
    size_t len = strlen(str);
    vga_write_str(&vga, str, len);
    return len;
}
