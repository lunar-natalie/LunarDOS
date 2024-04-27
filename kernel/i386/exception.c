// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#include <kernel/error.h>

#include <kernel/i386/cpu/isr.h>
#include <stdint.h>

void exception_handler(uint16_t isr, __attribute__((unused)) uint32_t error)
{
    switch (isr) {
    case DIVISION_ERROR:
        puts("Division error");
        kexit();
    case DEBUG:
        puts("Debug\n");
        break;
    case NMI:
        puts("NMI\n");
        break;
    case BREAKPOINT:
        puts("Breakpoint\n");
        break;
    case OVERFLOW:
        puts("Overflow\n");
        break;
    case BOUND_RANGE_EXCEEDED:
        puts("Bound range exceeded");
        kexit();
    case INVALID_OPCODE:
        puts("Invalid opcode");
        kexit();
    case DEVICE_NOT_AVAILABLE:
        puts("Device not available");
        kexit();
    case DOUBLE_FAULT:
        puts("Double fault");
        kexit();
    case INVALID_TSS:
        puts("Invalid TSS");
        kexit();
    case SEGMENT_NOT_PRESENT:
        puts("Segment not present");
        kexit();
    case STACK_SEGMENT_FAULT:
        puts("Stack segment fault");
        kexit();
    case GENERAL_PROTECTION_FAULT:
        puts("General protection fault");
        kexit();
    case PAGE_FAULT:
        puts("Page fault");
        kexit();
    case X87_FP_EXCEPTION:
        puts("x87 floating point exception");
        kexit();
    case ALIGNMENT_CHECK:
        puts("Alignment check");
        kexit();
    case MACHINE_CHECK:
        puts("Machine check");
        kexit();
    case SIMD_FP_EXCEPTION:
        puts("SIMD floating point exception");
        kexit();
    case VIRTUALIZATION_EXCEPTION:
        puts("Virtualization exception");
        kexit();
    case CONTROL_PROTECTION_EXCEPTION:
        puts("Control protection exception");
        kexit();
    case HYPERVISOR_INJECTION_EXCEPTION:
        puts("Hypervisor injection exception");
        kexit();
    case VMM_COMMUNICATION_EXCEPTION:
        puts("VMM communication exception");
        kexit();
    case SECURITY_EXCEPTION:
        puts("Security exception");
        kexit();
    default:
        puts("Exception");
        kexit();
    }
}
