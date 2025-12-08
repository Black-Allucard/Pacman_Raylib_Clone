#include "entity.h"
enum dir reverse_dir(enum dir d) {
	switch(d){
		case(UP):{
			return DOWN;
		}
		case(DOWN):{
			return UP;
		}
		case(LEFT):{
			return RIGHT;
		}
		case(RIGHT):{
			return LEFT;
		}
		default:{
			return UP;
		}
	}
}

Vector2 dir_to_vec(enum dir d) {
	switch(d){
		case(UP):{
			return (Vector2) {0,-1};
		}
		case(DOWN):{
			return (Vector2) {0,1};
		}
		case(LEFT):{
			return (Vector2) {-1,0};
		}
		case(RIGHT):{
			return (Vector2) {1,0};
		}
		default:{
			return (Vector2) {-1,0};
		}
	}
}



tile set_current_tile(entity e,grid*g) {
	int row = (centre_to_tile(e.centre.x, e.centre.y, g)).y;
	int collum = centre_to_tile(e.centre.x, e.centre.y, g).x;
	return (tile){ tile_to_centre(row,collum,(*g).current_tile.size),(*g).current_tile.size, (*g).grid[row][collum].type, row, collum };
	
}

tile get_current_tile(entity e) {
	return e.current_tile;
}

