// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-or-later

.section .text
.global load_gdt
.type load_gdt, @function
load_gdt:
	cli
	push	%ebp
	mov	%esp, %ebp

	mov	12(%ebp), %ax 	// Limit
	mov	%ax, gdtr

	mov	8(%ebp), %eax	// Base
	mov	%eax, gdtr + 2

	lgdt	gdtr

	mov	20(%ebp), %eax	// Reset segments with data selector
	mov	%ax, %ds
	mov	%ax, %es
	mov	%ax, %gs
	mov	%ax, %fs
	mov	%ax, %ss

	pushl	16(%ebp)	// Push code selector onto the stack as the far pointer
	push	$.setcs		// Push offset
	ljmp	*(%esp)		// Far jump to the next instruction

.setcs:
	pop	%ebp
	ret

.section data
gdtr:
.word 0         // Limit
.long 0         // Base
