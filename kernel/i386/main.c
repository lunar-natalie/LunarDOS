// Kernel entry point
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>

#include "cpu/gdt.h"
#include "cpu/idt.h"
#include "cpu/tss.h"
#include <kernel/tty.h>
#include <kernel/version.h>

void kernel_main(void)
{
    static tss_t *tss;

    // Initialize terminal
    tty_init();

    // Setup descriptor tables
    gdt_init(tss);
    tss = tss_init();
    load_tss(GDT_INDEX_RING0_TSS, 0);
    idt_init();

    printf("Loaded\n");
    //    printf("Version %d.%d.%d", KERNEL_VERSION.major, KERNEL_VERSION.minor, KERNEL_VERSION.patch);
}
