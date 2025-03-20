#pragma once

#include <stdbool.h>

/* terminal chars/codes */
static const char PIXEL = '#';
static const char* REWIND = "\033[H\033[2J";
static const char* HIDE = "\033[?25l";
static const char* BLACK = "30";
static const char* RED = "31";
static const char* GREEN = "32";
static const char* YELLOW = "33";
static const char* BLUE = "34";
static const char* MAGENTA = "35";
static const char* CYAN = "36";
static const char* WHITE = "37";

/*
 * 0-1: prefix (\033[)
 * 2-3: color
 * 4-4: suffix (m)
 * 5-6: pixel
 */
typedef char pixel_t[6];

bool init_render();
void resize();
void render();
void free_render();