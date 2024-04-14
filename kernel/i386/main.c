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

void kernel_main(void)
{
//    static tss_t *tss;

//    init_paging();
//    init_gdt(tss);
//    tss = init_tss();
//    load_tss(GDT_INDEX_RING0_TSS, 0);
//    init_idt();
    init_tty();

    // TODO: Test exception handling when the required components are implemented.
//    test();

    printf("Loaded\n");
}
