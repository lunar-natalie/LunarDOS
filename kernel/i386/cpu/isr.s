// Stubs for interrupt service routines
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-or-later

.extern exception_handler

.altmacro			// Enable macro parameters

.macro isr_stub i
.align 4
isr_stub_\i:
	iret
.endm

.macro isr_exception_stub i
.align 4
isr_stub_\i:
	pushl	$0		// Error code
	pushw	$\i		// ISR
	cld			// Clear DF before function entry
	call	exception_handler

	sub	$12, %esp	// Pop error code and ISR
	iret
.endm

.macro isr_exception_error_stub i
.align 4
isr_stub_\i:
	pushw	$\i		// ISR
	cld			// Clear DF before function entry
	call	exception_handler

	sub	$12, %esp	// Pop error code and ISR
	iret
.endm

.macro isr_table_entry i
.long isr_stub_\i
.endm


.section .data

.global isr_stub_table
.align 4
isr_stub_table:
.set i, 0
.rept 255
isr_table_entry %i
.set i, i + 1
.endr


.section .text

// Exceptions (0-31)
isr_exception_stub 0 // Division error
isr_exception_stub 1 // Debug
isr_stub 2 // NMI
isr_exception_stub 3 // Breakpoint
isr_exception_stub 4 // Overflow
isr_exception_stub 5 // Bound range exceeded
isr_exception_stub 6 // Invalid opcode
isr_exception_stub 7 // Device not available
isr_stub 8 // Double fault
isr_stub 9 // Coprocessor segment overrun (pre-586)
isr_exception_error_stub 10 // Invalid TSS
isr_exception_error_stub 11 // Segment not present
isr_exception_error_stub 12 // Stack-segment fault
isr_exception_error_stub 13 // General protection fault
isr_exception_error_stub 14 // Page fault
isr_stub 15 // Reserved
isr_exception_stub 16 // x87 floating point exception
isr_exception_error_stub 17 // Alignment check
isr_stub 18 // Machine check
isr_exception_stub 19 // SIMD floating point exception
isr_exception_stub 20 // Virtualization exception
isr_exception_error_stub 21 // Control protection exception
isr_stub 22 // Reserved
isr_stub 23 // Reserved
isr_stub 24 // Reserved
isr_stub 25 // Reserved
isr_stub 26 // Reserved
isr_stub 27 // Reserved
isr_exception_stub 28 // Hypervisor injection exception
isr_exception_error_stub 29 // VMM communication exception
isr_exception_error_stub 30 // Security exception
isr_stub 31 // Reserved

# Standard interrupts (32-255)
.set i, 32
.rept 255 - i
isr_stub %i
.set i, i + 1
.endr
