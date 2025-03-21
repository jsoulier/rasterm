cmake_minimum_required(VERSION 3.24)
project(rasterm)

set(BINARY_DIR ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BINARY_DIR})

add_executable(rasterm
    main.c
    model.c
    model_gltf.c
    model_obj.c
    render.c
    stb.c
)
if(WIN32)
    target_sources(rasterm PUBLIC
        term_win32.c
    )
else()
    target_sources(rasterm PUBLIC
        term_posix.c
    )
endif()
set_target_properties(rasterm PROPERTIES C_STANDARD 11)