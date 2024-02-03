#pragma once
#include "ghost.h"
#include "stdio.h"
#include "math.h"
void set_target(pacman* p, ghost* g, grid *grid , ghost*blink) {
	int row = (*p).entity.current_tile.row;
	int collum = (*p).entity.current_tile.collum;
	int row2 = (*p).entity.current_tile.row;
	int collum2 = (*p).entity.current_tile.collum;
	int dx;
	int dy;
	int d;
	if (!(*g).in_house) {
		switch ((*g).type) {
		case (PINKY): {
			if ((*g).state == SCATTER) {
				(*g).target_collum = 0;
				(*g).target_row = 0;
			}
			if ((*g).state == CHASE) {
				if ((*p).entity.dir == UP) {
					row -= 4;
					collum -= 4;
					(*g).target_collum = collum;
					(*g).target_row = row;;
				}
				else {
					row += 4 * dir_to_vec((*p).entity.dir).y;
					collum += 4 * dir_to_vec((*p).entity.dir).x;
					(*g).target_collum = collum;
					(*g).target_row = row;;
				}
			}
			if ((*g).state == EATEN) {
				(*g).target_collum = 13;
				(*g).target_row = 15;
			}
			break;
		}
		case (INKY): {
			if ((*g).state == SCATTER) {
				(*g).target_collum = 26;
				(*g).target_row = 35;
			}
			if ((*g).state == CHASE) {
				if ((*p).entity.dir == UP) {
					row2 -= 2;
					collum2 -= 2;

				}
				else {
					row2 += 2 * dir_to_vec((*p).entity.dir).y;
					collum2 += 2 * dir_to_vec((*p).entity.dir).x;

				}
				dy = Get_distance(row2, (*blink).entity.current_tile.row);
				dx = Get_distance(collum2, (*blink).entity.current_tile.collum);
				row = row2 - dy;
				collum = collum2 - dx;
				(*g).target_collum = collum;
				(*g).target_row = row;

			}
			if ((*g).state == EATEN) {
				(*g).target_collum = 13;
				(*g).target_row = 15;
			}
			break;
		}
		case (BLINKY): {
			if ((*g).state == SCATTER) {
				(*g).target_collum = 26;
				(*g).target_row = 0;
			}
			if ((*g).state == CHASE) {
				(*g).target_collum = collum;
				(*g).target_row = row;
			}
			if ((*g).state == EATEN) {
				(*g).target_collum = 13;
				(*g).target_row = 15;
			}
			break;
		}
		case (CLYDE): {
			if ((*g).state == SCATTER) {
				(*g).target_collum = 0;
				(*g).target_row = 34;
			}
			if ((*g).state == CHASE) {
				dy = abs(Get_distance(row, (*g).entity.current_tile.row));
				dx = abs(Get_distance(collum, (*g).entity.current_tile.collum));
				d = sqrt(pow(dy, 2) + pow(dx, 2));

				if (d >= 8) {
					(*g).target_collum = collum;
					(*g).target_row = row;
				}
				else if (d <= 8) {
					(*g).target_collum = 0;
					(*g).target_row = 34;
				}


			}
			if ((*g).state == EATEN) {
				(*g).target_collum = 13;
				(*g).target_row = 15;
			}
			break;
		}
		}
	}
	else {
		
	}
}

