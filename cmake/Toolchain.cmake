# Loads the toolchain for the target platform

if(NOT (TARGET_PLATFORM))
    message("-- TARGET_PLATFORM not set - skipped toolchain setup")
    return()
endif()

# Split target
string(REPLACE "-" ";" TARGET_LIST "${TARGET_PLATFORM}")
list(GET TARGET_LIST 0 TARGET_MACH)
list(GET TARGET_LIST 1 TARGET_ENV)
set(TARGET_PREFIX "${TARGET_PLATFORM}-")

# Set architecture
if("${TARGET_MACH}" MATCHES "^i.86$")
    set(TARGET_ARCH "i386")
else()
    set(TARGET_ARCH "${TARGET_MACH}")
endif()

# Parse system name
if("${TARGET_ENV}" MATCHES "^elf.*$")
    set(CMAKE_SYSTEM_NAME "Generic-ELF")
else()
    set(CMAKE_SYSTEM_NAME "Generic")
endif()

find_program(CMAKE_ASM-ATT_COMPILER "${TARGET_PREFIX}as" REQUIRED)
find_program(CMAKE_C_COMPILER "${TARGET_PREFIX}gcc" REQUIRED)
find_program(C_LINK_EXECUTABLE "${TARGET_PREFIX}ld" REQUIRED)

set(CMAKE_C_LINK_EXECUTABLE "${C_LINK_EXECUTABLE} <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_C_STANDARD 11 REQUIRED)
