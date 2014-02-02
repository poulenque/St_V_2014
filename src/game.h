#ifndef GAME_H
#define GAME_H

#include "camera.h"

typedef struct Camera Camera;

typedef struct Game{
	Camera* player;
	void (*update)(struct Game* game,int dt);
	void (*render)(struct Game* game);
}Game;

Game* initGame(Camera* player);



#endif