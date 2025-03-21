#include <stdio.h>
#include <stdlib.h>
#include "mesh.h"
#include "render.h"
#include "term.h"

int main(
    int argc,
    char** argv)
{
    if (argc < 2)
    {
        printf("Missing path to mesh\n");
        return EXIT_FAILURE;
    }
    mesh_t mesh;
    if (!load_mesh(&mesh, argv[1]))
    {
        printf("Failed to load mesh: %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    init_render();
    // render(&mesh);

    /* todo */
    // while (1)
    // {
    //     render();
    // }

    free_render();
    free_mesh(&mesh);
    return EXIT_SUCCESS;
}