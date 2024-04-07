# Libraries

add_library(Libc
        memory.c
        numeric.c
        printf.c
        string.c
)

set_target_properties(Libc PROPERTIES
        OUTPUT_NAME "c"
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CFLAGS -O2 -Wall -Wextra -ffreestanding)
set(LDFLAGS -N -nostdlib -static)

target_include_directories(Libc PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_link_options(Libc PRIVATE ${LDFLAGS})
target_compile_options(Libc PRIVATE ${CFLAGS})
