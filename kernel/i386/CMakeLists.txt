# Kernel sources for i386

target_sources(Kernel PRIVATE
        console.c
        cpu/cr.s
        cpu/gdt.c
        cpu/gdt.s
        cpu/idt.c
        cpu/idt.s
        cpu/isr.s
        cpu/paging.c
        cpu/tss.c
        cpu/tss.s
        exception.c
        loader.s
        main.c
        mm.c
        vga.c
)

if(ENABLE_TESTS)
    if(GRUB_FILE STREQUAL "GRUB_FILE-NOTFOUND")
        message("-- Unable to find grub-file - Multiboot test is disabled")
    else()
        add_test(NAME Multiboot COMMAND ${GRUB_FILE} --is-x86-multiboot "$<TARGET_FILE:Kernel>")
    endif()
endif()
