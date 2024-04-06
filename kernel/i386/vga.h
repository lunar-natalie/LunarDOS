// Text mode graphics driver
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <stddef.h>
#include <stdint.h>

typedef uint8_t vga_color_t;
typedef uint16_t vga_entry_t;
typedef vga_entry_t vga_index_t;

typedef struct {
    vga_index_t row;
    vga_index_t column;
    vga_color_t color;
    vga_entry_t *buffer;
} vga_t;

static const vga_index_t VGA_WIDTH;
static const vga_index_t VGA_HEIGHT;

enum vga_color {
    VGA_COLOR_BLACK         = 0,
    VGA_COLOR_BLUE          = 1,
    VGA_COLOR_GREEN         = 2,
    VGA_COLOR_CYAN          = 3,
    VGA_COLOR_RED           = 4,
    VGA_COLOR_MAGENTA       = 5,
    VGA_COLOR_BROWN         = 6,
    VGA_COLOR_LIGHT_GREY    = 7,
    VGA_COLOR_DARK_GREY     = 8,
    VGA_COLOR_LIGHT_BLUE    = 9,
    VGA_COLOR_LIGHT_GREEN   = 10,
    VGA_COLOR_LIGHT_CYAN    = 11,
    VGA_COLOR_LIGHT_RED     = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN   = 14,
    VGA_COLOR_WHITE         = 15,
};

static inline vga_color_t vga_color(enum vga_color fg, enum vga_color bg)
{
    return (vga_color_t)(fg | bg << 4);
}

static inline vga_entry_t vga_entry(unsigned char data, vga_color_t color)
{
    return (vga_entry_t)data | (vga_entry_t)color << 8;
}

static inline vga_index_t vga_index(vga_index_t x, vga_index_t y)
{
    return x + (y * VGA_WIDTH);
}

void vga_init(vga_t *vga);

void vga_write_ch(vga_t *vga, char ch);
void vga_write_str(vga_t *vga, const char *str, size_t length);

void vga_put_entry(vga_t *vga, char ch, vga_color_t color, vga_index_t x, vga_index_t y);
void vga_next_line(vga_t *vga);
void vga_scroll_line(vga_t *vga);
