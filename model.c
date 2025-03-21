#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "model.h"

/* loaders */
extern bool load_gltf_model(
    model_t* model,
    const char* path);
extern bool load_obj_model(
    model_t* model,
    const char* path);

bool load_model(
    model_t* model,
    const char* path)
{
    if (strstr(path, ".gltf"))
    {
        return load_gltf_model(model, path);
    }
    else if (strstr(path, ".obj"))
    {
        return load_obj_model(model, path);
    }
    else
    {
        printf("Unsupported model format: %s\n", path);
        return -1;
    }
}