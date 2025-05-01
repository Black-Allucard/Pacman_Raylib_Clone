#pragma once
#include "raylib.h"
#include "tile_grid.h"
#include "pacman.h"
#include <stdlib.h>
#include <time.h>

#define GHOST_EATEN_FREEZE_TICKS (60)
#define GHOST_FRIGHTENT_TICKS (60);

typedef enum states {
	SCATTER,
	CHASE,
	FRIGTHEND,
	EATEN,
	INSIDE_HOUSE,
	LEAVE_HOUSE,
	ENTER_HOUSE,

}states;

typedef enum ghost_types {
	BLINKY,
	INKY,
	PINKY,
	CLYDE,
	NUM_GHOSTS
}ghost_type;

typedef struct ghost {
	states state;
	ghost_type type;
	entity entity;
	Rectangle sources[10];
	Rectangle scores[4][3];
	int target_row;
	int target_collum;
	float frame;
	float score_frame;
	bool eat_once;
	bool flash;
	bool in_house;
	float speed;
	bool elroy1;
	bool elroy2;
}ghost;

void enter_house(ghost* g, states s);
void leave_house(ghost* g, states s);
void set_target(pacman* p, ghost* g, grid* grid, ghost* blink);
void move(ghost* g, grid* gr, pacman* p, ghost* blink, float time, states s,int level);
void bounce(ghost* g, int starty);
void update(ghost* g);
void draw_ghost(ghost* g, Texture2D text, int time);
ghost init_ghost(states state, ghost_type type, entity entity, Rectangle sources[5],int level);
void change_state(ghost* g, ghost* g2, ghost* g3, ghost* g4, states s);
void reset_ghost(ghost* g, grid* gr, states s);