void move(ghost* g, grid* gr, pacman* p, ghost* blink, float time, states s,int level) {
	int t = time;
	srand(t);
	(*g).entity.current_tile = set_current_tile((*g).entity, (*gr).current_tile.size, gr);
	set_target(p, g, gr, blink);
	tile current_tile = (*g).entity.current_tile;
	int next_row;
	int next_collum;
	int distances[NUM_DIRS];
	int d;
	int indices[4];
	int dirs[2] = { LEFT,LEFT };
	int dir_count = 0;
	int index = 0;
	int largest_d = 10000;
	double x;
	double y;
	if (!(*g).in_house) {
		if ((*g).entity.centre.x < -13) {
			(*g).entity.centre.x = 740;

		}
		if ((*g).entity.centre.x > 741) {
			(*g).entity.centre.x = -12;

		}


		if ((*g).entity.centre.x > 299 && (*g).entity.centre.x < 455 && (*g).entity.centre.y > 391 && (*g).entity.centre.y < 507) {
			if ((*g).state == EATEN) {
				enter_house(g, s);
			}
			else if ((*g).state != EATEN) {
				leave_house(g, s);
			}
		}

		else if (((abs((*g).entity.current_tile.Centre.x - (*g).entity.centre.x)) <= 1.13) && ((abs((*g).entity.current_tile.Centre.y - (*g).entity.centre.y)) <= 1.13)
			|| ((*g).entity.centre.x > 299 && (*g).entity.centre.x < 455 && abs((*g).entity.centre.y - 377) <= 1.76 && (*g).entity.dir == UP)) {



			for (int i = 0; i < NUM_DIRS; i++) {
				if (i != reverse_dir((*g).entity.dir)) {
					next_row = (*g).entity.current_tile.row + dir_to_vec(i).y;
					next_collum = (*g).entity.current_tile.collum + dir_to_vec(i).x;
					y = abs(Get_distance(next_row, (*g).target_row));
					x = abs(Get_distance(next_collum, (*g).target_collum));
					if ((*g).entity.centre.y == 455 && (*g).entity.centre.x < 156) {
						index = (*g).entity.dir;
						break;
					}
					else if ((*g).entity.centre.y == 455 && (*g).entity.centre.x > 572) {
						index = (*g).entity.dir;
						break;
					}
					else if ((*g).entity.centre.x > 312 && (*g).entity.centre.x < 416 && (*g).entity.centre.y == 689 && (*g).state != EATEN) {
						index = (*g).entity.dir;
						break;
					}
					else if ((*g).entity.centre.x > 312 && (*g).entity.centre.x < 416 && (*g).entity.centre.y == 377 && (*g).state != EATEN && (*g).entity.dir != DOWN && (*g).entity.dir != UP) {

						index = (*g).entity.dir;

						break;
					}
					else if ((*g).state == EATEN) {

						if ((*gr).grid[next_row][next_collum].type != wall) {
							d = (pow(x, 2) + pow(y, 2));
							if (d < largest_d || (d == largest_d && i > index)) {
								largest_d = d;
								index = i;
							}
						}
					}
					else if ((*g).state == SCATTER || (*g).state == CHASE || (*g).state == FRIGTHEND) {
						if ((*gr).grid[next_row][next_collum].type != wall && (*gr).grid[next_row][next_collum].type != ghost_house_entrance) {

							d = (pow(x, 2) + pow(y, 2));
							if (d < largest_d || (d == largest_d && i >= index)) {
								largest_d = d;
								index = i;
							}
							indices[dir_count] = i;
							dir_count += 1;

						}
					}


				}

			}

			if ((*g).state == FRIGTHEND) {
				if ((*g).entity.centre.x < 156 || (*g).entity.centre.x > 598) {
					if (abs((*g).entity.centre.y - 455) <= 0.4) {

					}

					else {
						if (dir_count == 0) {
							(*g).entity.dir = index;
						}

						else if (dir_count == 1) {
							(*g).entity.dir = indices[0];
						}
						else {
							(*g).entity.dir = indices[rand() % (dir_count)];
						}
					}
				}
				else {
					if (dir_count == 0) {
						(*g).entity.dir = index;
					}
					else if (dir_count == 1) {
						(*g).entity.dir = indices[0];
					}
					else {
						(*g).entity.dir = indices[rand() % (dir_count)];
					}
				}
			}
			else {
				(*g).entity.dir = index;
			}

			if (dir_to_vec((*g).entity.dir).x != 0) {
				(*g).entity.centre.y = (*g).entity.current_tile.Centre.y;
			}

			if (dir_to_vec((*g).entity.dir).y != 0) {
				(*g).entity.centre.x = (*g).entity.current_tile.Centre.x;
			}

		}
	}
	else{
		bounce(g, 455);
	}
	
		if (((*g).entity.centre.x < 156 && (*g).entity.centre.y == 455 && (*g).state != EATEN) || ((*g).entity.centre.x > 598 && (*g).entity.centre.y == 455 && (*g).state != EATEN)) {
			if (level == 1) {
				(*g).speed = 0.4;
			}
			else if (level < 5) {
				(*g).speed = 0.50;
			}
			else {
				(*g).speed = 0.50;
			}
		}
		else if ((*g).entity.centre.y > 377 && (*g).entity.centre.y < 507 && (*g).entity.centre.x > 299 && (*g).entity.centre.x < 481 && (*g).state != EATEN) {
			(*g).speed = 0.4;
		}
		else if ((*g).state == EATEN) {
			(*g).speed = 1;
		}
		else if ((*g).state == FRIGTHEND) {
			if (level == 1) {
				(*g).speed = 0.5;
			}
			else if (level < 5) {
				(*g).speed = 0.55;
			}
			else {
				(*g).speed = 0.60;
			}
		}
		else {
			if ((*g).elroy2) {
				if (level == 1) {
					(*g).speed = 0.85;
				}
				else if (level < 2 && level <= 5) {
					(*g).speed = 0.95;
				}
				else {
					(*g).speed = 1.05;
				}
			}
			else if ((*g).elroy1) {
				if (level == 1) {
					(*g).speed = 0.8;
				}
				else if (level < 2 && level < 5) {
					(*g).speed = 0.9;
				}
				else {
					(*g).speed = 1;
				}
			}
			
			
			else {
				if (level == 1) {
					(*g).speed = 0.75;
				}
				else if (level < 5 && level <= 20) {
					(*g).speed = 0.85;
				}
				else {
					(*g).speed = 0.95;
				}
			}
		}
		(*g).entity.centre.x += dir_to_vec((*g).entity.dir).x * 4.095 * (*g).speed;
		(*g).entity.centre.y += dir_to_vec((*g).entity.dir).y * 4.095 * (*g).speed;
	
}
	
