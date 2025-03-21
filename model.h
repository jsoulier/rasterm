#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "vertex.h"

typedef struct
{
    vertex_t* vertices;
    uint32_t size;
}
model_t;

bool load_model(
    model_t* model,
    const char* path);