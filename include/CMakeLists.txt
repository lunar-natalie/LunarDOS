# Base include directory

target_sources(Libc PUBLIC FILE_SET HEADERS
        FILES
        stdio.h
        string.h
)

add_subdirectory(kernel)
