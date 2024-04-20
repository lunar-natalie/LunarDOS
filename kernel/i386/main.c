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
    // TODO: Fix GDT and enable interrupts
    console_init();
    paging_init();
    gdt_init(&tss);
    //    tss_init(&tss);
    //    load_tss(GDT_INDEX_RING0_TSS, 0);
    //    idt_init();
    printf("Loaded\n");
}
