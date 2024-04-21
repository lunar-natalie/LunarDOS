// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/i386/vga.h>

#include <string.h>

static uint16_t *const VGA_BUFFER = (uint16_t *)0xb8000;

void init_vga(vga_t *vga)
{
    vga->row = 0;
    vga->column = 0;
    vga->color = vga_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    vga->buffer = VGA_BUFFER;

    // Clear the buffer
    for (unsigned int y = 0; y < VGA_HEIGHT; ++y) {
        for (unsigned int x = 0; x < VGA_WIDTH; ++x) {
            vga->buffer[vga_index(x, y)] = vga_entry('\0', vga->color);
        }
    }
}

void vga_put_entry(vga_t *vga, char ch, uint8_t color, unsigned int x, unsigned int y)
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
    static const unsigned int LAST_ROW = (VGA_HEIGHT - 1) * VGA_WIDTH;

    // Copy each character in each row to the next row, until the last row has been reached
    for (unsigned int y = 0; y < VGA_HEIGHT - 1; ++y) {
        memcpy((void *)(vga->buffer + (VGA_WIDTH * y)),
               (void *)(vga->buffer + (VGA_WIDTH * (y + 1))),
               VGA_WIDTH * sizeof(uint16_t));
    }

    // Clear the last row
    for (unsigned long i = LAST_ROW; i < LAST_ROW + VGA_WIDTH; ++i) {
        vga->buffer[i] = 0;
    }
}
