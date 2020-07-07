
#include <stdio.h>

#include "graphics.h"
#include "map.h"


void update() {
	if (IsKeyPressed(KEY_RIGHT)) map_move(RIGHT);
	if (IsKeyPressed(KEY_LEFT)) map_move(LEFT);
	if (IsKeyPressed(KEY_UP)) map_move(UP);
	if (IsKeyPressed(KEY_DOWN)) map_move(DOWN);

}

void render() {
	BeginDrawing();
	ClearBackground(RAYWHITE);

	graphics_map_draw(map_data, map_width, map_height);

	EndDrawing();

}

int main(void) {
	srand(time(NULL));

	graphics_window_create("2048C", 800, 600);

	map_reset(8, 8);
	map_add_random_values(16);



	while (!WindowShouldClose()) {

		update();

		render();
	}

	map_free();
	graphics_window_destroy();

	return 0;
}

