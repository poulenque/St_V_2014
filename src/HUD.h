#ifndef HUD_H
#define HUD_H

#include "game.h"

void bow_HUD(Game*);
void weapon_HUD(Game* game);
//anim_frame is a value between 0 and 1
void weapon_HUD_ARM(Game* game);
void weapon_HUD_FIRE(Game* game);
void empty_HUD(Game* game);
void fake_walk_update(Game* game,int dt);

#endif