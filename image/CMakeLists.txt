# Bootable disk image

if((GRUB_MKRESCUE STREQUAL "GRUB_MKRESCUE-NOTFOUND") OR (XORRISO STREQUAL "XORRISO-NOTFOUND"))
    message("-- Unable to find grub-mkrescue/xorriso - image build is disabled")
    return()
endif()

set(ISO_DIR "${CMAKE_CURRENT_BINARY_DIR}/iso")
set(ISO_FILE "${CMAKE_BINARY_DIR}/system.iso")

file(READ "${CMAKE_CURRENT_SOURCE_DIR}/grub.cfg.in" GRUB_CFG)
file(GENERATE OUTPUT "${ISO_DIR}/boot/grub/grub.cfg" CONTENT ${GRUB_CFG})

add_custom_command(OUTPUT ${ISO_FILE}
        COMMAND cp "$<TARGET_FILE:Kernel>" "${ISO_DIR}/boot/$<TARGET_FILE_NAME:Kernel>"
        COMMAND ${GRUB_MKRESCUE} -o "${ISO_FILE}" "${ISO_DIR}"
        DEPENDS Kernel)

add_custom_target(Image ALL DEPENDS ${ISO_FILE})
