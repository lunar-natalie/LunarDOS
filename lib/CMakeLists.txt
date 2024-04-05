# Libraries

add_library(Libc
        string.c
)

target_sources(Libc PUBLIC FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
        FILES
            string.h
)

set_target_properties(Libc PROPERTIES
        OUTPUT_NAME "libc"
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CFLAGS -O2 -Wall -Wextra -ffreestanding)
set(LDFLAGS -N -nostdlib -static)

target_compile_options(Libc PRIVATE ${CFLAGS})
target_link_options(Libc PRIVATE ${LDFLAGS})
