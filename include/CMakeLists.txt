# Include directory

target_sources(Libc PUBLIC FILE_SET HEADERS
        BASE_DIRS ${CMAKE_SOURCE_DIR}
        FILES
        stdio.h
        stdlib.h
        string.h
)
