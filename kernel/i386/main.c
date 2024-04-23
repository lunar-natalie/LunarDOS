// Kernel entry point
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/console.h>
#include <kernel/i386/cpu/gdt.h>
#include <kernel/i386/cpu/idt.h>
#include <kernel/i386/cpu/tss.h>
#include <kernel/i386/mm/init.h>
#include <kernel/i386/mm/paging.h>
#include <stdio.h>

void kmain(void)
{
    static tss_t tss;
    console_init();
    paging_init();
    gdt_init(&tss);
    tss_init(&tss, GDT_SEL_TSS_PL0);
    idt_init();
    mm_init();
    printf("Loaded\n");
}
