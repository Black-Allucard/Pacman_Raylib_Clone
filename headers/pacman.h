#pragma once
#include "entity.h"
#include "tile_grid.h"
#include "time_trigger.h"
#define NUM_LIVES (3)
typedef struct pacman{
	Rectangle sources[3];
	Rectangle death_sources[11];
	entity entity;
	double frame;
	int max_frames;
	bool moved;
	bool cornering;
	int freeze_frames;
	int score;
	float angle;
	float factor;
	Sound sounds[3];
	int soundindex;
	bool powered;
	bool live;
	int time_powered;
	int dots_eaten;
	int dots_left;
	int time_since_dot_eaten;
}pacman;
typedef struct fruits {
	int x;
	int y;
	Rectangle fruits[8];
	int level_indices[20];
	Rectangle fruit_scores[8][3];
	Rectangle ghost_scores[4][3];
	int fruit_index;
	float frame;
	float ghost_frame;

	bool disable;
	

}fruits;

fruits init_fruits();
void draw_fruit(Texture2D t, fruits* f);
void draw_fruit_score(Texture2D t, fruits* f);
void draw_level(int level, Texture2D text, fruits* f);
void update_p(pacman* p);
void move_pacman(pacman* e, grid*g, int level);
void draw_pacman(pacman* e,Texture2D graphics);
pacman Init_pac(Rectangle s[3], Rectangle d[12], entity e, int frame, int freeze, int level, int dots_left, int score);
bool is_tile_blocking(grid* g,pacman* p, enum dir wanted_dir);
bool allow_cornering(grid* g, pacman* p, enum dir wanted_dir);
void corner(pacman* p, enum dir wanted_dir, grid* g);
float dir_to_angle(enum dir d);
void draw_ghost_score(int streak, int x, int y, Texture2D text, fruits* f);
void reset_pacman(pacman* p,grid* g);