#include "graphics.h"

bool graphics_is_window_created = false;
graphics_background_tile_offset = 7;
graphics_tile_size = 64;

Color graphics_map_palette[12] = {
	{178, 212, 245, 255},
	{147, 191, 235, 255},
	{88, 153, 218, 255},
	{24, 102, 180, 255},
	
	{143, 209, 187, 255},
	{25, 169, 121, 255},
	{3, 115, 77, 255},
	
	{252, 195, 167, 255},
	{245, 170, 133, 255},
	{232, 116, 59, 255},
	{204, 67, 0, 255},

	{214, 47, 47, 255},
};

Color graphics_map_background[2] = {
	{187, 173, 160, 255},
	{205, 192, 180, 255},
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
	graphics_map_draw_background(map_width, map_height);

	for (int y = 0; y < map_height; ++y) {
		for (int x = 0; x < map_width; ++x) {
			graphics_map_draw_rectangle(x, y, map[y * map_width + x]);
		}
	}
}

void graphics_map_draw_rectangle(int x, int y, int value)
{
	if (value == 0) return;

	int off = graphics_background_tile_offset;
	int tile = graphics_tile_size;
	int tile_off = off + tile;

	int palette_index = from_value_to_index(value);
	if (palette_index > 11) palette_index = 11;


	DrawRectangle((x * tile_off) + off, (y * tile_off) + off, tile, tile, graphics_map_palette[palette_index]);
	DrawText(FormatText("%i", value), (x * tile_off) + off, (y * tile_off) + off, 20, BLACK);
}

void graphics_map_draw_background(int width, int height)
{
	int off = graphics_background_tile_offset;
	int tile = graphics_tile_size;

	Vector2 bg_size = { ((width * (off + tile)) + off),
						((height * (off + tile)) + off) };

	DrawRectangle(0, 0, bg_size.x, bg_size.y, graphics_map_background[1]);

	for (int x = 0; x < width + 1; ++x) {
		Vector2 start = { (x * (off + tile)) + (off / 2.0f), 0 };
		Vector2 end = { (x * (off + tile)) + (off / 2.0f), bg_size.y };

		DrawLineEx(start, end, off, graphics_map_background[0]);
	}
	

	for (int y = 0; y < height + 1; ++y) {
		Vector2 start = { 0, (y * (off + tile)) + (off / 2.0f) };
		Vector2 end = { bg_size.x, (y * (off + tile)) + (off / 2.0f) };

		DrawLineEx(start, end, off, graphics_map_background[0]);
	}
}
