# Kernel include directory for i386

target_sources(Kernel PUBLIC FILE_SET HEADERS
        FILES
        cpu/cr.h
        cpu/gdt.h
        cpu/idt.h
        cpu/paging.h
        cpu/tss.h
        vga.h
)
