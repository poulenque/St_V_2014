#ifndef GAME_H
#define GAME_H

#include "camera.h"
#include "audioplayer.h"

typedef struct Camera Camera;

typedef struct Game{
	double shared_var1;
	Camera* player;
	AudioPlayer* audio;
	void (*update)(struct Game* game,int dt);
	void (*render)(struct Game* game);
	void (*HUD_render)(struct Game* game);
}Game;

Game* initGame(Camera* player);
void game_pause(Game * game,int state);



#endif