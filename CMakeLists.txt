cmake_minimum_required(VERSION 3.24)
project(rasterm)

set(BINARY_DIR ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BINARY_DIR})

if(WIN32)
    add_executable(rasterm
        main.c
        render.c
        term_win32.c
    )
else()
    add_executable(rasterm
        main.c
        render.c
        term_posix.c
    )
    message(FATAL_ERROR "Not Implemented")
endif()
set_target_properties(rasterm PROPERTIES C_STANDARD 11)