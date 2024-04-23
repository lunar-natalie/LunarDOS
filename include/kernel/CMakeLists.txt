# Kernel include directory

target_sources(Kernel PUBLIC FILE_SET HEADERS
        FILES
        console.h
        error.h
        mm.h
        version.h
)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_ARCH}")
