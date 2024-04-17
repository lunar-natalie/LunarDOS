// Kernel entry point
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include "cpu/gdt.h"
#include "cpu/idt.h"
#include "cpu/tss.h"
#include "cpu/paging.h"
#include <kernel/tty.h>
#include <stdio.h>

//extern void test(void);

static tss_t tss;

void kernel_main(void)
{
    // TODO: Fix GDT in order to far jump to kernel code segment
    // TODO: Verify TSS implementation
    // TODO: Implement interrupts
    init_paging();
    init_gdt(&tss);
//    init_tss(&tss);
//    load_tss(GDT_INDEX_RING0_TSS, 0);
//    init_idt();
    init_tty();

    // TODO: Test exception handling when the required components are implemented
//    test();

    printf("Loaded\n");
}