void draw_ghost(ghost* g, Texture2D text, int time) {
	int max_frames = 2;
	int frame = floor((*g).frame);
	Vector2 Centre = tile_to_centre((*g).target_row, (*g).target_collum, 26);
	int index = (*g).entity.dir;
	Rectangle rect;
	if ((time % 10) == 0 && time <= 100 && (*g).state == FRIGTHEND) {
		if ((*g).flash == true) {
			(*g).flash = false;
		}
		else if ((*g).flash == false) {
			(*g).flash = true;
		}
		
	}
	else if((*g).state != FRIGTHEND){
		(*g).flash = false;
	}
	
	if ((*g).frame >= max_frames) {
		(*g).frame = 0;
		frame = floor((*g).frame);
	}
	if ((*g).state != FRIGTHEND && (*g).state != EATEN) {
		rect = (*g).sources[(*g).entity.dir];

	}
	else if ((*g).state == FRIGTHEND) {
		if ((*g).flash) {
			rect = (*g).sources[5];
		}
		else {
			rect = (*g).sources[4];
		}
	}
	else if ((*g).state == EATEN) {
		rect = (*g).sources[6+index];
	}
	if((*g).state == EATEN){
		DrawTexturePro(text, rect, (Rectangle) { (*g).entity.centre.x, (*g).entity.centre.y, 48, 48 }, (Vector2) { 24, 24 }, 0, RAYWHITE) ;
	}
	else {
		DrawTexturePro(text, (Rectangle) { (rect.x + ((rect.width / 2) * (frame))), rect.y, (rect.width / 2), rect.height }, (Rectangle) { (*g).entity.centre.x, (*g).entity.centre.y, 48, 48 }, (Vector2) { 24, 24 }, 0, RAYWHITE);
	}
	
	/*switch ((*g).type) {
	case BLINKY: {DrawRectanglePro( (Rectangle) { Centre.x, Centre.y, 26, 26 }, (Vector2){ 13,13} ,0,RED );
		break;
	}
	case INKY: {DrawRectanglePro((Rectangle) { Centre.x, Centre.y, 26, 26 }, (Vector2) { 13, 13 }, 0, DARKBLUE);
		break;
	}
	case PINKY: {DrawRectanglePro((Rectangle) { Centre.x, Centre.y, 26, 26 }, (Vector2) { 13, 13 }, 0, PINK);
		break;
    }
	case CLYDE: {DrawRectanglePro((Rectangle) { Centre.x, Centre.y, 26, 26 }, (Vector2) { 13, 13 }, 0, ORANGE);
		break;
		}

	}*/
	
}

ghost init_ghost(states state, ghost_type type, entity entity, Rectangle sources[5], int level) {
	ghost g;
	for (int i = 0; i < 10; i++) {
		g.sources[i] = sources[i];
	}
	g.entity = entity;
	g.type = type;
	g.state = state;
	g.frame = 0;
	g.flash = false;
	g.score_frame = 0;
	g.elroy1 = false;
	g.elroy2 = false;
	if(level = 1){
		g.speed = 0.75;
	}
	else if (level < 5 && level <= 20) {
		g.speed = 0.85;
	}
	else{ 
	    g.speed = 0.95;
	}
	if (g.type != BLINKY) {
		g.in_house = true;
	}
	else {
		g.in_house = false;
	}
	
	return g;
}
 
