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
        float x;
        float y;
    }
    uv;
    struct
    {
        float x;
        float y;
        float z;
    }
    normal;
}
vertex_t;