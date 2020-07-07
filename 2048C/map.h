#ifndef MAP_H
#define MAP_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef enum {
	UP,
	DOWN,
	RIGHT,
	LEFT,
}Dir;


extern int* map_data;
extern int map_width;
extern int map_height;

extern void map_reset(int width, int height);
extern void map_free();
extern void map_add_random_values(int num_of_values);
extern bool map_is_full();
extern void map_move(Dir dir);



bool _map_is_row_full(int row);
bool _map_is_row_empty(int row);

void _map_collide_row(int row);
void _map_collide();

void _map_fall_row(int row);
void _map_fall();

void _map_rotate();
void _map_flip();

int _vtp(int x, int y);



#endif // !MAP_H
