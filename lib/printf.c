// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>

#include <kernel/console.h>

int printf(const char *restrict format, ...)
{
    int ret;
    va_list args;

    va_start(args, format);
    ret = vprintf(format, args);
    va_end(args);

    return ret;
}

int vprintf(const char *restrict format, va_list vlist) // NOLINT
{
    int ret = 0;
    while (*format != '\0') {
        if (*format == '%') {
            // Format specifier
            char spec = *++format;

            // char
            if (spec == 'c') {
                int value = va_arg(vlist, int);
                putc(value);
                ++ret;
            }
            // string
            else if (spec == 's') {
                char *value = va_arg(vlist, char *);
                ret += puts(value);
            }
            // int (unimplemented)
            else if (spec == 'd' || spec == 'i') {
                //    int value = va_arg(vlist, int);
                //    char *buffer = ...
                //    // Parse negatives
                //    if (value < 0) {
                //        value     = -value;
                //        buffer[0] = '-';
                //        ++buffer;
                //    }
                //    itoa(value, buffer, 10);
                //    ret += puts(buffer);
            }
            // octal (unimplemented)
            else if (spec == 'o') {
                //    unsigned int value = va_arg(vlist, unsigned int);
                //    char *buffer = ...
                //    itoa(value, buffer, 8);
                //    ret += puts(buffer);
            }
            // hex (unimplemented)
            else if (spec == 'x') {
                //    unsigned int value = va_arg(vlist, unsigned int);
                //    char *buffer = ...
                //    itoa(value, buffer, 16);
                //    ret += puts(buffer);
            }
        }
        else {
            putc(*format);
            ++ret;
        }
        ++format;
    }
    return ret;
}
