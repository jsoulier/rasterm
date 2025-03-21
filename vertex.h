#pragma once

typedef struct
{
    struct
    {
        float x;
        float y;
        float z;
    }
    position;
    struct
    {
        float r;
        float g;
        float b;
    }
    colour;
    struct
    {
        float x;
        float y;
        float z;
    }
    normal;
}
vertex_t;