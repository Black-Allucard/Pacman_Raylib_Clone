#pragma once
#include "entity.h"

enum dir reverse_dir(enum dir d) {
	if (d == UP) {
		return DOWN;
	}
	if (d == DOWN) {
		return UP;
	}
	if (d == LEFT) {
		return RIGHT;
	}
	if (d == RIGHT) {
		return LEFT;
	}
}

Vector2 dir_to_vec(enum dir d) {
	if (d == UP) {
		return (Vector2) {0,-1};
	}
	else if (d == DOWN) {
		return (Vector2) {0,1};
	}
	else if (d == LEFT) {
		return (Vector2) {-1,0};
	}
	else if (d == RIGHT) {
		return (Vector2) {1,0};
	}
}



tile set_current_tile(entity e,int size,grid*g) {
	int row = (centre_to_tile(e.centre.x, e.centre.y, g)).y;
	int collum = centre_to_tile(e.centre.x, e.centre.y, g).x;
	return (tile){ tile_to_centre(row,collum,(*g).current_tile.size),(*g).current_tile.size, (*g).grid[row][collum].type, row, collum };
	
}

tile get_current_tile(entity e) {
	return e.current_tile;
}

