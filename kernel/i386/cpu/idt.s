// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-or-later

.section .text
.global load_idt
.type load_idt, @function
load_idt:
	push	%ebp
	mov	%esp, %ebp

	mov	12(%ebp), %ax 	// Size
	mov	%ax, idtr

	mov	8(%ebp), %eax	// Offset
	mov	%eax, idtr + 2

	lidt	idtr

	pop	%ebp
	sti
	ret

.section data
idtr:
.word 0         		// Size
.long 0         		// Offset
