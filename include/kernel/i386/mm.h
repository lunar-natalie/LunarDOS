// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

enum {
    PAGE_FREE = 0,
    PAGE_USED = 1
};

enum {
    NUM_HEAP_PAGES = 256
};

void kalloc_init(void);
