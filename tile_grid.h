#pragma once
#include "raylib.h"
#include "math.h"

#define NUMTYPES (6)

typedef enum tile_type {
	empty,
	wall,
	dot,
	tunnel,
	ghost_house_entrance,
	energizer
};

typedef struct tile {
	Vector2 Centre;
	int size;
	enum tile_type type;
	int row;
	int collum;
	float frame;
}tile;

typedef struct tile_grid {
	tile current_tile;
	int rows;
	int collums;
	int delay;
	float flash;
	struct tile grid[36][28];
}grid;

grid Init_grid(int size, int a[36][28]);
void reset_grid(grid* g, int a[36][28]);
Vector2 tile_to_centre(int row, int collum, int size);
void Draw_grid(grid* g, Rectangle r[NUMTYPES], Texture2D t);
float Get_distance(float t1, float t2);
Vector2 centre_to_tile(int x, int y, grid*g);
float CalcDistance(Vector2 c1, Vector2 c2);
