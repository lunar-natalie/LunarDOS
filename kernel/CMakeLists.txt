# Kernel build config

add_executable(Kernel)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_ARCH}")

set_target_properties(Kernel PROPERTIES
        OUTPUT_NAME "kernel"
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CFLAGS -O2 -Wall -Wextra -ffreestanding)
set(LDFLAGS -N -nostdlib -static -z noexecstack --no-warn-rwx-segments)
set(LD_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_ARCH}/link.ld")

target_compile_options(Kernel PRIVATE $<$<COMPILE_LANGUAGE:C>:${CFLAGS}>)
target_link_options(Kernel PRIVATE ${LDFLAGS} -T${LD_SCRIPT})
set_property(TARGET Kernel APPEND PROPERTY LINK_DEPENDS ${LD_SCRIPT})