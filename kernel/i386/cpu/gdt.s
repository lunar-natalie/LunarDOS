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

	pushl	16(%ebp)	// Push code selector
	push	$.setcs		// Push offset
/*	ljmp	*(%esp)		// Load EIP with the offset of .setcs and far jump to CS:EIP	*/

.setcs:
	add	$8, %esp	// Restore stack after far jump
/*
	mov	20(%ebp), %eax	// Reload segments with data selector
	mov	%ax, %ds
	mov	%ax, %es
	mov	%ax, %gs
	mov	%ax, %fs
	mov	%ax, %ss
*/
	pop	%ebp
	ret

.section data
gdtr:
.word 0         // Limit
.long 0         // Base
