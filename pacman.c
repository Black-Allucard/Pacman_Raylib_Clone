#pragma once
#include "pacman.h"
#include "stdio.h"
#include "math.h"

void move_pacman(pacman* e, grid* g, int level) {
    
     (*e).entity.current_tile = set_current_tile((*e).entity, (*g).current_tile.size, g);
    enum dir wanted_dir;
    tile next_tile = (*e).entity.current_tile;

    Vector2 c = centre_to_tile((*e).entity.centre.x, (*e).entity.centre.y, g);
    int row = c.y;
    int col = c.x;
    if ((*g).grid[row][col].type == dot) {
                (*g).grid[row][col].type = 0;
                (*e).score += 10;
                (*e).freeze_frames += 1;
                (*e).dots_eaten += 1;
                (*e).dots_left -= 1;
                if((*e).soundindex >= 2){
                    (*e).soundindex = 0;
                    
                }
                PlaySound((*e).sounds[(*e).soundindex]);
                (*e).soundindex += 1;
                (*e).time_since_dot_eaten = 0;

    }
    else if ((*g).grid[row][col].type == energizer) {
                (*e).time_since_dot_eaten = 0;
                (*g).grid[row][col].type = 0;
                (*e).score += 50;
                (*e).freeze_frames += 4;
                (*e).powered = true;
                (*e).dots_eaten += 1;
                (*e).dots_left -= 1;
                if (level == 1) {
                    (*e).time_powered = 360;
                }
                else if (level == 2 || level == 6 || level == 10) {
                    (*e).time_powered = 300;
                }
                else if (level == 3) {
                    (*e).time_powered = 240;
                }
                else if (level == 4 || level == 14) {
                    (*e).time_powered = 180;
                }
                else if (level == 5 || level == 7 || level == 8 || level == 11) {
                    (*e).time_powered = 120;
                }
                else if (level == 9 || level == 12 || level == 13 || level == 15 || level == 18 ) {
                    (*e).time_powered = 60;
                }
                else {
                    (*e).powered = false;
                    if (level <= 1) {
                        (*e).factor = 0.8;
                    }
                    else if (level > 1 && level < 5) {
                        (*e).factor = 0.9;
                    }
                    else if (level >=  5 && level < 21) {
                        (*e).factor = 1;
                    }
                    else if (level >= 21) {
                        (*e).factor = 0.9;
                    }
                }
     }
    else {
        (*e).time_since_dot_eaten += 1;
        if ((*e).time_powered <= 0) {
                    (*e).powered = false;
                    (*e).time_powered = 0;
                    if (level <= 1) {
                        (*e).factor = 0.8;
                    }
                    else if (level > 1 && level < 5) {
                        (*e).factor = 0.9;
                    }
                    else if (level >= 5 && level < 21) {
                        (*e).factor = 1;
                    }
                    else if (level >= 21) {
                        (*e).factor = 0.9;
                    }
        }
        else {
            if (level <= 1) {
                (*e).factor = 0.8;
            }
            else if (level > 1 && level < 5) {
                (*e).factor = 0.9;
            }
            else if (level >= 5 && level < 21) {
                (*e).factor = 1;
            }
            else if (level >= 21) {
                (*e).factor = 0.9;
            }

        }
        
     }
    

    if ((*e).freeze_frames >= 0) {
        (*e).freeze_frames -= 1;
        wanted_dir = (*e).entity.dir;
    }
 
    
    else {
        if (IsKeyDown(KEY_DOWN)) {
            if (is_tile_blocking(g, e, DOWN) == false)  {
                wanted_dir = DOWN;
            }
            else {
                wanted_dir = (*e).entity.dir;
            }
             
        }
        else if (IsKeyDown(KEY_UP)) {
            if (is_tile_blocking(g, e, UP) == false ){
                wanted_dir = UP;
            }
            else {
                wanted_dir = (*e).entity.dir;
            }
        }
        else if (IsKeyDown(KEY_RIGHT)) {
            if (is_tile_blocking(g, e, RIGHT) == false ) {
                wanted_dir = RIGHT;
            }
            else {
                wanted_dir = (*e).entity.dir;
            }
        }
        else if (IsKeyDown(KEY_LEFT)) {
            if (is_tile_blocking(g, e, LEFT) == false) {
                wanted_dir = LEFT;
            }
            else {
                wanted_dir = (*e).entity.dir;
            }
        }
        else {
            wanted_dir = (*e).entity.dir;
        }

        
        if ((*e).entity.centre.x <= -13) {
            (*e).entity.centre.x = 740;
        }
        if ((*e).entity.centre.x >= 741) {
            (*e).entity.centre.x = -12;
        }

        if ((*e).entity.centre.x >= 715 || ((*e).entity.centre.x <= 13)) {
            if (wanted_dir == RIGHT || wanted_dir == LEFT) {
                (*e).entity.centre.x += (dir_to_vec(wanted_dir).x * (*e).factor * 4.1);
                (*e).entity.centre.y += (dir_to_vec(wanted_dir).y * (*e).factor * 4.1);
                
                (*e).entity.dir = wanted_dir;
            }
            else{
                (*e).entity.centre.x += (dir_to_vec((*e).entity.dir).x * (*e).factor *4.1);
                (*e).entity.centre.y += (dir_to_vec((*e).entity.dir).y * (*e).factor *4.1);
                
   
            }
        }
        else if (is_tile_blocking(g, e, wanted_dir) == false) {
            (*e).angle = dir_to_angle(wanted_dir);
            if (allow_cornering(g, e, wanted_dir)) {
                corner(e, wanted_dir, g);

            }
            else {
                if (dir_to_vec(wanted_dir).x != 0) {
                    (*e).entity.centre.y = (*e).entity.current_tile.Centre.y;
                }
                if (dir_to_vec(wanted_dir).y != 0) {
                    (*e).entity.centre.x = (*e).entity.current_tile.Centre.x;
                }
            }
            (*e).entity.centre.x += (dir_to_vec(wanted_dir).x * (*e).factor*4.1);
            (*e).entity.centre.y += (dir_to_vec(wanted_dir).y * (*e).factor*4.1);
            (*e).entity.dir = wanted_dir;
            (*e).moved = true;
            
        }
        else {
            if (dir_to_vec(wanted_dir).x != 0) {
                (*e).entity.centre.x = (*e).entity.current_tile.Centre.x;
            }
            if (dir_to_vec(wanted_dir).y != 0) {
                (*e).entity.centre.y = (*e).entity.current_tile.Centre.y;
            }
            (*e).moved = false;
        }
        //printf("%d", (*e).score);
    }
    (*e).entity.current_tile = set_current_tile((*e).entity, (*g).current_tile.size, g);
    (*e).time_powered -= 1;
        
   
}

