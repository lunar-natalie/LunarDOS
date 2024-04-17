// Terminal driver
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <stddef.h>

void init_tty(void);
void tty_putc(char ch);
size_t tty_puts(const char *str);
