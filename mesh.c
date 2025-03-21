#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mesh.h"

/* loaders */
extern bool load_gltf_mesh(
    mesh_t* mesh,
    const char* path);
extern bool load_obj_mesh(
    mesh_t* mesh,
    const char* path);

bool load_mesh(
    mesh_t* mesh,
    const char* path)
{
    if (strstr(path, ".gltf"))
    {
        return load_gltf_mesh(mesh, path);
    }
    else if (strstr(path, ".obj"))
    {
        return load_obj_mesh(mesh, path);
    }
    else
    {
        printf("Unsupported mesh format: %s\n", path);
        return -1;
    }
}

void free_mesh(
    mesh_t* mesh)
{
    free(mesh->vertices);
    mesh->vertices = NULL;
    mesh->size = 0;
}