#include "render.h"
#include "term.h"

int main(
    int argc,
    char** argv)
{
    init_render();
    render();
    while (1)
    {
        // render();
    }
    free_render();
    return 0;
}