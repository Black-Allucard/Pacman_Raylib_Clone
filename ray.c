// includes
#include "raylib.h"
#include "tile_grid.h"
#include "pacman.h"
#include "ghost.h"
#include "Time_trigger.h"
#include "stdio.h"
// definities
#define Window_height (936)
#define Window_width (728)
#define name ("pacman")
#define Tile_Size (26)
#define DOT_COUNT (244)

Color ligth_blue = { 19,225,234,255 };
Color I = { 27,169,197,255 };
Color B = { 172,35,35,255 };
Color P = { 255,121,230,255 };
Color C = { 255,165,0,255 };
Color peach = { 255,139,126,255 };
Color light_pink = { 251,128,228,255 };

const int a[36][28] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
						{1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1},
						{1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
						{1,5,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,5,1},
						{1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
						{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
						{1,2,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,2,1},
						{1,2,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,2,1},
						{1,2,2,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,2,2,1},
						{1,1,1,1,1,1,2,1,1,1,1,1,0,1,1,0,1,1,1,1,1,2,1,1,1,1,1,1},
						{0,0,0,0,0,1,2,1,1,1,1,1,0,1,1,0,1,1,1,1,1,2,1,0,0,0,0,0},
						{0,0,0,0,0,1,2,1,1,0,0,0,0,0,0,0,0,0,0,1,1,2,1,0,0,0,0,0},
						{0,0,0,0,0,1,2,1,1,0,1,1,1,4,4,1,1,1,0,1,1,2,1,0,0,0,0,0},
						{1,1,1,1,1,1,2,1,1,0,1,0,0,0,0,0,0,1,0,1,1,2,1,1,1,1,1,1},
						{3,3,3,3,3,3,2,0,0,0,1,0,0,0,0,0,0,1,0,0,0,2,3,3,3,3,3,3},
						{1,1,1,1,1,1,2,1,1,0,1,0,0,0,0,0,0,1,0,1,1,2,1,1,1,1,1,1},
						{0,0,0,0,0,1,2,1,1,0,1,1,1,1,1,1,1,1,0,1,1,2,1,0,0,0,0,0},
						{0,0,0,0,0,1,2,1,1,0,0,0,0,0,0,0,0,0,0,1,1,2,1,0,0,0,0,0},
						{0,0,0,0,0,1,2,1,1,0,1,1,1,1,1,1,1,1,0,1,1,2,1,0,0,0,0,0},
						{1,1,1,1,1,1,2,1,1,0,1,1,1,1,1,1,1,1,0,1,1,2,1,1,1,1,1,1},
						{1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1},
						{1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
						{1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
						{1,5,2,2,1,1,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,1,1,2,2,5,1},
						{1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1},
						{1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1},
						{1,2,2,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,2,2,1},
						{1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1},
						{1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1},
						{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
						{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
						{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };
struct game {
	int tick;
	trigger round_started;
	trigger enter_fright;
	trigger fruit_appeared;
	bool in_prelude;
	bool in_round;
	bool game_over;
	bool round_won;
	int lives;
	int current_level;
	pacman player;
	pacman* pac;
	grid g;
	grid* gr;
	ghost ghosts[NUM_GHOSTS];
	ghost* gs[NUM_GHOSTS];
	fruits f;
	int max_sounds;
	Sound sounds[3];
	int high_score;
	Texture2D graphics;
};

// main loop
int main() {
    // init van kleuren, ghosts, pacman..
	InitWindow(Window_width ,Window_height,name);
	InitAudioDevice();
	// main game loop
	

	int game_freeze_frames = 0;
	int high_score = 0;
	int loop_tick = 0;
	int tick = 0;
	int level = 1;
	int lives = 4;
	int pause = 0;
	int eaten_ghost = 0;
	int streak = 0;
	int dot_trigger;
	int time_in_round = 0;
	int dot_counter = 0;

	int inky_dot_limit;
	int pinky_dot_limit;
	int clyde_dot_limit;
	int elroy1_trigger;
	int elroy2_trigger;


	bool beat_highscore = false;
	bool in_prelude = true;
	bool in_prelude2 = true;
	bool enable_global_counter = false;
	bool eat_fruit = true;
	bool in_round = false;
	bool flash = false;
	bool one_up = false;

	Texture2D graphics = LoadTexture("./assets/Sprites.png");

	states global_state = SCATTER;

	Rectangle sources_grid[NUMTYPES] = { (Rectangle) { 624,232,16,16 },(Rectangle) { 648,240,8,8 } ,(Rectangle) { 664,240,8,8 } ,(Rectangle) { 640,240,8,8 } ,(Rectangle) { 656,240,8,8 },(Rectangle) { 672,240,8,8 } };
	Rectangle sources_pacman[3] = { (Rectangle) { 261,1,13,13 },(Rectangle) { 245,1,13,13 },(Rectangle) { 229,1,13,13 } };
	Rectangle death_sources_pacman[11] = { (Rectangle) { 276,1,15,15 },(Rectangle) { 292,1,15,15 },(Rectangle) { 308,1,15,15 },(Rectangle) { 324,1,15,15 },(Rectangle) { 340,1,15,15 },(Rectangle) { 356,1,15,15 },(Rectangle) { 372,1,15,15 },(Rectangle) { 388,1,15,15 },(Rectangle) { 404,1,15,15 },(Rectangle) { 420,1,15,15 },(Rectangle) { 435,1,17,17 } };
	Rectangle sources_blinky[10] = { (Rectangle) { 228,64,32,16 },(Rectangle) { 324,64,32,16 } ,(Rectangle) { 260,64,32,16 } ,(Rectangle) { 292,64,32,16 } ,(Rectangle) { 356,64,32,16}, (Rectangle) { 388,64,32,16 },(Rectangle) { 356,80,16,16 },(Rectangle) { 402,80,16,16 },(Rectangle) { 372,80,16,16 },(Rectangle) { 386,80,16,16 } };
	Rectangle sources_pinky[10] = { (Rectangle) { 228,80,32,16 },(Rectangle) { 324,80,32,16 } ,(Rectangle) { 260,80,32,16 } ,(Rectangle) { 292,80,32,16 } ,(Rectangle) { 356,64,32,16 }, (Rectangle) { 388,64,32,16 },(Rectangle) { 356,80,16,16 },(Rectangle) { 402,80,16,16 },(Rectangle) { 372,80,16,16 },(Rectangle) { 386,80,16,16 } };
	Rectangle sources_inky[10] = { (Rectangle) { 228,96,32,16 },(Rectangle) { 324,96,32,16 } ,(Rectangle) { 260,96,32,16 } ,(Rectangle) { 292,96,32,16 } ,(Rectangle) { 356,64,32,16 } , (Rectangle) { 388,64,32,16 },(Rectangle) { 356,80,16,16 },(Rectangle) { 402,80,16,16 },(Rectangle) { 372,80,16,16 },(Rectangle) { 386,80,16,16 } };
	Rectangle sources_clyde[10] = { (Rectangle) { 228,112,32,16 },(Rectangle) { 324,112,32,16 } ,(Rectangle) { 260,112,32,16 } ,(Rectangle) { 292,112,32,16 } ,(Rectangle) { 356,64,32,16 }, (Rectangle) { 388,64,32,16 },(Rectangle) { 356,80,16,16 },(Rectangle) { 402,80,16,16 },(Rectangle) { 372,80,16,16 },(Rectangle) { 386,80,16,16 } };
	Rectangle lives_rect = (Rectangle){ 357,17,13,13 };

	grid g = Init_grid(Tile_Size, a);
	grid* ptr = &g;

	pacman p = Init_pac(sources_pacman, death_sources_pacman, (entity) { (Vector2) { 364, 689 }, (tile) { (Vector2) { 39, 117 }, Tile_Size, empty, 26, 15 }, LEFT }, 0, 0, level, 244, 0);
	pacman* pac = &p;


	fruits fruit = init_fruits();
	fruit.fruit_index = 0;
	fruits* fruits = &fruit;

	ghost ink = init_ghost(global_state, INKY, (entity) { (Vector2) { 312, 455 }, g.grid[9][14], UP }, sources_inky, level);
	ghost pink = init_ghost(global_state, PINKY, (entity) { (Vector2) { 364, 455 }, g.grid[9][14], DOWN }, sources_pinky, level);
	ghost blink = init_ghost(global_state, BLINKY, (entity) { (Vector2) { 365, 376 }, g.grid[9][14], LEFT }, sources_blinky, level);
	ghost clyd = init_ghost(global_state, CLYDE, (entity) { (Vector2) { 412, 455 }, g.grid[9][14], UP }, sources_clyde, level);
	ink.in_house = true;
	pink.in_house = true;
	clyd.in_house = true;
	ghost* inky = &ink;
	ghost* blinky = &blink;
	ghost* pinky = &pink;
	ghost* clyde = &clyd;

	Sound scared = LoadSound("./assets/Ghost_Scared.wav");
	Sound siren = LoadSound("./assets/Ghost_siren_1.wav");
	Sound siren2 = LoadSound("./assets/Ghost_siren_2.wav");
	Sound eaten = LoadSound("./assets/Ghost_eaten.wav");
	Sound fruit_eat = LoadSound("./assets/Fruit_eaten.wav");
	Sound ghost_eat = LoadSound("./assets/Ghost_eat.wav");
	Sound ding_ding = LoadSound("./assets/One_up.wav");
	Sound start_up = LoadSound("./assets/pacman_start.wav");
	Sound pac_die = LoadSound("./assets/Pac_die.wav");
	Sound s;
	Sound transition = LoadSound("./assets/prelude_transition.wav");

	Font font = LoadFont("./assets/font.ttf");
	Font logo_font = LoadFont("./assets/namco_.ttf");


	trigger enter_fright;
	trigger* ghost_eaten;
	trigger game_started;
	trigger round_ended = disable_trigger();
	trigger round_started = disable_trigger();
	trigger pacman_died = disable_trigger();
	trigger game_over = disable_trigger();
	trigger round = disable_trigger();
	trigger fruit_appeared = disable_trigger();
	trigger fruit_eaten = disable_trigger();
	trigger state_trigger = disable_trigger();




		
	
	SetTargetFPS(60);
	while (true) {
		if (WindowShouldClose()) {
			break;

		}
		if (enable_global_counter && (*clyde).in_house && (*pac).dots_eaten == 32) {
			enable_global_counter = false;
		}
		if (in_prelude) {

			if (IsKeyPressed(KEY_SPACE)) {
				in_prelude = false;
				in_prelude2 = true;
				flash = false;
				PlaySound(transition);
				
			}

			BeginDrawing();

			ClearBackground(BLACK);
			DrawTextEx(font, "HIGH SCORE", (Vector2) { 240, 0 }, 36, 0, YELLOW);
			DrawTextEx(font, TextFormat("%02i", (*pac).score), (Vector2) { 100, 30 }, 36, 1, RAYWHITE);
			DrawTextEx(font, TextFormat("%02i", high_score), (Vector2) { 400, 30 }, 36, 1, RAYWHITE);
			DrawTextEx(font, "credit 0", (Vector2) { 50, 888 }, 33, 1, RAYWHITE);
			DrawTextEx(font, "character / nickname", (Vector2) { 150, 150 }, 33, 1, RAYWHITE);
			DrawTextEx(font, "1UP", (Vector2) { 50 , 0 }, 36, 1, RAYWHITE);
			DrawTextEx(font, "2UP", (Vector2) { 575, 0 }, 36, 1, RAYWHITE);
			if (loop_tick >= 120) {
				DrawTexturePro(graphics, (Rectangle) { 228, 64, 16, 16 }, (Rectangle) { 120, 220, 52, 52 }, (Vector2) { 26, 26 }, 0, RAYWHITE);
			
			}
			if (loop_tick >= 170) {
				DrawTextEx(font, "-shadow", (Vector2) { 200, 205 }, 30, 0, B);

			}
			if (loop_tick >= 220) {
				DrawTextEx(font, "\"blinky\"", (Vector2) { 450, 205 }, 30, 0, B);

			}
			if (loop_tick >= 340) {
				DrawTexturePro(graphics, (Rectangle) { 228, 80, 16, 16 }, (Rectangle) { 120, 300, 52, 52 }, (Vector2) { 26, 26 }, 0, RAYWHITE);

			}
			if (loop_tick >= 390) {
				DrawTextEx(font, "-speedy", (Vector2) { 200, 285 }, 30, 0, P);

			}
			if (loop_tick >= 440) {
				DrawTextEx(font, "\"pinky\"", (Vector2) { 450, 285 }, 30, 0, P);

			}
			if (loop_tick >= 560) {
				DrawTexturePro(graphics, (Rectangle) { 228, 96, 16, 16 }, (Rectangle) { 120, 380, 52, 52 }, (Vector2) { 26, 26 }, 0, RAYWHITE);

			}
			if (loop_tick >= 610) {
				DrawTextEx(font, "-bashful", (Vector2) { 200, 365 }, 30, 0, I);

			}
			if (loop_tick >= 660) {
				DrawTextEx(font, "\"inky\"", (Vector2) { 450, 365 }, 30, 0, I);

			}
			if (loop_tick >= 780) {
				DrawTexturePro(graphics, (Rectangle) { 228, 112, 16, 16 }, (Rectangle) { 120, 460, 52, 52 }, (Vector2) { 26, 26 }, 0, RAYWHITE);

			}
			if (loop_tick >= 830) {
				DrawTextEx(font, "-pokey", (Vector2) { 200, 445 }, 30, 0, C);

			}
			if (loop_tick >= 880) {
				DrawTextEx(font, "\"clyde\"", (Vector2) { 450, 445 }, 30, 0, C);

			}
			if (loop_tick >= 940) {
				DrawTextEx(font, "10", (Vector2) { 300, 600 }, 25, 0, RAYWHITE);
				DrawTextEx(font, "PTS", (Vector2) { 350, 605 }, 20, 0, RAYWHITE);
				DrawTextEx(font, "50", (Vector2) { 300, 650 }, 25, 0, RAYWHITE);
				DrawTextEx(font, "PTS", (Vector2) { 350, 655 }, 20, 0, RAYWHITE);
				DrawTextEx(logo_font, "namco", (Vector2) { 290, 750 }, 40, 3, PINK);

			}
			if (loop_tick >= 980) {
				if (loop_tick % 15 == 0 && flash == true) {
					flash = false;
				}
				else if (loop_tick % 15 == 0 && flash == false) {
					flash = true;
				}
				DrawTexturePro(graphics, sources_grid[2], (Rectangle) { 270,615 , 24, 24 }, (Vector2) { 12, 12 }, 0, RAYWHITE);
				if (flash) {
					DrawTexturePro(graphics, sources_grid[5], (Rectangle) { 270, 665, 24, 24 }, (Vector2) { 12, 12 }, 0, RAYWHITE);
				}
			}
			if (loop_tick >= 1280) {
			//	loop_tick = 0;
			}
			
			EndDrawing();
			loop_tick += 1;
		}
		else if (in_prelude2) {
			if (IsKeyPressed(KEY_SPACE)) {
				in_prelude2 = false;
				flash = false;
				game_started.trigger = tick;
			}
			BeginDrawing();
			ClearBackground(BLACK);
			DrawTextEx(font, "HIGH SCORE", (Vector2) { 240, 0 }, 36, 0, YELLOW);
			DrawTextEx(font, TextFormat("%02i", (*pac).score), (Vector2) { 100, 30 }, 36, 1, RAYWHITE);
			DrawTextEx(font, TextFormat("%02i", high_score), (Vector2) { 400, 30 }, 36, 1, RAYWHITE);
			DrawTextEx(font, "1 player only", (Vector2) { 200, 500 }, 30, 0, ligth_blue);
			DrawTextEx(font, "push space bar to start", (Vector2) { 100, 410 }, 30, 0, ORANGE);
			DrawTextEx(font, "bonus pac-man for 10000 PTS", (Vector2) { 50, 560 }, 30, 0, peach);
			draw_level(level, graphics, fruits);
			DrawTextEx(font, "credit 1", (Vector2) { 50, 888 }, 33, 1, RAYWHITE);
			EndDrawing();
		}

		else if (since(round_ended, tick) >= 240 && round_ended.trigger > -1) {
			round_ended = disable_trigger();
			state_trigger = disable_trigger();
			global_state = SCATTER;
			if (!(*pac).live) {
				lives -= 1;
			}
			else {
				level += 1;
			}
			
			if ((*pac).live) {
				reset_grid(ptr, a);
			}
			reset_pacman(pac, ptr,global_state);
			reset_ghost(pinky, ptr, global_state);
			reset_ghost(inky, ptr, global_state);
			reset_ghost(blinky, ptr, global_state);
			reset_ghost(clyde, ptr, global_state);
			enable_global_counter = true;
			(*fruits).disable = true;
			time_in_round = 0;
			round_started.trigger = tick;
			if (lives <= 0) {
				game_over.trigger = tick;
			}
		}
		
		
		else if (lives <= 0) {
			game_over.trigger = tick;

			
			tick = 0;
			level = 1;
			lives = 4;
			pause = 0;
			eaten_ghost = 0;
			streak = 0;
			p.dots_eaten = 0;
			reset_grid(ptr, a);
			p = Init_pac(sources_pacman, death_sources_pacman, (entity) { (Vector2) { 364, 689 }, (tile) { (Vector2) { 39, 117 }, Tile_Size, empty, 26, 15 }, LEFT }, 0, 0, level,244,0);
			
			ink = init_ghost(global_state, INKY, (entity) { (Vector2) { 312, 455 }, g.grid[9][14], UP }, sources_inky, level);
			pink = init_ghost(global_state, PINKY, (entity) { (Vector2) { 364, 455 }, g.grid[9][14], DOWN }, sources_pinky, level);
			blink = init_ghost(global_state, BLINKY, (entity) { (Vector2) { 365, 376 }, g.grid[9][14], LEFT }, sources_blinky, level);
			clyd = init_ghost(global_state, CLYDE, (entity) { (Vector2) { 412, 455 }, g.grid[9][14], UP }, sources_clyde, level);
			game_started = disable_trigger();
	        round_ended = disable_trigger();
			round_started = disable_trigger();
			pacman_died = disable_trigger();
			game_over = disable_trigger();
			state_trigger = disable_trigger();
			in_prelude = true;
			time_in_round = 0;

		}

		
		else {



			if (since(game_started, tick) >= 270 && round_started.trigger < 0 && game_started.trigger > -1) {
				in_round = true;
				round_started.trigger = tick;


			}
			else if (since(round_started, tick) >= 80 && round_started.trigger > -1) {
				in_round = true;
				if (state_trigger.trigger < 0) {
					state_trigger = set_trigger(tick);
				}
				


			}
			
			if (in_round) {
				if (level == 1 && state_trigger.trigger >= 0) {
					switch (since(state_trigger, tick)) {
					case(420): {
						global_state = CHASE;

						break;
					}
					case(1620): {
						global_state = SCATTER;

						break;
					}
					case(2080): {
						global_state = CHASE;

						break;
					}
					case(3280): {
						global_state = SCATTER;

						break;
					}
					case(3580): {
						global_state = CHASE;

						break;
					}
					case(4780): {
						global_state = SCATTER;

						break;
					}
					case(5080): {
						global_state = CHASE;
						break;
					}
					}

				}
				
				if (level > 1 && level < 5 && state_trigger.trigger >= 0) {
					switch (since(state_trigger, tick)) {
						
						case(420): {
							global_state = CHASE;

							break;
						}
						case(1620): {
							global_state = SCATTER;

							break;
						}
						case(2080): {
							global_state = CHASE;

							break;
						}
						case(3280): {
							global_state = SCATTER;

							break;
						}
						case(3580): {
							global_state = CHASE;

							break;
						}
						case(65560): {
							global_state = SCATTER;

							break;
						}
						case(65561): {
							global_state = CHASE;
							break;
						}
						
					}
				}
				if(state_trigger.trigger >= 0 && level >= 5){
					switch (since(state_trigger, tick)) {
						
						case(300): {
							global_state = CHASE;

							break;
						}
						case(1500): {
							global_state = SCATTER;

							break;
						}
						case(1800): {
							global_state = CHASE;

							break;
						}
						case(3000): {
							global_state = SCATTER;

							break;
						}
						case(3300): {
							global_state = CHASE;

							break;
						}
						case(65520): {
							global_state = SCATTER;

							break;
						}
						case(65521): {
							global_state = CHASE;
							break;
						}
						
					}
				}
				
			}
			
			
			if (level == 1) {
				elroy1_trigger = 20;
				elroy2_trigger = elroy1_trigger / 2;
			}
			else if (level == 2) {
				elroy1_trigger = 30;
				elroy2_trigger = elroy1_trigger / 2;
			}
			else if (level < 6) {
				elroy1_trigger = 40;
				elroy2_trigger = elroy1_trigger / 2;
			}
			else if (level < 9) {
				elroy1_trigger = 50;
				elroy2_trigger = elroy1_trigger / 2;
			}
			else if (level < 12) {
				elroy1_trigger = 60;
				elroy2_trigger = elroy1_trigger / 2;
			}
			else if (level < 15) {
				elroy1_trigger = 80;
				elroy2_trigger = elroy1_trigger / 2;
			}
			else if (level < 19) {
				elroy1_trigger = 100;
				elroy2_trigger = elroy1_trigger / 2;
			}
			else {
				elroy1_trigger = 120;
				elroy2_trigger = elroy1_trigger / 2;
			}
			
		


			if (level < 5) {
				dot_trigger = 240;
			}
			else {
				dot_trigger = 180;
			}

			switch (level) {
			case(1): {
				inky_dot_limit = 30;
				pinky_dot_limit = 0;
				clyde_dot_limit = 50;
				break;

			}
			case(2): {
				inky_dot_limit = 0;
				pinky_dot_limit = 0;
				clyde_dot_limit = 30;
				break;
			}
			default: {
				inky_dot_limit = 0;
				pinky_dot_limit = 0;
				clyde_dot_limit = 0;
				break;
			}
			}

			if (enable_global_counter && in_round) {
				
				if (((*pac).dots_eaten == 0 && (*pinky).in_house) || ((*pac).time_since_dot_eaten > dot_trigger && (*pinky).in_house)) {
					(*pinky).in_house = false;
					(*pac).time_since_dot_eaten = 0;
				}
				else if (((*pac).dots_eaten == 17 && (*inky).in_house) || ((*pac).time_since_dot_eaten > dot_trigger && (*inky).in_house)) {
					(*inky).in_house = false;
					(*pac).time_since_dot_eaten = 0;
				}
				else if (((*pac).dots_eaten == 32 && (*clyde).in_house) || ((*pac).time_since_dot_eaten > dot_trigger && (*clyde).in_house)) {
					(*clyde).in_house = false;
					(*pac).time_since_dot_eaten = 0;

				}
			}
			else if(in_round){
				
				if (((*pac).dots_eaten > pinky_dot_limit && (*pinky).in_house) || ((*pac).time_since_dot_eaten > dot_trigger && (*pinky).in_house)) {
					(*pinky).in_house = false;
					(*pac).time_since_dot_eaten = 0;
				}
				else if (((*pac).dots_eaten > inky_dot_limit && (*inky).in_house) || ((*pac).time_since_dot_eaten > dot_trigger && (*inky).in_house)) {
					(*inky).in_house = false;
					(*pac).time_since_dot_eaten = 0;
				}
				else if (((*pac).dots_eaten > clyde_dot_limit && (*clyde).in_house) || ((*pac).time_since_dot_eaten > dot_trigger && (*clyde).in_house)) {
					(*clyde).in_house = false;
					(*pac).time_since_dot_eaten = 0;

				}
			}

			if ((*pac).dots_eaten == 70 || (*pac).dots_eaten == 170) {
				fruit_appeared.trigger = tick;
				eat_fruit = false;
				fruit_eaten.trigger = -1;
				(*fruits).disable = false;
			}
			if (since(fruit_appeared, tick) >= 600 && fruit_appeared.trigger > 0) {
				fruit_eaten.trigger = -1;
				eat_fruit = true;
				(*fruits).disable = true;
			}
			// prelude : alleen gebruikt in het begin van het spel

			// ready pause : gebruikt wanneer een nieux level bereikt is of pacman sterft

			// main game : het spel dat de speler speelt

			   // update
			if (level < 21) {
				(*fruits).fruit_index = (*fruits).level_indices[level - 1];
			}
			else {
				(*fruits).fruit_index = (*fruits).level_indices[19];
			}

			struct ghost* gs[4] = { inky,pinky,blinky,clyde };
			if (!(*pinky).in_house && !(*inky).in_house && !(*clyde).in_house) {
				if ((*pac).dots_left <= elroy2_trigger) {
					(*blinky).elroy2 = true;
				}
				else if ((*pac).dots_left <= elroy1_trigger) {
					(*blinky).elroy1 = true;

				}
			}
			else {
				(*blinky).elroy1 = false;
				(*blinky).elroy2 = false;
			}

			




			if ((*pac).powered) {

				s = scared;
				change_state(inky, pinky, blinky, clyde, FRIGTHEND);

			}
			else {
				(*inky).eat_once = false;
				(*blinky).eat_once = false;
				(*pinky).eat_once = false;
				(*clyde).eat_once = false;
				change_state(inky, pinky, blinky, clyde, global_state);

				s = siren;

			}

			if (pause <= 0 && in_round && round_ended.trigger < 0) {
				move_pacman(pac, ptr, level);
				move(inky, ptr, pac, blinky, GetTime(), global_state, level);
				move(blinky, ptr, pac, blinky, GetTime(), global_state, level);
				move(pinky, ptr, pac, blinky, GetTime(), global_state, level);
				move(clyde, ptr, pac, blinky, GetTime(), global_state, level);
			}
			else {
				pause -= 1;
			}


			Vector2 c = centre_to_tile((*pac).entity.centre.x, (*pac).entity.centre.y, ptr);
			int row = c.y;
			int col = c.x;
			if (pause <= 0 && in_round) {


				for (int i = 0; i < 4; i++) {
					if ((*gs[i]).state == EATEN) {
						(*gs[i]).eat_once = true;

						continue;
					}
					else if ((*ptr).grid[row][col].type == energizer) {
						if ((*gs[i]).state != FRIGTHEND) {
							(*gs[i]).entity.dir = reverse_dir((*gs[i]).entity.dir);
						}
						streak = 0;
						if ((*gs[i]).eat_once == true && (*gs[i]).state != EATEN) {
							(*gs[i]).eat_once = false;
						}
					}


					else if ((*gs[i]).entity.current_tile.row == row && (*gs[i]).entity.current_tile.collum == col && (*gs[i]).state == FRIGTHEND) {
						(*gs[i]).state = EATEN;
						(*gs[i]).eat_once = true;
						streak += 1;
						ghost_eaten = i;
						PlaySound(ghost_eat);
						pause = 120;
						(*pac).score += 200 * pow(2, (streak - 1));

					}
					else if ((*gs[i]).entity.current_tile.row == row && (*gs[i]).entity.current_tile.collum == col && (*gs[i]).state != FRIGTHEND && round_ended.trigger < 0) {
						round_ended.trigger = tick;

					}

				}
			}
			if ((*pac).dots_left <= 0 && in_round && round_ended.trigger < 0) {
				round_ended.trigger = tick;
			}


		


			if (abs((*pac).entity.centre.x - (*fruits).x) <= 5 && abs((*pac).entity.centre.y - (*fruits).y) <= 5) {
				if (!(*fruits).disable) {
					fruit_eaten.trigger = tick;
					eat_fruit = true;
					PlaySound(fruit_eat);
					switch ((*fruits).fruit_index) {
					case (0): {
						(*pac).score += 100;
						break;
					}
					case (1): {
						(*pac).score += 300;
						break;
					}
					case (2): {
						(*pac).score += 500;
						break;
					}
					case (3): {
						(*pac).score += 700;
						break;
					}
					case (4): {
						(*pac).score += 1000;
						break;
					}
					case (5): {
						(*pac).score += 2000;
						break;
					}
					case (6): {
						(*pac).score += 3000;
						break;
					}
					case (7): {
						(*pac).score += 5000;
						break;
					}
					}
					(*fruits).disable = true;
				}
			}

			if ((*pac).score >= high_score && high_score > 0) {
				high_score = (*pac).score;
				if (!IsSoundPlaying(ding_ding) && !beat_highscore) {
					beat_highscore = true;
					PlaySound(ding_ding);
				}
			}
			
			if ((*pac).score >= 10000 && !one_up) {
				lives += 1;
				one_up = true;
				
				if (!IsSoundPlaying(ding_ding) && !beat_highscore) {
					beat_highscore = true;
					PlaySound(ding_ding);
				}
			}

			if (streak >= 4) {
				(*pac).powered = false;
			}
			// draw

			BeginDrawing();


			ClearBackground(BLACK);

			

			if (since(round_ended, tick) >= 60 && round_ended.trigger >= 0) {
				if ((*pac).dots_left <= 0) {
					if (tick % 15 == 0 && flash == true) {
						flash = false;
					}
					else if (tick % 15 == 0 && flash == false) {
						flash = true;
					}
				}
				if (flash) {
					DrawTexturePro(graphics, (Rectangle) { 683, 0, 224, 248 }, (Rectangle) { 0, 78, 728, 806 }, (Vector2) { 0, 0 }, 0, RAYWHITE);
				}
				else {
					DrawTexturePro(graphics, (Rectangle) { 0, 0, 224, 248 }, (Rectangle) { 0, 78, 728, 806 }, (Vector2) { 0, 0 }, 0, RAYWHITE);
				}
				in_round = false;
				if ((*pac).dots_left > 0) {
					(*pac).live = false;
				}
				else {
					(*pac).live = true;
				}

				
				if (since(round_ended, tick) <= 239 && (*pac).frame < 10.8 && round_ended.trigger > -1) {
					draw_pacman(pac, graphics);
					if (!(*pac).live) {
						update_p(pac);
					}
					if (!IsSoundPlaying(pac_die) && !(*pac).live) {
						PlaySound(pac_die);
					}
				}
				
			}
			else{
				DrawTexturePro(graphics, (Rectangle) { 0, 0, 224, 248 }, (Rectangle) { 0, 78, 728, 806 }, (Vector2) { 0, 0 }, 0, RAYWHITE);
				Draw_grid(ptr, sources_grid, graphics);

				if (pause <= 0) {
					if (since(game_started, tick) >= 120) {

						draw_pacman(pac, graphics);
						draw_ghost(inky, graphics, (*pac).time_powered);
						draw_ghost(blinky, graphics, (*pac).time_powered);
						draw_ghost(pinky, graphics, (*pac).time_powered);
						draw_ghost(clyde, graphics, (*pac).time_powered);






					}
				}
				else {

					for (int i = 0; i < 4; i++) {
						if ((*gs[i]).entity.current_tile.row == row && (*gs[i]).entity.current_tile.collum == col && (*gs[i]).state == EATEN) {

						}
						else {
							draw_ghost(gs[i], graphics, (*pac).time_powered);
						}
					}
					draw_ghost_score(streak, (*pac).entity.centre.x, (*pac).entity.centre.y, graphics, fruits);
					pause -= 1;
				}
				
				if (eat_fruit && since(fruit_eaten, tick) < 180 && fruit_eaten.trigger > 0) {
					draw_fruit_score(graphics, fruits);
				}
				else if (eat_fruit == false && !(*fruits).disable) {
					draw_fruit(graphics, fruits);
				}
				if (since(game_started, tick) <= 120) {
					for (int i = 0; i < lives; i++) {
						DrawTexturePro(graphics, lives_rect, (Rectangle) { 50 + 50 * i, 910, 42, 42 }, (Vector2) { 21, 21 }, 0, RAYWHITE);
					}
				}
				else {
					for (int i = 0; i < lives - 1; i++) {
						DrawTexturePro(graphics, lives_rect, (Rectangle) { 50 + 50 * i, 910, 42, 42 }, (Vector2) { 21, 21 }, 0, RAYWHITE);
					}
				}
				if (!in_round) {
					DrawTextEx(font, "READY!", (Vector2) { 305, 518 }, 30, 0, YELLOW);
					if (since(game_started, tick) <= 120) {
						DrawTextEx(font, "PLAYER ONE", (Vector2) { 246, 362 }, 30, 0, ligth_blue);
					}
				}
				draw_level(level, graphics, fruits);

			}

			if (round_ended.trigger < 0) {
				update(inky);
				update(blinky);
				update(pinky);
				update(clyde);
				if (in_round) {
					update_p(pac);
				}
			}
			DrawTextEx(font, "HIGH SCORE", (Vector2) { 240, 0 }, 36, 0, YELLOW);
			DrawTextEx(font, TextFormat("%02i", (*pac).score), (Vector2) { 100, 36 }, 36 ,1, RAYWHITE);
			DrawTextEx(font, TextFormat("%02i", high_score), (Vector2) { 400, 36 }, 36, 1, RAYWHITE);
			
			
			EndDrawing();


			for (int i = 0; i < 4; i++) {
				if ((*gs[i]).state == EATEN) {
					s = eaten;
					break;
				}
			}

			if (!IsSoundPlaying(s) && !IsSoundPlaying(start_up) && round_ended.trigger < 0) {
				if (in_round) {
					PlaySound(s);
				}
				else if (since(game_started, tick) <= 120) {
					PlaySound(start_up);
				}
			}
			printf("%d\n",(*blinky).state);
			tick += 1;

		}

	}
	return 0;


}
