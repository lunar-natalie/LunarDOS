# Kernel include directory for i386

target_sources(Kernel PUBLIC FILE_SET HEADERS
        FILES
        cpu/cr.h
        cpu/gdt.h
        cpu/idt.h
        cpu/tss.h
        mm/defs.h
        mm/frame.h
        mm/init.h
        mm/paging.h
        mm/vm.h
        vga.h
)
