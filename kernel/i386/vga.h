// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <stddef.h>
#include <stdint.h>

#define VGA_WIDTH  80
#define VGA_HEIGHT 25

typedef struct {
    size_t     row;
    size_t     column;
    uint8_t    color;
    uint16_t  *buffer;
} vga_t;

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

static inline uint8_t vga_color(enum vga_color fg, enum vga_color bg)
{
    return (uint8_t)(fg | bg << 4);
}

static inline uint16_t vga_entry(unsigned char data, uint8_t color)
{
    return (uint16_t)data | (uint16_t)color << 8;
}

static inline uint16_t vga_index(uint8_t x, uint8_t y)
{
    return x + (y * VGA_WIDTH);
}

void vga_init(vga_t *vga);
void vga_put_entry(vga_t *vga, char c, uint8_t color, uint8_t x, uint8_t y);
void vga_put_char(vga_t *vga, char c);
void vga_next_line(vga_t *vga);
void vga_scroll(vga_t *vga);
void vga_write(vga_t *vga, const char *s, size_t length);
