# Kernel build config

add_executable(Kernel)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_ARCH}")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/version.c.in" "${CMAKE_CURRENT_BINARY_DIR}/version.c")
target_sources(Kernel PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/version.c")

set_target_properties(Kernel PROPERTIES
        OUTPUT_NAME "kernel"
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CFLAGS -O2 -Wall -Wextra -ffreestanding)
set(LDFLAGS -N -nostdlib -static -z noexecstack --no-warn-rwx-segments)
set(LD_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_ARCH}/link.ld")

target_compile_options(Kernel PRIVATE $<$<COMPILE_LANGUAGE:C>:${CFLAGS}>)
target_include_directories(Kernel PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Kernel PRIVATE Libc)
target_link_options(Kernel PRIVATE ${LDFLAGS} -T${LD_SCRIPT})
set_property(TARGET Kernel APPEND PROPERTY LINK_DEPENDS ${LD_SCRIPT})