void change_state(ghost* g, ghost* g2, ghost* g3, ghost* g4, states s) {
	struct ghost* gs[4] = { g,g2,g3,g4 };
	for (int i = 0; i < 4; i++) {

		//change state

		if ((*gs[i]).state != EATEN) {
			if (s == FRIGTHEND) {
				if ((*gs[i]).eat_once == false) {
					
					(*gs[i]).state = s;
				}
				else {
					continue;
				}
			}
			else {
				if (s != (*gs[i]).state && (*gs[i]).state != FRIGTHEND && !(*gs[i]).elroy2 && !(*gs[i]).elroy1 && s != FRIGTHEND) {
					(*gs[i]).entity.dir = reverse_dir((*gs[i]).entity.dir);
				}
				if (!(*gs[i]).elroy2 && !(*gs[i]).elroy1) {
					(*gs[i]).state = s;
				}
				else {
					(*gs[i]).state = CHASE;
				}
			}
		}
		else {
			continue;
		}

		//change direction
	}
	

}

void bounce(ghost* g,int starty) {
	if (dir_to_vec((*g).entity.dir).x != 0) {
		if ((*g).type == PINKY){
			(*g).entity.dir = DOWN;
		}
		else {
			(*g).entity.dir = UP;
		}
	}
	if (abs((*g).entity.centre.y - starty) > 10) {
		if ((*g).entity.centre.y < starty) {
			(*g).entity.dir = DOWN;
		
		}
		if ((*g).entity.centre.y > starty) {
			(*g).entity.dir = UP;

		}
	}
}

void leave_house(ghost* g, states s) {
	
	srand(0);
	Vector2 Centre = { 364,351 };
	int dirs[2] = { RIGHT,LEFT };

	if (abs((*g).entity.centre.x - 364) <= 2.3) {
		if ((*g).entity.centre.y > 391) {
			(*g).entity.dir = UP;
		}
		else {
			(*g).entity.dir = LEFT;
		}

	}
	else if((*g).entity.centre.y > 417){
		if ((*g).entity.centre.x > 364) {
			(*g).entity.dir = LEFT;
		}
		if ((*g).entity.centre.x < 364) {
			(*g).entity.dir = RIGHT;
		}
	}
}

void enter_house(ghost* g, states s){
	Vector2 centre;
	switch ((*g).type) {
	case INKY: {
		centre = (Vector2){ 312, 455 };
		break;
	}
	case BLINKY: {
		centre = (Vector2){ 364, 455 };
		break;
	}
	case PINKY: {
		centre = (Vector2){ 364, 455 };
		break;
	}
	case CLYDE: {
		centre = (Vector2){ 416, 455 };
		break;
	}
	}
	if (abs((*g).entity.centre.x - centre.x) <= 4 && abs((*g).entity.centre.y - centre.y) <= 4) {
		if ((*g).type == BLINKY) {
			
		}
		else if((*g).type != BLINKY){
			(*g).in_house = true;
		}
		(*g).state = s;
	}
	else if ((*g).entity.centre.y < centre.y && (*g).entity.centre.y > 417) {
		(*g).entity.dir = DOWN;
	}
	else if ((*g).entity.centre.x > centre.x && (*g).entity.centre.y > 417) {
		(*g).entity.dir = LEFT;
	}
	else if ((*g).entity.centre.x < centre.x && (*g).entity.centre.y > 417) {
		(*g).entity.dir = RIGHT;
	}
	

}

void update(ghost* g) {
	if ((*g).state == FRIGTHEND) {
		(*g).frame += 0.20;
	}
	else {
		(*g).frame += 0.10;
	}
}

void reset_ghost(ghost* g, grid* gr, states s) {
	switch ((*g).type) {
	case (INKY): {
		(*g).entity.centre = (Vector2){ 312, 455 };
		(*g).in_house = true;
		(*g).frame = 0;
		(*g).entity.dir = DOWN;
		set_current_tile((*g).entity, 26, gr);
		(*g).state = s;
		break;
		
	}
	case (PINKY): {
		(*g).entity.centre = (Vector2){ 364, 455 };
		(*g).in_house = true;
		(*g).frame = 0;
		(*g).entity.dir = UP;
		set_current_tile((*g).entity, 26, gr);
		(*g).state = s;
		break;

	}
	case (BLINKY): {
		(*g).entity.centre = (Vector2){ 365, 376 };
		(*g).frame = 0;
		(*g).entity.dir = LEFT;
		set_current_tile((*g).entity, 26, gr);
		(*g).state = s;
		break;

	}
	case (CLYDE): {
		(*g).entity.centre = (Vector2){ 412, 455 };
		(*g).in_house = true;
		(*g).frame = 0;
		(*g).entity.dir = DOWN;
		set_current_tile((*g).entity, 26, gr);
		(*g).state = s;
		break;

	}
	}
}