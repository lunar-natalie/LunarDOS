cmake_minimum_required(VERSION 3.27)

if(NOT (TARGET_PLATFORM))
    message(FATAL_ERROR "Unable to determine target platform")
endif()
include(Toolchain.cmake)

project(os VERSION 1.0.0)

add_subdirectory(lib)
add_subdirectory(kernel)
add_subdirectory(include)
add_subdirectory(image)
