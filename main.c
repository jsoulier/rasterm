#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include "render.h"
#include "term.h"

int main(
    int argc,
    char** argv)
{
    if (argc < 2)
    {
        printf("Missing path to model\n");
        return EXIT_FAILURE;
    }
    model_t model;
    if (!load_model(&model, argv[1]))
    {
        printf("Failed to load model: %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    init_render();
    render(&model);

    /* todo */
    // while (1)
    // {
    //     render();
    // }

    free_render();
    return EXIT_SUCCESS;
}