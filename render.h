#pragma once

#include <stdbool.h>

/* terminal chars/codes */
static const char PIXEL = '▄';
static const char NEWLINE = '\n';
static const char* CLEAR="\033[H\033[2J";
static const char* BLACK = "30";
static const char* RED = "31";
static const char* GREEN = "32";
static const char* YELLOW = "33";
static const char* BLUE = "34";
static const char* MAGENTA = "35";
static const char* CYAN = "36";
static const char* WHITE = "37";

/*
 * 0-0: pixel
 * 1-4: prefix (\033[)
 * 5-6: color
 * 7-7: suffix (m)
 */
typedef char pixel_t[8];

bool init_render();
void resize();
void render();
void free_render();