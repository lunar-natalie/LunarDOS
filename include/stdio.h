// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <stdarg.h>

int printf(const char *restrict format, ...);
int vprintf(const char *restrict format, va_list vlist);
