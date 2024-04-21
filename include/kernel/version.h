// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

typedef struct {
    int major;
    int minor;
    int patch;
} version_t;

static const version_t KERNEL_VERSION __attribute__((unused));
