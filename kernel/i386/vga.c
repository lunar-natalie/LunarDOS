// VGA graphics driver
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include "vga.h"

#include <string.h>

static uint16_t *const VGA_BUFFER = (uint16_t *)0xb8000;

void vga_init(vga_t *vga)
{
    vga->row    = 0;
    vga->column = 0;
    vga->color  = vga_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    vga->buffer = VGA_BUFFER;

    // Clear the buffer
    for (uint8_t y = 0; y < VGA_HEIGHT; ++y) {
        for (uint8_t x = 0; x < VGA_WIDTH; ++x) {
            vga->buffer[vga_index(x, y)] = vga_entry('\0', vga->color);
        }
    }
}

void vga_put_entry(vga_t *vga, char c, uint8_t color, uint8_t x, uint8_t y)
{
    vga->buffer[vga_index(x, y)] = vga_entry(c, color);
}

void vga_put_char(vga_t *vga, char c)
{
    if (c == '\n') {
        vga_next_line(vga);
    } else {
        vga_put_entry(vga, c, vga->color, vga->column, vga->row);
        if (++vga->column == VGA_WIDTH) {
            vga_next_line(vga);
        }
    }
}

void vga_next_line(vga_t *vga)
{
    vga->column = 0;
    if (vga->row < VGA_HEIGHT - 1) {
        ++vga->row;
    } else {
        vga_scroll(vga);
    }
}

void vga_scroll(vga_t *vga)
{
    static const uint16_t last_row = (VGA_HEIGHT - 1) * VGA_WIDTH;

    // Copy every character in each row to the same column in the next row, until the final row has been reached.
    for (uint8_t y = 0; y < VGA_HEIGHT - 1; ++y) {
        memcpy((void *)(vga->buffer + (y * VGA_WIDTH)),
               (void *)(vga->buffer + ((y + 1) * VGA_WIDTH)), VGA_WIDTH);
    }

    // Clear the last row
    for (uint16_t i = last_row; i < last_row + VGA_WIDTH; ++i) {
        vga->buffer[i] = 0;
    }
}

void vga_write(vga_t *vga, const char *s, size_t length)
{
    for (size_t i = 0; i < length; ++i) {
        vga_put_char(vga, s[i]);
    }
}
