#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <raylib.h>
#include <stdio.h>

#include "common.h"

static Color graphics_map_palette[12];
static Color graphics_map_background[2];

static bool graphics_is_window_created;
static int graphics_tile_size;
static int graphics_background_tile_offset;

extern void graphics_window_create(const char* title, int width, int height);
extern void graphics_window_destroy();

extern void graphics_map_draw(int* map, int map_width, int map_height);



void graphics_map_draw_rectangle(int x, int y, int value);
void graphics_map_draw_background(int width, int height);



#endif // !GRAPHICS_H
