cmake_minimum_required(VERSION 3.27)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(Toolchain)

project(os
        VERSION 1.0.0
        LANGUAGES C ASM-ATT)

include(Grub)
if(ENABLE_TESTS)
    set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)
    include(CTest)
    enable_testing()
endif()

add_subdirectory(lib)
add_subdirectory(kernel)
add_subdirectory(include)
add_subdirectory(image)
