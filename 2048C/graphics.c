#include "graphics.h"

bool graphics_is_window_created = false;



void graphics_window_create(const char* title, int width, int height)
{
	if (graphics_is_window_created)
		return;

	SetTargetFPS(60);
	InitWindow(width, height, title);

	graphics_is_window_created = true;
}

void graphics_window_destroy()
{
	if (!graphics_is_window_created)
		return;

	CloseWindow();

	graphics_is_window_created = false;
}


void graphics_map_draw(int* map, int map_width, int map_height)
{
	for (int y = 0; y < map_height; ++y) {
		for (int x = 0; x < map_width; ++x) {
			graphics_map_draw_rectangle(x, y, map[y * map_width + x]);
		}
	}
}

void graphics_map_draw_rectangle(int x, int y, int value)
{
	DrawRectangle(x * 32, y * 32, 32, 32, (Color) { value * 4, value * 4, value * 4, 255 });
	DrawText(FormatText("%i", value), x * 32, y * 32, 20, LIGHTGRAY);
}
