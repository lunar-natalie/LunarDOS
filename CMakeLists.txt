cmake_minimum_required(VERSION 3.27)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(Toolchain)

project(os VERSION 1.0.0)

include(Grub)
if(ENABLE_TESTS)
    include(CTest)
endif()

add_subdirectory(lib)
add_subdirectory(kernel)
add_subdirectory(include)
add_subdirectory(image)
