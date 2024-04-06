/* Multiboot v1-compatible kernel bootstrap assembly
 * Copyright (c) 2024 Natalie Wiggins. All rights reserved.
 * SPDX-License-Identifier: GPL-3.0-or-later */

/* Multiboot constants */
.set ALIGN,	1 << 0
.set MEMINFO,	1 << 1
.set FLAGS,	ALIGN | MEMINFO
.set MAGIC,	0x1BADB002
.set CHECKSUM,	-(MAGIC + FLAGS)

/* Multiboot header */
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/* Stack (16K) */
.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

/* Entrypoint */
.section .text
.global _start
.type _start, @function
_start:
	mov	$stack_top, %esp
	call	kernel_main

.size _start, . - _start	/* Set symbol size for debugging */

/* Stop execution */
_end:
	cli
1:	hlt			/* Halt on NMI */
	jmp	1b
