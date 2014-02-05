#ifndef GAME_H
#define GAME_H

#include "camera.h"
#include "audioplayer.h"

typedef struct Camera Camera;

// enum PLAYER_STATE {ARMING,FIRING,IDLE};

typedef struct Game{
	double shared_var1;
	Camera* player;
	AudioPlayer* audio;
	void (*update)(struct Game* game,int dt);
	void (*render)(struct Game* game);
	void (*HUD_render)(struct Game* game);

	double fire_value;//if [0,1[ : firing ; if =1 , not firing
	double fire_value_MAX;
	double trigger_value;
	double trigger_value_MAX;
	int trigger_state;
	int weapon;
	void (*trigger)(struct Game* game,int state);
	void (*fire)(struct Game* game);
}Game;

Game* initGame(Camera* player);
void game_pause(Game * game,int state);
void game_update(Game* game,int dt);



#endif