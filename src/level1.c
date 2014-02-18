#include "levels.h"
#include "random.h"




//==================================================================
//                                                                
//  _|        _|_|_|_|  _|      _|  _|_|_|_|  _|              _|  
//  _|        _|        _|      _|  _|        _|            _|_|  
//  _|        _|_|_|    _|      _|  _|_|_|    _|              _|  
//  _|        _|          _|  _|    _|        _|              _|  
//  _|_|_|_|  _|_|_|_|      _|      _|_|_|_|  _|_|_|_|        _|  
//                                                                
//==================================================================
//==================================================================
//==================================================================
void level1_spawn_mechants(Game* game){
	Mechant * mechant;
	// for(int i=-15;i<15;i++){
	// 	for(int j=-15;j<15;j++){
	// 		mechant = malloc(sizeof(Mechant));
	// 		mechant->x=20*i;
	// 		mechant->y=20*j;
	// 		mechant->z=0;

	// 		mechant->dx=0;
	// 		mechant->dy=0;
	// 		mechant->dz=0;

	// 		mechant->update=NULL;
	// 		game_insert_Mechant(game, mechant);
	// 	}
	// }


	for(int i=-10;i<10;i++){
		for(int j=-10;j<10;j++){
			mechant = malloc(sizeof(Mechant));
			double rayon = random(200,120);
			double angle = random(0,2*PI);
			mechant->x=rayon*cos(angle);
			mechant->y=rayon*sin(angle);
			mechant->z=0;

			mechant->dx=random(0,.05);
			mechant->dy=random(0,.05);
			mechant->dz=0;

			mechant->rho=0;
			mechant->theta=0;
			mechant->phi=random(0,360);

			mechant->drho=0;
			mechant->dtheta=0;
			mechant->dphi=random(0,.5);
			// mechant->dphi=.25;

			mechant->update=mechant_update_dummy;
			mechant->type=0;
			// mechant->update=NULL;
			game_insert_Mechant(game, mechant);
		}
	}

}
void ingame_level1_setup(Game* game){
	audioplayer_set_next(game->audio,"music/Goto80_gopho_level1.ogg");

	glClearColor(1,1,1,1);

	// game->player->x=0;
	// game->player->y=0;
	// game->player->z=0;
	// game->player->theta=0;
	game->update=ingame_level1_update;
	game->render=ingame_level1_render;
	game->weapon=1;

	set_time_(0);

	glEnable(GL_FOG);

	glFogi(GL_FOG_MODE, GL_LINEAR);//GL_EXP, GL_EXP2, GL_LINEAR
	glFogf(GL_FOG_START, 20);
	glFogf(GL_FOG_END, 300);

	// glFogi(GL_FOG_MODE, GL_EXP);//GL_EXP, GL_EXP2, GL_LINEAR
	// glFogi(GL_FOG_MODE, GL_EXP2);//GL_EXP, GL_EXP2, GL_LINEAR
	// glFogf(GL_FOG_START, 2000);
	// glFogf(GL_FOG_END, 3000);

	GLfloat fogColor[4]= {1,1, 1, 1};
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.35f);
	glHint(GL_FOG_HINT, GL_DONT_CARE);

	glFogf(GL_FOG_START, 20);
	glFogf(GL_FOG_END, 50);
	level1_spawn_mechants(game);

}
static int landed=0;
void ingame_level1_update(Game* game,int dt){
	if(!strcmp(game->audio->now_playing,"music/Goto80_gopho_loop_far.ogg")){
		game->player->z=-100;
		game->player->dz=0;
		// String3d* str=get_str();
		// string3d_setTxt(str,"==========\n");
	}
	if(!strcmp(game->audio->now_playing,"music/Goto80_gopho_level1.ogg")){

		audioplayer_set_next(game->audio,"music/Goto80_gopho_level2.ogg");

		// printf("%lf\n", audioplayer_getTime(game->audio));
		if(audioplayer_getTime(game->audio)<6.7){
			// printf("FLYING\n");
			// game->player->z=-100;
			// game->player->dz=0;
		}else if(audioplayer_getTime(game->audio)<7.65){
			double t=(audioplayer_getTime(game->audio)-6.7)/(7.65-6.7);
			glFogf(GL_FOG_START, 20);
			glFogf(GL_FOG_END, 50+t*250);

			// game->player->z=100-100*(audioplayer_getTime(game->audio)-6.7)/(7.65-6.7);
			// game->player->dz=-10;
		}else{
			if(!landed){
				for(int i=0;i<20;i++){
					game_add_explosion(game,GOOD,50,
						-game->player->x + random(0,20),
						-game->player->y + random(0,20),
						-game->player->z + random(0,20),
						-0.003*game->player->dx,
						-0.003*game->player->dy,
						0.);
				}
				landed=1;
				// printf("BOOM\n");
			}
		}

		if (audioplayer_getTime(game->audio)>37.30 &&
			audioplayer_getTime(game->audio)<37.60){
			GLfloat fogColor[4]= {0,0, 0, 1};
			glFogfv(GL_FOG_COLOR, fogColor);
			glClearColor(0,0,0,1);
		}else
		if (audioplayer_getTime(game->audio)>37.60 &&
			audioplayer_getTime(game->audio)<37.85){
			GLfloat fogColor[4]= {1,0, 0, 1};
			glFogfv(GL_FOG_COLOR, fogColor);
			glClearColor(1,0,0,1);
		}else
		if (audioplayer_getTime(game->audio)>37.85){
			GLfloat fogColor[4]= {0,0, 0, 1};
			glFogfv(GL_FOG_COLOR, fogColor);
			game->weapon=4;
			// TODO
			// TODO
			// TODO
			// SPAWN NEW MONSTER
			// TODO
			// TODO
			// TODO
			glClearColor(0,0,0,1);
		}

	}
	if(!strcmp(game->audio->now_playing,"music/Goto80_gopho_level2.ogg")){
		ingame_level2_setup(game);
	}

}
void ingame_level1_render(Game* game){
	// if(!strcmp(game->audio->now_playing,"music/Goto80_gopho_loop_far.ogg")){
	// 		double t=audioplayer_getTime(game->audio)/7.66;
	// }

	// glColor4d(1,0,0,1);
	// for(int i=0;i<10;i++){
	// 	for(int j=0;j<10;j++){
	// 		glBegin(GL_LINE_STRIP);
	// 			glVertex3d( 10*i, 10*j,-4+100);
	// 			glVertex3d(-10*i, 10*j,-4+100);
	// 			glVertex3d(-10*i,-10*j,-4+100);
	// 			glVertex3d( 10*i,-10*j,-4+100);
	// 		glEnd();
	// 	}
	// }
}










