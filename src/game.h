#ifndef GAME_H
#define GAME_H

#include "camera.h"
#include "objects.h"
// #include "audioplayer.h"

typedef struct Camera Camera;


double get_time_();
void set_time_(double t);
String3d* get_str();








typedef struct Game{
	Camera* player;

	Arrow* arrows;
	Arrow* arrows_last;
	Arrow* arrows_to_update;//chained list

	int color_debug;
	int sorting;
	int next_sort_time;

	double world_x_size;
	double world_y_size;


	Mechant* mechants;

	// AudioPlayer* audio;

	void (*update)(struct Game* game,int dt);
	void (*render)(struct Game* game);
	void (*HUD_render)(struct Game* game);

	// fire_value = 0 -> loaded
	// fire_value = 1 -> fired once
	// fire_value = 2 -> fired twice
	double fire_value;
	int fire_state;
	double trigger_value;
	int trigger_state;

	int weapon;
	void (*trigger)(struct Game* game,int state);
	void (*fire)(struct Game* game,int state);
}Game;

Game* initGame(Camera* player);
void game_pause(Game * game,int state);
void game_update(Game* game,int dt);
void game_render(Game* game);
void clear_arrow(Game* game);
void clear_mechant(Game* game);


#endif