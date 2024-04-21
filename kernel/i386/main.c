// Kernel entry point
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include "cpu/gdt.h"
#include "cpu/idt.h"
#include "cpu/paging.h"
#include "cpu/tss.h"
#include <kernel/console.h>
#include <stdio.h>

static tss_t tss;

void kmain(void)
{
    // TODO: Enable interrupts
    console_init();
    paging_init();
    gdt_init(&tss);
    tss_init(&tss);
    load_tss(GDT_SEL_TSS_PL0, 0);
    //    idt_init();
    printf("Loaded\n");
}
