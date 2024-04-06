# Kernel sources for i386

target_sources(Kernel PRIVATE
        main.c
        start.s
        tty.c
        vga.c
)
