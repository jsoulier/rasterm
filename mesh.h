#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "vertex.h"

typedef struct
{
    vertex_t* vertices;
    uint32_t size;
}
mesh_t;

bool load_mesh(
    mesh_t* mesh,
    const char* path);
void free_mesh(
    mesh_t* mesh);