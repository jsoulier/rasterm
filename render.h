#pragma once

#include <stdbool.h>
#include "mesh.h"

bool init_render();
void resize();
void render(
    const mesh_t* mesh);
void free_render();