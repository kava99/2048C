#include "graphics.h"

bool graphics_is_window_created = false;
Color graphics_map_palette[12] = {
	{178, 212, 245, 255},
	{147, 191, 235, 255},
	{88, 153, 218, 255},
	{24, 102, 180, 255},
	
	{252, 195, 167, 255},
	{245, 170, 133, 255},
	{232, 116, 59, 255},
	{204, 67, 0, 255},
	
	{143, 209, 187, 255},
	{25, 169, 121, 255},
	{3, 115, 77, 255},
	{214, 47, 47, 255},
};


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
	int palette_index = from_value_to_index(value);
	if (palette_index > 11) palette_index = 11;
	DrawRectangle(x * 32, y * 32, 32, 32, graphics_map_palette[palette_index]);
	DrawText(FormatText("%i", value), x * 32, y * 32, 20, BLACK);
}
