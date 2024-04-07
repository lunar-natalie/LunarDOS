cmake_minimum_required(VERSION 3.27)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Setup toolchain
if(NOT(TARGET_PLATFORM))
    message(FATAL_ERROR "Unable to determine target platform")
endif()
include(Toolchain)

# Initialize project
project(os VERSION 1.0.0)

# Enable dependencies
include(Grub)
if(ENABLE_TESTS)
    include(CTest)
endif()

# Add source directories
add_subdirectory(lib)
add_subdirectory(kernel)
add_subdirectory(include)
add_subdirectory(image)
