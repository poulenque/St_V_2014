#ifndef GAME_H
#define GAME_H

#include "camera.h"

typedef struct Camera Camera;

typedef struct Game{
	unsigned int dof_Shader_id;
	//
	// unsigned int frame_buffer_id;
	// unsigned int depth_tex_id;
	//
	Camera* player;
	void (*update)(struct Game* game,int dt);
	void (*render)(struct Game* game);
}Game;

Game* initGame(Camera* player);



#endif