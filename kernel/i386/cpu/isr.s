// Stubs for interrupt service routines.
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-or-later

.altmacro		// Enable macro parameters

.macro isr_stub irq
.align 4
isr_stub_\irq:
	iret
.endm

.macro isr_exception_stub irq
.align 4
.extern kernel_exception_handler
isr_stub_\irq:
	pusha
	cld			// DF must be clear on function entry
	call	kernel_exception_handler
	popa
	iret
.endm

// Stub for exceptions which push an error code onto the stack
.macro isr_exception_error_stub irq
.align 4
.extern kernel_exception_handler
isr_stub_\irq:
	pusha
	cld			// DF must be clear on function entry
	call	kernel_exception_handler
	popa
	sub	$8, %esp	// Pop error
	iret
.endm

.macro isr_table_entry irq
	.long isr_stub_\irq
.endm


.section .data

// ISR stub table for the IDT
.global isr_stub_table
.align 4
isr_stub_table:
.set i, 0
.rept 255
	isr_table_entry %i
	.set i, i+1
.endr


.section .text

// Exceptions
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
isr_exception_stub 10 // Invalid TSS
isr_exception_stub 11 // Segment not present
isr_exception_stub 12 // Stack-segment fault
isr_exception_stub 13 // General protection fault
isr_exception_stub 14 // Page fault
isr_stub 15 // Reserved
isr_exception_stub 16 // x87 floating point exception
isr_exception_stub 17 // Alignment check
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

# Standard interrupts
isr_stub 32
isr_stub 33
isr_stub 34
isr_stub 35
isr_stub 36
isr_stub 37
isr_stub 38
isr_stub 39
isr_stub 40
isr_stub 41
isr_stub 42
isr_stub 43
isr_stub 44
isr_stub 45
isr_stub 46
isr_stub 47
isr_stub 48
isr_stub 49
isr_stub 50
isr_stub 51
isr_stub 52
isr_stub 53
isr_stub 54
isr_stub 55
isr_stub 56
isr_stub 57
isr_stub 58
isr_stub 59
isr_stub 60
isr_stub 61
isr_stub 62
isr_stub 63
isr_stub 64
isr_stub 65
isr_stub 66
isr_stub 67
isr_stub 68
isr_stub 69
isr_stub 70
isr_stub 71
isr_stub 72
isr_stub 73
isr_stub 74
isr_stub 75
isr_stub 76
isr_stub 77
isr_stub 78
isr_stub 79
isr_stub 80
isr_stub 81
isr_stub 82
isr_stub 83
isr_stub 84
isr_stub 85
isr_stub 86
isr_stub 87
isr_stub 88
isr_stub 89
isr_stub 90
isr_stub 91
isr_stub 92
isr_stub 93
isr_stub 94
isr_stub 95
isr_stub 96
isr_stub 97
isr_stub 98
isr_stub 99
isr_stub 100
isr_stub 101
isr_stub 102
isr_stub 103
isr_stub 104
isr_stub 105
isr_stub 106
isr_stub 107
isr_stub 108
isr_stub 109
isr_stub 110
isr_stub 111
isr_stub 112
isr_stub 113
isr_stub 114
isr_stub 115
isr_stub 116
isr_stub 117
isr_stub 118
isr_stub 119
isr_stub 120
isr_stub 121
isr_stub 122
isr_stub 123
isr_stub 124
isr_stub 125
isr_stub 126
isr_stub 127
isr_stub 128
isr_stub 129
isr_stub 130
isr_stub 131
isr_stub 132
isr_stub 133
isr_stub 134
isr_stub 135
isr_stub 136
isr_stub 137
isr_stub 138
isr_stub 139
isr_stub 140
isr_stub 141
isr_stub 142
isr_stub 143
isr_stub 144
isr_stub 145
isr_stub 146
isr_stub 147
isr_stub 148
isr_stub 149
isr_stub 150
isr_stub 151
isr_stub 152
isr_stub 153
isr_stub 154
isr_stub 155
isr_stub 156
isr_stub 157
isr_stub 158
isr_stub 159
isr_stub 160
isr_stub 161
isr_stub 162
isr_stub 163
isr_stub 164
isr_stub 165
isr_stub 166
isr_stub 167
isr_stub 168
isr_stub 169
isr_stub 170
isr_stub 171
isr_stub 172
isr_stub 173
isr_stub 174
isr_stub 175
isr_stub 176
isr_stub 177
isr_stub 178
isr_stub 179
isr_stub 180
isr_stub 181
isr_stub 182
isr_stub 183
isr_stub 184
isr_stub 185
isr_stub 186
isr_stub 187
isr_stub 188
isr_stub 189
isr_stub 190
isr_stub 191
isr_stub 192
isr_stub 193
isr_stub 194
isr_stub 195
isr_stub 196
isr_stub 197
isr_stub 198
isr_stub 199
isr_stub 200
isr_stub 201
isr_stub 202
isr_stub 203
isr_stub 204
isr_stub 205
isr_stub 206
isr_stub 207
isr_stub 208
isr_stub 209
isr_stub 210
isr_stub 211
isr_stub 212
isr_stub 213
isr_stub 214
isr_stub 215
isr_stub 216
isr_stub 217
isr_stub 218
isr_stub 219
isr_stub 220
isr_stub 221
isr_stub 222
isr_stub 223
isr_stub 224
isr_stub 225
isr_stub 226
isr_stub 227
isr_stub 228
isr_stub 229
isr_stub 230
isr_stub 231
isr_stub 232
isr_stub 233
isr_stub 234
isr_stub 235
isr_stub 236
isr_stub 237
isr_stub 238
isr_stub 239
isr_stub 240
isr_stub 241
isr_stub 242
isr_stub 243
isr_stub 244
isr_stub 245
isr_stub 246
isr_stub 247
isr_stub 248
isr_stub 249
isr_stub 250
isr_stub 251
isr_stub 252
isr_stub 253
isr_stub 254
isr_stub 255