void draw_pacman(pacman* e, Texture2D graphics) {
   
    int r_frame = floor((*e).frame);

    if ((*e).live) {
        if ((*e).frame >= 2.8) {
            (*e).frame = 0;
        }
        
        DrawTexturePro(graphics, (*e).sources[r_frame], (Rectangle) { (*e).entity.centre.x, (*e).entity.centre.y, 42, 42 }, (Vector2) { 21, 21 }, (*e).angle, RAYWHITE);
    }
    else if(!(*e).live){
        if ((*e).frame >= 10.8) {
            (*e).frame = 0;
        }
        DrawTexturePro(graphics, (*e).death_sources[r_frame], (Rectangle) { (*e).entity.centre.x, (*e).entity.centre.y, 46, 46 }, (Vector2) { 23, 23 }, 0, RAYWHITE);
    }

    

}

pacman Init_pac(Rectangle s[3], Rectangle d[12], entity e, int frame, int freeze, int level,int dots_left,int score) {
    pacman p;
    for (int i = 0; i < 3; i++) {
        p.sources[i] = s[i];
    }
    for (int j = 0; j < 11; j++) {
        p.death_sources[j] = d[j];
    }
    p.entity = e;
    p.frame = frame;

    p.max_frames = 3;
    p.moved = false;
    p.freeze_frames = freeze;
    p.score = score;
    p.angle = dir_to_angle(e.dir);
    p.time_since_dot_eaten = 0;
    p.sounds[0] = LoadSound("./assets/dot_eaten1.wav");
    p.sounds[1] = LoadSound("./assets/dot_eaten2.wav");
    p.sounds[2] = LoadSound("./assets/pac_die.wav");

    p.soundindex = 0;
    p.powered = false;
    p.dots_eaten = 0;
    p.dots_left = dots_left;
    p.live = true;
    if (level <= 1) {
        p.factor = 0.8;
    }
    else if (level > 1 && level < 5) {
        p.factor = 0.9;
    }
    else if (level >= 5 && level < 21) {
        p.factor = 1;
    }
    else if (level >= 21) {
        p.factor = 0.9;
    }
   
    return p;
}

