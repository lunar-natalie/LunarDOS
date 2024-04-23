// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/i386/mm/init.h>

#include <kernel/i386/mm/frame.h>
#include <kernel/i386/mm/vm.h>

void mm_init(void)
{
    init_page_frames();
    init_vm();
}
