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
	int arrow_count;
	int arrow_limit;

	Mechant* mechants;
	int mechant_count;
	int mechant_limit;

	// AudioPlayer* audio;

	void (*update)(struct Game* game,int dt);
	void (*render)(struct Game* game);
	void (*HUD_render)(struct Game* game);

	double fire_value;//if [0,1[ : firing ; if =1 , not firing
	double trigger_value;
	int trigger_state;
	int weapon;
	void (*trigger)(struct Game* game,int state);
	void (*fire)(struct Game* game);
}Game;

Game* initGame(Camera* player);
void game_pause(Game * game,int state);
void game_update(Game* game,int dt);
void game_render(Game* game);


#endif