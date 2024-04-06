# Libraries

add_library(Libc
        memory.c
        numeric.c
        printf.c
        string.c
)

target_sources(Libc PUBLIC FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
        FILES
        stdio.h
        stdlib.h
        string.h
)

set_target_properties(Libc PROPERTIES
        OUTPUT_NAME "libc"
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CFLAGS -O2 -Wall -Wextra -ffreestanding)
set(LDFLAGS -N -nostdlib -static)

target_include_directories(Libc PRIVATE ${CMAKE_SOURCE_DIR})
target_compile_options(Libc PRIVATE ${CFLAGS})
target_link_options(Libc PRIVATE ${LDFLAGS})
