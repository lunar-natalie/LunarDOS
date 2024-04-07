// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-or-later

.section .text
.global load_tss
.type load_tss, @function
load_tss:
	push	%ebp
	mov	%esp, %ebp

	// Load TSS selector corresponding to the given GDT entry
	mov	12(%ebp), %ax		// GDT index
	mul	8			// 8 byte descriptor size
	or	%ax, 8(%ebp)		// OR with RPL
        ltr	%ax			// Load selector into task register

	pop	%ebp
        ret
