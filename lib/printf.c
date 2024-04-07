// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>

#include <kernel/tty.h>

int printf(const char *restrict format, ...)
{
    int     result = 0;
    va_list args;

    va_start(args, format);
    result = vprintf(format, args);
    va_end(args);

    return result;
}

int vprintf(const char *restrict format, va_list vlist)
{
    int result = 0;
    while (*format != '\0') {
        if (*format == '%') {
            // Get format specifier at next character
            char specifier = *++format;
            // char
            if (specifier == 'c') {
                int value = va_arg(vlist, int);
                tty_putc(value);
                ++result;
            }
            // string
            else if (specifier == 's') {
                char *value = va_arg(vlist, char *);
                result += tty_puts(value);
            }
            // int UNIMPLEMENTED
            else if (specifier == 'd' || specifier == 'i') {
                //                int value = va_arg(vlist, int);
                //                char *buffer = ...
                //                // Parse negatives
                //                if (value < 0) {
                //                    value     = -value;
                //                    buffer[0] = '-';
                //                    ++buffer;
                //                }
                //                itoa(value, buffer, 10);
                //                result += tty_puts(buffer);
            }
            // octal UNIMPLEMENTED
            else if (specifier == 'o') {
                //                unsigned int value = va_arg(vlist, unsigned int);
                //                char *buffer = ...
                //                itoa(value, buffer, 8);
                //                result += tty_puts(buffer);
            }
            // hex UNIMPLEMENTED
            else if (specifier == 'x') {
                //                unsigned int value = va_arg(vlist, unsigned int);
                //                char *buffer = ...
                //                itoa(value, buffer, 16);
                //                result += tty_puts(buffer);
            }
        }
        else {
            tty_putc(*format);
            ++result;
        }
        ++format;
    }
    return result;
}