float dir_to_angle(enum dir d) {
    if (d == UP) {
        return -90;
    }
    if (d == DOWN) {
        return 90;
    }
    if (d == LEFT) {
        return 180;
    }
    if (d == RIGHT) {
        return 0;
    }
}

bool allow_cornering(grid* g, pacman* p, enum dir wanted_dir) {
    if ((dir_to_vec(wanted_dir).x != 0 && (dir_to_vec((*p).entity.dir).x != 0) || (dir_to_vec(wanted_dir).y != 0 && dir_to_vec((*p).entity.dir).y != 0))){
        if ((!is_tile_blocking(g, p, (*p).entity.dir)) && (!is_tile_blocking(g, p, wanted_dir))) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }

}

bool is_tile_blocking(grid* g, pacman* p, enum dir wanted_dir) {
    (*p).entity.current_tile = set_current_tile((*p).entity,(*g).current_tile.size,g);
    int next_row = round((*p).entity.current_tile.row + dir_to_vec(wanted_dir).y);
    int next_collum = round((*p).entity.current_tile.collum + dir_to_vec(wanted_dir).x);



    if ((*g).grid[next_row][next_collum].type == wall || (*g).grid[next_row][next_collum].type == ghost_house_entrance) {
        Vector2 next_centre = tile_to_centre(next_row, next_collum, (*g).current_tile.size);
        if (dir_to_vec(wanted_dir).x != 0) {
            if (abs(Get_distance((*p).entity.centre.x, next_centre.x)) <= 26) {

                return true;
            }
            else {
                return false;
            }
        }
        if (dir_to_vec(wanted_dir).y != 0) {
            if (abs(Get_distance((*p).entity.centre.y, next_centre.y)) <= 26) {
                return true;
            }
            else {
                return false;
            }
        }
    }
    else {
        return false;
    }
}

void corner(pacman* p, enum dir wanted_dir, grid* g) {
    float d_x;
    float d_y;

    d_x = Get_distance((*p).entity.current_tile.Centre.x, (*p).entity.centre.x);
    d_y = Get_distance((*p).entity.current_tile.Centre.y, (*p).entity.centre.y);
        if (dir_to_vec((*p).entity.dir).x != 0 ) {
            if (d_y > 0) {
                (*p).entity.centre.y -= 1.3 * (*p).factor;
                (*p).angle = dir_to_angle((*p).entity.dir) + (dir_to_vec(wanted_dir).x * 45);
            }

            else if (d_y < 0) {
                (*p).entity.centre.y += 1.3 * (*p).factor;
                (*p).angle = (dir_to_angle((*p).entity.dir) + (dir_to_vec(wanted_dir).x * 45))*-1;
            }
            
        }
        if (dir_to_vec((*p).entity.dir).y != 0) {

                if (d_x > 0) {
                    (*p).entity.centre.x -= 1.3 * (*p).factor;
                    (*p).angle = dir_to_angle((*p).entity.dir) + (dir_to_vec(wanted_dir).y * 45);
                }
                else if (d_x < 0) {
                    (*p).entity.centre.x += 1.3 * (*p).factor;
                    (*p).angle = (dir_to_angle((*p).entity.dir) + (dir_to_vec(wanted_dir).y * 45))*-1;
                }
        
        }
    }

