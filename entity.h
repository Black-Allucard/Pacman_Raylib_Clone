#pragma once
#include "raylib.h"
#include "tile_grid.h"

typedef enum dir {
	RIGHT,
	DOWN,
	LEFT,
	UP,
	NUM_DIRS
}dir;

typedef struct entity {
	Vector2 centre;
	tile current_tile;
	enum dir dir;
}entity;

enum dir reverse_dir(enum dir d);
Vector2 dir_to_vec(enum dir d);
bool is_tile_blocking(grid* g, enum dir wanted_dir, tile t2);
tile set_current_tile(entity e, int size, grid*g);
tile get_current_tile(entity* e);

