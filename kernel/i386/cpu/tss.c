// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/i386/cpu/tss.h>

struct {
    uint32_t ss;
    uint32_t esp;
} __attribute__((packed)) boot_tss;

void tss_init(tss_t *tss, uint16_t selector)
{
    tss->ss0 = boot_tss.ss;
    tss->esp0 = boot_tss.esp;
    tss->iopb = sizeof(tss);
    load_tss(selector, 0);
}
