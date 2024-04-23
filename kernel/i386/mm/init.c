// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/i386/mm/init.h>

#include <kernel/i386/mm/frame.h>
#include <string.h>

void kalloc_init(void)
{
    memset(frame_map, FREE, sizeof(frame_map));
}
