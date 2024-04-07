// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-or-later

.section .text
.global load_idt
.type load_idt, @function
load_idt:
	push	%ebp
	mov	%esp, %ebp

	mov	12(%ebp), %ax 	// Size

	cmp	$0, %ax
	je	1f
	mov	%ax, idtr

	mov	8(%ebp), %eax	// Offset
	mov	%eax, idtr + 2

	lidt	idtr

	xor	%eax, %eax	// Success
	jmp	2f

1:	mov	$1, %eax	// Fail

2:	pop	%ebp
	ret

idtr:
.word 0         // Offset
.long 0         // Size
