// Kernel entry point
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include "cpu/gdt.h"
#include "cpu/idt.h"
#include "cpu/paging.h"
#include "cpu/tss.h"
#include <kernel/console.h>
#include <stdio.h>

// extern void test(void);

static tss_t tss;

void kmain(void)
{
    // TODO: Fix GDT in order to far jump to kernel code segment
    // TODO: Verify TSS implementation
    // TODO: Implement interrupts
    paging_init();
    gdt_init(&tss);
    //    tss_init(&tss);
    //    load_tss(GDT_INDEX_RING0_TSS, 0);
    //    idt_init();
    console_init();

    // TODO: Test exception handling when the required components are implemented
    //    test();

    printf("Loaded\n");
}
