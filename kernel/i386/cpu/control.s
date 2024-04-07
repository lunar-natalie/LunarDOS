// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-or-later

.global read_cr0
read_cr0:
	mov	%cr0, %eax
	ret

.global read_cr3
read_cr3:
	mov	%cr3, %eax
	ret

.global write_cr0
write_cr0:
	push	%ebp
	mov	%esp, %ebp
	mov	8(%ebp), %eax
	mov	%eax, %cr0
	pop	%ebp
	ret

.global write_cr3
write_cr3:
	push	%ebp
	mov	%esp, %ebp
	mov	8(%ebp), %eax
	mov	%eax, %cr3
	pop	%ebp
	ret
