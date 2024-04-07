// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include "vga.h"

#include <string.h>

static vga_entry_t *const VGA_BUFFER = (vga_entry_t *)0xb8000;
static const vga_index_t  VGA_WIDTH  = 80;
static const vga_index_t  VGA_HEIGHT = 25;

void vga_init(vga_t *vga)
{
    vga->row    = 0;
    vga->column = 0;
    vga->color  = vga_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    vga->buffer = VGA_BUFFER;

    // Clear the buffer
    for (vga_index_t y = 0; y < VGA_HEIGHT; ++y) {
        for (vga_index_t x = 0; x < VGA_WIDTH; ++x) {
            vga->buffer[vga_index(x, y)] = vga_entry('\0', vga->color);
        }
    }
}

void vga_put_entry(vga_t *vga, char ch, vga_color_t color, vga_index_t x, vga_index_t y)
{
    vga->buffer[vga_index(x, y)] = vga_entry(ch, color);
}

void vga_write_ch(vga_t *vga, char ch)
{
    if (ch == '\n') {
        vga_next_line(vga);
    }
    else {
        vga_put_entry(vga, ch, vga->color, vga->column, vga->row);
        if (++vga->column == VGA_WIDTH) {
            vga_next_line(vga);
        }
    }
}

void vga_write_str(vga_t *vga, const char *str, size_t length)
{
    for (size_t i = 0; i < length; ++i) {
        vga_write_ch(vga, str[i]);
    }
}

void vga_next_line(vga_t *vga)
{
    vga->column = 0;
    if (vga->row < VGA_HEIGHT - 1) {
        ++vga->row;
    }
    else {
        vga_scroll_line(vga);
    }
}

void vga_scroll_line(vga_t *vga)
{
    static const vga_index_t LAST_ROW = (VGA_HEIGHT - 1) * VGA_WIDTH;

    // Copy every character in each row to the same column in the next row, until the final row has been reached.
    for (uint8_t y = 0; y < VGA_HEIGHT - 1; ++y) {
        memcpy((void *)(vga->buffer + (y * VGA_WIDTH)),
               (void *)(vga->buffer + ((y + 1) * VGA_WIDTH)),
               VGA_WIDTH * sizeof(uint16_t));
    }

    // Clear the last row
    for (vga_index_t i = LAST_ROW; i < LAST_ROW + VGA_WIDTH; ++i) {
        vga->buffer[i] = 0;
    }
}