fruits init_fruits() {
    fruits f;
    for (int i = 0; i < 8; i++) {
        f.fruits[i] = (Rectangle){260 + i*16,48,16,16};
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            f.fruit_scores[i][j] = (Rectangle){(226 + j * 24),(172+i*9),22,9};
        }
    }
    f.frame = 0;
    f.fruit_index = 0;
    f.x = 364;
    f.y = 533;
    f.disable = true;
    f.ghost_frame = 0;
    for (int i = 0; i < 20; i++) {
        if (i +1  == 1) {
            f.level_indices[i] = 0;
        }
        else if (i + 1 == 2) {
            f.level_indices[i] = 1;
        }
        else if (i+1 < 5) {
            f.level_indices[i] = 2;
        }
        else if (i+1 < 7) {
            f.level_indices[i] = 3;
        }
        else if (i+1 < 9) {
            f.level_indices[i] = 4;
        }
        else if (i + 1 < 11) {
            f.level_indices[i] = 5;
        }
        else if (i + 1 < 13) {
            f.level_indices[i] = 6;
        }
        else{
            f.level_indices[i] = 7;
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            f.ghost_scores[i][j] = (Rectangle){ 231 + 22 * j,135 + 9 * i ,22,9 };
        }
    }
    return f;
}

void draw_ghost_score(int streak, int x, int y, Texture2D text, fruits * f) {
    if ((*f).ghost_frame >= 3) {
        (*f).ghost_frame = 0;
    }
    int frame = (*f).ghost_frame;

    DrawTexturePro(text, (*f).ghost_scores[streak-1][frame], (Rectangle) {x, y, 66, 27 }, (Vector2) { 33, 13 }, 0, RAYWHITE);
    (*f).ghost_frame += 0.3;
};

void draw_fruit(Texture2D t,fruits* f) {
    int level_index;
    int x;
    DrawTexturePro(t,(*f).fruits[(*f).fruit_index],(Rectangle){(*f).x,(*f).y, 48, 48 }, (Vector2) { 24, 24 }, 0, RAYWHITE);

   

}

void draw_level(int level,Texture2D text, fruits * f) {
    if (level < 7) {
        for (int i = 0; i < level; i++) {
            DrawTexturePro(text, (*f).fruits[(*f).level_indices[i]], (Rectangle) { 690 - 40 * i, 910, 48, 48 }, (Vector2) { 24, 24 }, 0, RAYWHITE);
        }
    }
    else if (level > 7 && level < 19) {
        for (int i = 0; i < 7; i++) {
            DrawTexturePro(text, (*f).fruits[(*f).level_indices[level - 8 + i]], (Rectangle) { 690 - 40 * i, 910, 48, 48 }, (Vector2) { 24, 24 }, 0, RAYWHITE);
        }
    }
    else if (level >= 18) {
        for (int i = 0; i < 7; i++) {
            DrawTexturePro(text, (*f).fruits[(*f).level_indices[18]], (Rectangle) { 690 - 40 * i, 910, 48, 48 }, (Vector2) { 24, 24 }, 0, RAYWHITE);
        }
    }

}

void draw_fruit_score(Texture2D t, fruits* f) {
    int frame;
    if ((*f).frame > 3) {
        (*f).frame = 0;
    }
    frame = (*f).frame;
    DrawTexturePro(t, (*f).fruit_scores[(*f).fruit_index][frame], (Rectangle) { (*f).x, (*f).y, 72, 27 }, (Vector2) { 36, 14 }, 0, RAYWHITE);
    (*f).frame += 0.1;
};

void update_p(pacman* p){
    if(!(*p).live){
        (*p).frame += 0.11;
        }
    else if ((*p).moved) {
        if ((*p).live) {
            (*p).frame += 0.4;
        }
        
    }
}

void reset_pacman(pacman* p, grid* g) {
    (*p).entity.centre = (Vector2){ 364,689 };
    set_current_tile((*p).entity, 26, g);
    if ((*p).dots_left <= 0 && (*p).live) {
        (*p).dots_left = 244;
    }
    (*p).live = true;
    (*p).frame = 0;
    (*p).dots_eaten = 0;
    (*p).time_since_dot_eaten = 0;
    (*p).entity.dir = LEFT;
    (*p).powered = false;
    (*p).time_powered = 0;
   

}