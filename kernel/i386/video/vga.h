// Text mode graphics driver
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct {
    unsigned int row;
    unsigned int column;
    uint8_t color;
    uint16_t *buffer;
} vga_t;

enum {
    VGA_WIDTH = 80,
    VGA_HEIGHT = 25
};

enum VGA_COLOR {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_color(enum VGA_COLOR fg, enum VGA_COLOR bg)
{
    return (uint8_t)(fg | bg << 4);
}

static inline uint16_t vga_entry(unsigned char data, uint8_t color)
{
    return (uint16_t)data | (color << 8);
}

static inline unsigned long vga_index(unsigned int x, unsigned int y)
{
    return x + (y * VGA_WIDTH);
}

void init_vga(vga_t *vga);

void vga_write_ch(vga_t *vga, char ch);
void vga_write_str(vga_t *vga, const char *str, size_t length);

void vga_put_entry(vga_t *vga, char ch, uint8_t color, unsigned int x, unsigned int y);
void vga_next_line(vga_t *vga);
void vga_scroll_line(vga_t *vga);
