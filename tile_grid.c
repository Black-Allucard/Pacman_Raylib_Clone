#include "tile_grid.h"
#include "stdio.h"
// gebruikt om de coördinaten van de tile t.o.v het scherm
Vector2 tile_to_centre(int row, int collum, int size) {
	int x = (size / 2) + (collum * size);
	int y = (size / 2) + (row * size);

	return (Vector2) { x, y };
}

grid Init_grid(int size, int a[36][28]) {
	grid g;
	g.current_tile = (tile){ tile_to_centre(0,0,size),size,0,0 };
	g.rows = 36;
	g.collums = 28;
	for (int i = 0; i < g.rows; i++) {
		for (int j = 0; j < g.collums; j++) {
			g.grid[i][j] = (tile){ (Vector2) { tile_to_centre(i,j,size).x, tile_to_centre(i,j,size).y },size,a[i][j], i, j };
		}
	}
	g.delay = 4;
	g.flash = 0;
	return g;
}

void reset_grid(grid* g, int a[36][28]) {
	for (int i = 0; i < (*g).rows; i++) {
		for (int j = 0; j < (*g).collums; j++) {
			(*g).grid[i][j].type = a[i][j];
		}
	}
};

void Draw_grid(grid* g, Rectangle r[NUMTYPES], Texture2D t) {
	for (int i = 0; i < (*g).rows; i++) {
		for (int j = 0; j < (*g).collums; j++) {
			if ((*g).grid[i][j].type == dot || (*g).grid[i][j].type == energizer) {
				if ((*g).grid[i][j].type == energizer) {
					if ((*g).flash >= 1) {
						DrawTexturePro(t, r[(*g).grid[i][j].type], (Rectangle) { (*g).grid[i][j].Centre.x, (*g).grid[i][j].Centre.y, (*g).grid[i][j].size, (*g).grid[i][j].size }, (Vector2) { (*g).grid[i][j].size / 2, (*g).grid[i][j].size / 2 }, 0, RAYWHITE);
					}
				}
				else {
					DrawTexturePro(t, r[(*g).grid[i][j].type], (Rectangle) { (*g).grid[i][j].Centre.x, (*g).grid[i][j].Centre.y, (*g).grid[i][j].size, (*g).grid[i][j].size }, (Vector2) { (*g).grid[i][j].size / 2, (*g).grid[i][j].size / 2 }, 0, RAYWHITE);

				}
			}
			//DrawTexturePro(t, r[0], (Rectangle) { (*g).grid[i][j].Centre.x, (*g).grid[i][j].Centre.y, (*g).grid[i][j].size, (*g).grid[i][j].size }, (Vector2) { (*g).grid[i][j].size / 2, (*g).grid[i][j].size / 2 }, 0, RAYWHITE);
		}
	}
	if ((*g).flash > 2) {
		(*g).flash = 0;
	}
	(*g).flash += 0.05;

}

float Get_distance(float t1, float t2) {
	float d = t2 - t1;
	return d;
};

Vector2 centre_to_tile(int x, int y, grid* g) {
	float rows;
	float collums;
	if (y < (*g).current_tile.size / 2) {
		rows = 0;
	}
	else {
		rows = round(y / (*g).current_tile.size);
		if (round(rows) - rows == 0.5) {
			rows -= 0.5;
		}

		
	}
	if (x < round((*g).current_tile.size / 2)) {
		collums = 0;
	}
	else {
		collums = x  / (*g).current_tile.size;
		

	}

	return (Vector2) { collums, rows };
};

float CalcDistance(Vector2 c1, Vector2 c2) {
	float length = c2.x - c1.x;
	float height = c2.y - c1.y;
	float d = sqrt(pow(length, 2) + pow(height, 2));
	return d;
}