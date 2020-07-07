#include "map.h"

int* map_data;
int map_width;
int map_height;

void map_reset(int width, int height)
{
	map_free();
	map_data = malloc(sizeof(int) * width * height);
	map_width = width;
	map_height = height;

	memset(map_data, 0, sizeof(int) * width * height);
}

void map_free()
{
	free(map_data);
}



void map_add_random_values(int num_of_values)
{
	if (map_data == 0)
		return;

	for (int i = 0; i < num_of_values; ++i) {
		if (map_is_full())
			return;

		while (1) {
			int r = rand() % (map_width * map_height);
			if (map_data[r] == 0) {
				int r2 = (rand() % 2) + 1;
				map_data[r] = r2 * 2;
				break;
			}
		}
	}

}

bool map_is_full()
{
	if (map_data == 0)
		return;

	for (int i = 0; i < map_width * map_height; ++i) {
		if (map_data[i] == 0)
			return false;
	}
	return true;
}

void map_move(Dir dir)
{
	switch (dir) {
	case RIGHT:
		_map_fall();
		_map_collide();
		break;
	case LEFT:
		_map_flip();
		_map_fall();
		_map_collide();
		_map_flip();
		break;
	case UP:
		_map_rotate();
		_map_flip();
		_map_fall();
		_map_collide();
		_map_flip();
		_map_rotate();
		break;
	case DOWN:
		_map_rotate();
		_map_fall();
		_map_collide();
		_map_rotate();
		break;
	}

	map_add_random_values(1);
}

void _map_collide_row(int row)
{
	if (map_data == 0)
		return;

	if (_map_is_row_empty(row))
		return;

	for (int i = map_width - 1; i > 0; --i) {
		if (map_data[_vtp(i - 1, row)] == 0)
			break;
		if (map_data[_vtp(i - 1, row)] == map_data[_vtp(i, row)]) {
			map_data[_vtp(i, row)] *= 2;
			map_data[_vtp(i - 1, row)] = 0;
			--i;
		}
	}
}

void _map_collide()
{
	for (int i = 0; i < map_height; ++i) {
		_map_collide_row(i);
	}

	_map_fall();
}

void _map_fall_row(int row)
{
	if (map_data == 0)
		return;

	if (_map_is_row_full(row))
		return;

	if (_map_is_row_empty(row))
		return;

	int last_free_space = map_width - 1;
	if (map_data[_vtp(map_width - 1, row)] != 0)
		last_free_space--;

	for (int i = map_width - 2; i > -1; --i) {
		if (map_data[_vtp(i, row)] != 0) {
			if(i != last_free_space) {
				map_data[_vtp(last_free_space, row)] = map_data[_vtp(i, row)];
				map_data[_vtp(i, row)] = 0;
			}
			last_free_space--;
		}
	}
}

bool _map_is_row_full(int row)
{
	if (map_data == 0)
		return;

	for (int i = 0; i < map_width; ++i) {
		if (map_data[(map_width * row) + i] == 0)
			return false;
	}
	return true;
}

bool _map_is_row_empty(int row)
{
	if (map_data == 0)
		return;

	for (int i = 0; i < map_width; ++i) {
		if (map_data[(map_width * row) + i] != 0)
			return false;
	}
	return true;
}

void _map_fall()
{
	for (int i = 0; i < map_height; ++i) {
		_map_fall_row(i);
	}
}

void _map_rotate()
{
	if (map_data == 0)
		return;

	int* new_map = malloc(sizeof(int) * map_width * map_height);
	int old_width = map_width;
	int old_height = map_height;
	map_width = old_height;
	map_height = old_width;

	for (int y = 0; y < old_height; ++y) {
		for (int x = 0; x < old_width; ++x) {
			new_map[(x * old_height) + y] = map_data[(y * old_width) + x];
		}
	}

	free(map_data);
	map_data = new_map;
}

void _map_flip()
{
	if (map_data == 0)
		return;

	int* new_map = malloc(sizeof(int) * map_width * map_height);

	for (int y = 0; y < map_height; ++y) {
		for (int x = 0; x < map_width; ++x) {
			new_map[_vtp(x, y)] = map_data[_vtp(map_width - x - 1, y)];
		}
	}

	free(map_data);
	map_data = new_map;
}

int _vtp(int x, int y)
{
	return (y * map_width) + x;
}
