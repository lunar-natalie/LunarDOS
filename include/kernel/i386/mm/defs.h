// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <stddef.h>

enum {
    NUM_CODE_PAGES = 0x300, // 3M kernel space
    NUM_HEAP_PAGES = 0x100, // 1M heap space
    NUM_PAGES = NUM_CODE_PAGES + NUM_HEAP_PAGES,
    PAGE_SIZE = 0x1000, // 4K per page

    // Maximum number of frames which can be allocated before allocating a new set of pre-frames
    PRE_FRAME_LIMIT = 20
};
