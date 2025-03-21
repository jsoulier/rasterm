cmake_minimum_required(VERSION 3.24)
project(rasterm)

set(BINARY_DIR ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BINARY_DIR})

add_executable(rasterm
    main.c
    matrix.c
    mesh.c
    mesh_gltf.c
    mesh_obj.c
    path.c
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
find_library(LIBM m)
if(LIBM)
    target_link_libraries(rasterm m)
endif()