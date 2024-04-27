# Base include directory

target_sources(Libc PUBLIC FILE_SET HEADERS
        FILES
        stdio.h
        stdlib.h
        string.h
        utils.h
)

add_subdirectory(kernel)
