// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include "tss.h"

static tss_t tss = {};

struct {
    uint32_t ss;
    uint32_t esp;
} __attribute__((packed)) boot_tss;

tss_t *init_tss()
{
    tss.ss0  = boot_tss.ss;
    tss.esp0 = boot_tss.esp;
    tss.iopb = sizeof(tss);
    return &tss;
}
