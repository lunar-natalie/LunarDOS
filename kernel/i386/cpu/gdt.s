/* Copyright (c) 2024 Natalie Wiggins. All rights reserved.
 * SPDX-License-Identifier: GPL-3.0-or-later */

.section .text
.global load_gdt
.type load_gdt, @function
load_gdt:
	push	%ebp		/* Save stack frame */
	mov	%esp, %ebp

	mov	12(%ebp), %ax 	/* Get limit */
	cmp	$0, %ax		/* Return if zero */
	je	1f
	mov	%ax, gdtr

	mov	8(%ebp), %eax	/* Get base */
	mov	%eax, gdtr + 2

	lgdt	gdtr		/* Write to register */

	xor	%eax, %eax	/* Success */
	jmp	2f

1:	mov	$1, %eax	/* Fail */

2:	pop	%ebp		/* Restore stack frame */
	ret

gdtr:
.word 0         /* Limit */
.long 0         /* Base */
