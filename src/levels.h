#ifndef LEVELS_H
#define LEVELS_H


#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <math.h>
#include "string3d.h"
#include "constants.h"
#include "shader.h"
#include "draw.h"
#include "HUD.h"


void intro_update(Game* game,int dt);
void intro_render(Game* game);

void intro_get_weapon_update(Game* game,int dt);
void intro_get_weapon_render(Game* game);

//friendly ennemies
void ingame_level1_update(Game* game,int dt);
void ingame_level1_render(Game* game);
//ennemies are angry
void ingame_level2_update(Game* game,int dt);
void ingame_level2_render(Game* game);
//swarm... you get "la sulphateuse"
void ingame_level3_update(Game* game,int dt);
void ingame_level3_render(Game* game);
//boss finale !
void ingame_level4_update(Game* game,int dt);
void ingame_level4_render(Game* game);



#endif
