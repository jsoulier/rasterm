#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "render.h"
#include "term.h"

static float* depths;
static pixel_t* pixels;
static int width;
static int height;

bool init_render()
{
    resize();
    return true;
}

void resize()
{
    /* width + 1 for newlines */
    const int w = get_width() + 1;
    const int h = get_height();
    if (width == w && height == h)
    {
        return;
    }
    free(depths);
    free(pixels);
    depths = malloc(sizeof(float) * w * h);
    pixels = malloc(sizeof(pixel_t) * w * h);
    if (!depths || !pixels)
    {
        printf("Failed to allocate framebuffer");
        return;
    }
    width = w;
    height = h;
    for (int x = 0; x < width; x++)
    for (int y = 0; y < height; y++)
    {
        pixels[y * width + x][0] = PIXEL;
        pixels[y * width + x][1] = '\0';
        pixels[y * width + x][2] = '3';
        pixels[y * width + x][3] = '3';
        pixels[y * width + x][4] = '[';
        pixels[y * width + x][7] = 'm';
    }
    for (int y = 0; y < height; y++)
    {
        pixels[y * width][0] = NEWLINE;
    }
}

void render()
{
    for (int x = 0; x < width; x++)
    for (int y = 0; y < height; y++)
    {
        depths[y * width + x] = 1.0f;
        pixels[y * width + x][5] = BLACK[0];
        pixels[y * width + x][6] = BLACK[1];
    }
    printf("testing");
    printf(CLEAR);
    printf("asdasdasd2222");
}

void free_render()
{
    free(depths);
    free(pixels);
    depths = NULL;
    pixels = NULL;
}