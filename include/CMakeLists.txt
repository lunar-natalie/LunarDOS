# Base include directory

target_sources(Libc PUBLIC FILE_SET HEADERS
        FILES
        number.h
        stdio.h
        stdlib.h
        string.h
)

add_subdirectory(kernel)
