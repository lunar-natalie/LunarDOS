# Kernel include directory

target_sources(Kernel PUBLIC FILE_SET HEADERS
        FILES
        console.h
        defs.h
        error.h
        version.h
)
