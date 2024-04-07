# Kernel sources for i386

target_sources(Kernel PRIVATE
        boot.s
        cpu/control.s
        cpu/gdt.c
        cpu/gdt.s
        cpu/idt.c
        cpu/idt.s
        cpu/isr.s
        cpu/tss.c
        cpu/tss.s
        exception.c
        main.c
        tty.c
        video/vga.c
)
