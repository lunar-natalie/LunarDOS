// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <number.h>

#include <limits.h>

int digits(int n)
{
    int result = 1;
    if (n < 0) {
        n = (n == INT_MIN) ? INT_MAX : -n;
    }
    while (n > 9) {
        // Next digit
        n /= 10;
        ++result;
    }
    return result;
}
