// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <stddef.h>

void console_init(void);

void putc(char ch);
size_t puts(const char *str);
