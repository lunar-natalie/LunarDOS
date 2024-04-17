// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include "tss.h"

struct {
    uint32_t ss;
    uint32_t esp;
} __attribute__((packed)) boot_tss;

void init_tss(tss_t *tss)
{
    tss->ss0  = boot_tss.ss;
    tss->esp0 = boot_tss.esp;
    tss->iopb = sizeof(tss);
}
