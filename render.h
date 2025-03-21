#pragma once

#include <stdbool.h>
#include "model.h"

bool init_render();
void resize();
void render(
    const model_t* model);
void free_render();