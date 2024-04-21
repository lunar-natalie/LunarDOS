// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-or-later

.section .text
.global load_tss
.type load_tss, @function
load_tss:
	push	%ebp
	mov	%esp, %ebp

	// Load the TSS selector corresponding to the given GDT entry
	mov	12(%ebp), %ax		// GDT selector
	or	%ax, 8(%ebp)		// RPL
        ltr	%ax			// Load selector into task register

	pop	%ebp
        ret
