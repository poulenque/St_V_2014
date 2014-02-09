#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <math.h>
#include "random.h"
#include "string3d.h"
#include "constants.h"
#include "shader.h"
#include "draw.h"
#include "HUD.h"
#include "levels.h"

//==========================================================
//                                                      
//  _|_|_|_|    _|_|    _|      _|  _|_|_|_|_|          
//  _|        _|    _|  _|_|    _|      _|          _|  
//  _|_|_|    _|    _|  _|  _|  _|      _|              
//  _|        _|    _|  _|    _|_|      _|              
//  _|          _|_|    _|      _|      _|          _|  
//                                                      
//==========================================================
//http://patorjk.com/software/taag/#p=display&f=Block&t=FONT
//==========================================================

static double time_=0;
double get_time_(){
	return time_;
}
void set_time_(double t){
	time_=t;
}

void clear_arrow(Game* game){
	Arrow* arrow = game->arrows;
	Arrow* a;
	while(arrow!=NULL){
		a=arrow->next;	
		free(arrow);
		arrow=a;
	}
	game->arrows=NULL;
	game->arrows_to_update=NULL;
}

void clear_mechant(Game* game){
	Mechant* mechant = game->mechants;
	Mechant* m;
	while(mechant!=NULL){
		m=mechant->next;	
		free(mechant);
		mechant=m;
	}
	game->mechants=NULL;
}


static String3d* str;
String3d* get_str(){
	return str;
}

static double trigger_value_MAX[4];
static double fire_value_MAX[4]   ;

static double messages_x[200];
static double messages_y[200];
static double messages_z[200];
static double messages_z_exp_offset[200];
static double messages_z_exp_speed[200];
static double messages_dephasage[200];

int ttt=0;
static void update_arrow(Game* game){
		Arrow* arrow_before=NULL;
		Arrow* arrow=game->arrows_to_update;
		ttt+=1;
		while(arrow!=NULL){
			arrow->v=sqrt(arrow->dx*arrow->dx + arrow->dy*arrow->dy + arrow->dz*arrow->dz);
			double angle_=-1+acos(arrow->dz/arrow->v)*2./PI;
			if(arrow->z>-4){

				// ACCELERATION g
				arrow->dz -=.0002;

				arrow->x += arrow->dx;
				arrow->y += arrow->dy;
				arrow->z += arrow->dz;

				arrow->alpha=180+acos(arrow->dz/arrow->v)*180/PI;
				arrow->beta=180./PI*atan2(arrow->dy,arrow->dx);

			//TODO COLLISION
			//TODO COLLISION
			//TODO COLLISION
			//TODO COLLISION
			//TODO COLLISION
			//TODO COLLISION
			//TODO COLLISION
			//TODO COLLISION
			//TODO COLLISION
			//TODO COLLISION
			//TODO COLLISION
			//TODO COLLISION
			//TODO COLLISION
			//TODO COLLISION
			//TODO COLLISION

			}else{
				// double k=(-4-angle_*2)/(game->arrows[i].dz);
				// game->arrows[i].x=k*game->arrows[i].dx+x_before;
				// game->arrows[i].y=k*game->arrows[i].dy+y_before;
				// game->arrows[i].z=-4-angle_*2 = k*dz+z_before
				double factor = -arrow->dz*10;
				if(factor>1)
					factor=1;
				arrow->z=-4-angle_*2*factor - random(.1,angle_);
				// arrow->z=-4-angle_*2*factor ;
				//RETIRER DES UPDATABLE
				if(arrow_before != NULL){
					arrow_before->next_update = arrow->next_update;
				}
				if( arrow==game->arrows_to_update){
					game->arrows_to_update=arrow->next_update;
				}
				arrow->next_update=NULL;
			}
			arrow_before=arrow;
			arrow=arrow->next_update;
		}
}

static void fire_arrow_with_bow(Game* game){
	Arrow* to_add= malloc(sizeof(Arrow));

	double y_offset=-.5  + 2./180.*game->player->theta;
	double z_offset=-1.5 - 5./180.*game->player->theta;

	to_add->x=-game->player->x + y_offset*sin(game->player->phi/360.*2.*PI);
	to_add->y=-game->player->y + y_offset*cos(game->player->phi/360.*2.*PI);
	to_add->z=-game->player->z + z_offset;

	to_add->dx= .6*cos(-game->player->phi/360.*2.*PI)*(1-1.6*fabs(sin(-game->player->theta/360.*2.*PI)))*random(.85,.3) + .6*sin(game->player->phi/360.*2.*PI-180.)*random(-.015,.1);
	to_add->dy= .6*sin(-game->player->phi/360.*2.*PI)*(1-1.6*fabs(sin(-game->player->theta/360.*2.*PI)))*random(.85,.3) + .6*cos(game->player->phi/360.*2.*PI-180.)*random(-.015,.1);
	double dz;
	if(game->player->theta>0){
		//look up
		dz=-.4*sin(-game->player->theta/180.*PI);
	}else{
		//look down
		dz=-.1*sin(-game->player->theta/180.*PI);
		// if(dz>.0001)dz=.001;
		if(dz>0.0001)dz=0.0001;
	}
	to_add->dz=dz;

	//======================
	//UPDATE THE UPDATE_LIST 
	//======================

	to_add->next_update=game->arrows_to_update;
	game->arrows_to_update = to_add;

	to_add->next=game->arrows;
	game->arrows = to_add;
}

static void fire_arrow_with_sulfateuse(Game* game){
	Arrow* to_add= malloc(sizeof(Arrow));

	double x_offset=1;
	double y_offset=-.5  + 2./180.*game->player->theta;
	double z_offset;
	if(game->player->theta<0){
		x_offset=0;
		z_offset=-1.5 + 5./180.*game->player->theta;
	}else{
		z_offset=-1.5 - 10./180.*game->player->theta;
	}

	to_add->x=-game->player->x + y_offset*sin(game->player->phi/360.*2.*PI) + x_offset*cos(game->player->phi/360.*2.*PI);
	to_add->y=-game->player->y + y_offset*cos(game->player->phi/360.*2.*PI) - x_offset*sin(game->player->phi/360.*2.*PI);
	to_add->z=-game->player->z + z_offset;

	to_add->dx= .6*cos(-game->player->phi/360.*2.*PI)*(1-1.6*fabs(sin(-game->player->theta/360.*2.*PI)))*random(.85,.3) + .6*sin(game->player->phi/360.*2.*PI-180.)*random(-.015,.1);
	to_add->dy= .6*sin(-game->player->phi/360.*2.*PI)*(1-1.6*fabs(sin(-game->player->theta/360.*2.*PI)))*random(.85,.3) + .6*cos(game->player->phi/360.*2.*PI-180.)*random(-.015,.1);
	double dz;
	if(game->player->theta>0){
		//look up
		dz=-.4*sin(-game->player->theta/180.*PI);
	}else{
		//look down
		dz=-.05*sin(-game->player->theta/180.*PI);
		// if(dz>.0001)dz=.001;
		if(dz>0.0001)dz=0.0001;
	}
	to_add->dz=dz;

	//======================
	//UPDATE THE UPDATE_LIST 
	//======================

	to_add->next_update=game->arrows_to_update;
	game->arrows_to_update = to_add;

	to_add->next=game->arrows;
	game->arrows = to_add;
}

//UPDATE PART THAT IS COMMON TO ALL GAMES
void game_update(Game* game,int dt){

	time_+=dt/15.;
	camera_update(game->player,dt);
	fake_walk_update(game,dt);
	//=======================================================
	//=======================================================
	//=======================================================
	//======================FIRE UPDATE======================
	//=======================================================
	//=======================================================
	//=======================================================
		for(int i=0;i<dt;i++){

			if(game->trigger_state){
				//augmente jusqu'a trigger_value_MAX
				game->trigger_value+=1./trigger_value_MAX[game->weapon];
				if(game->trigger_value>1){
					// printf("trigger MAX\n");
					game->trigger_value=1;
				}
			}else{
				//diminue jusqu'a 0
				//!! VITESSE DIMINUTION PLUS GRANDE 
				game->trigger_value-=1.5/trigger_value_MAX[game->weapon];
				if(game->trigger_value<0){
					game->trigger_value=0;
				}
			}

			if(game->fire_value>0){
				game->fire_value-=1./fire_value_MAX[game->weapon];
				if(game->weapon==1 && game->fire_value<=0){
					game->trigger_value=0;
				}
			}

			if(game->fire_state && game->trigger_value==1){
				if(game->fire_value<=0){
					game->fire_value+=1;
					if(game->weapon==1){
						fire_arrow_with_bow(game);
					}else if(game->weapon>=2){
						fire_arrow_with_sulfateuse(game);
					}
				}
			}

			//UPDATE ARROWS 
			update_arrow(game);

		}
	//=======================================================
	//=======================================================
	//=======================================================


	// if(game->trigger_state==0 && game->trigger_value==game->trigger_value_MAX){
	// 	game->fire(game);
	// 	// MAYBE ???
	// 	// game->trigger_value=0;
	// 	//TODO :
	// 	//TO CHECK
	// }



	game->update(game,dt);
}




























void game_render_one_arrow(Arrow * arrow){
	glRotated(arrow->beta,0,0,1);
	glRotated(arrow->alpha,0,1,0);
	if(arrow->dist<500){
		if(!(arrow->z<=-4)){
			glScaled(2,2,2);
		}
		draw_arrow_high_quality();
	}else{
		if(!(arrow->z<=-4)){
			glScaled(2,2,2);
			draw_arrow_low_quality();
		}else if(arrow->dist<30000){
			draw_arrow_very_low_quality();
		}else {
			draw_arrow_ultra_low_quality();
		}
	}
}

void game_render_one_mechant(Mechant * mechant){

}

void game_render(Game* game){
	game->render(game);
	
	//RENDER AN INVISIBLE PLANE FOR GROUND DEPTH
	glPushMatrix();
		glTranslated(-game->player->x,-game->player->y,0);
		glTranslated(0,0,-4);
		glRotated(90,0,1,0);
		glColor4d(0,0,0,0);
		draw_face(600,0);
	glPopMatrix();
	GLfloat bkColor[3];
	glGetFloatv(GL_COLOR_CLEAR_VALUE, bkColor);

	//=======================LOOP TEST=========================
	//=======================LOOP TEST=========================
	//=======================LOOP TEST=========================
	// glPushMatrix();
	// 	glTranslated(-game->player->x,-game->player->y,-4);
	// 	glRotated(90,0,1,0);
	// 	glScaled(1,game->world_y_size,game->world_x_size);
	// 	glLineWidth(5);
	// 	glColor4d(0,0,1,1);
	// 	draw_square(.5,0);
	// glPopMatrix();


	Arrow* arrow;
	Mechant* mechant;

	//REFLEXIONS
	glDepthFunc(GL_GREATER);
	glDepthMask(GL_FALSE);
	glPushMatrix();
		//TO THE GROUND
		glTranslated(0,0,-8);


		//=======================ARROWS=======================
		//=======================ARROWS=======================
		//=======================ARROWS=======================
		glColor4d(.5+.5*bkColor[0],0+.5*bkColor[1],0+.5*bkColor[2],1);
		arrow=game->arrows;
		while(arrow!=NULL){
			//WORLD LOOP
			while(arrow->x+game->player->x+game->world_x_size/2.>0)
				arrow->x-=game->world_x_size;
			while(arrow->x+game->player->x+game->world_x_size/2.<0)
				arrow->x+=game->world_x_size;
			while(arrow->y+game->player->y+game->world_y_size/2.>0)
				arrow->y-=game->world_y_size;
			while(arrow->y+game->player->y+game->world_y_size/2.<0)
				arrow->y+=game->world_y_size;


			double xx=arrow->x+game->player->x;
			double yy=arrow->y+game->player->y;
			double zz=arrow->z+game->player->z;
			arrow->dist=xx*xx+yy*yy+zz*zz;

			if(arrow->dist<90000){
				// glDepthFunc(GL_ALWAYS);//debug
				glPushMatrix();
					glTranslated(arrow->x,arrow->y,-arrow->z);
					glScaled(.5,.5,-.5);
					game_render_one_arrow(arrow);
				glPopMatrix();
			}
			arrow=arrow->next;
		}
		//======================MECHANTS======================
		//======================MECHANTS======================
		//======================MECHANTS======================
		mechant=game->mechants;
		while(mechant!=NULL){
			double xx=mechant->x+game->player->x;
			double yy=mechant->y+game->player->y;
			double zz=mechant->z+game->player->z;
			mechant->dist=xx*xx+yy*yy+zz*zz;

			mechant=mechant->next;
		}

	glPopMatrix();
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);





	//REAL WORLD
	glColor4d(1,0,0,1);
	arrow=game->arrows;
	while(arrow!=NULL){
		if(arrow->dist<90000){
			glPushMatrix();
				glTranslated(arrow->x,arrow->y,arrow->z);
				glScaled(.5,.5,.5);
				game_render_one_arrow(arrow);
			glPopMatrix();
		}
		arrow=arrow->next;
	}

}

void fire(Game* game,int state){
	game->fire_state=state;
}

void trigger(Game* game,int state){
	game->trigger_state=state;
	// if(state)
	// 	printf("trigger_ON\n");
	// else
	// 	printf("trigger_OFF\n");
}

void game_pause(Game * game,int state){
	if(state){
		//TODO PAUSE MUSIC
	}else{
		//TODO UNPAUSE MUSIC
	}
}




































Game* initGame(Camera* player){

	//no weapon
	trigger_value_MAX[0]=1;//avoid 1./0.
	fire_value_MAX[0]   =1;//avoid 1./0.
	//bow
	trigger_value_MAX[1]=200;
	fire_value_MAX[1]   =300;
	// fire_value_MAX[1]   =1800;
	// la sulfateuse
	trigger_value_MAX[2]=400;
	fire_value_MAX[2]   =100;
	// la sulfateuse BOURRIN
	trigger_value_MAX[3]=400;
	fire_value_MAX[3]   =10;

	draw_init();
	// audio_init();

	for(int i=0;i<200;i++){
		messages_x[i]=rand()*1./RAND_MAX;
		messages_y[i]=rand()*1./RAND_MAX;
		messages_z[i]=rand()*1./RAND_MAX;
		messages_z_exp_offset[i]=rand()*1./RAND_MAX;
		messages_z_exp_speed[i]=rand()*1./RAND_MAX;
		messages_dephasage[i]=rand()*1./RAND_MAX;
	}

	str = new_string3d();
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glClearColor( 0., 0., 0., 1. );

	glEnable(GL_DEPTH_TEST);
	glEnable (GL_BLEND);
	glDisable(GL_CULL_FACE);

	glEnable(GL_TEXTURE_2D);

	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LESS);//GL_NEVER, GL_LESS, GL_EQUAL, GL_LEQUAL, GL_GREATER, GL_NOTEQUAL, GL_GEQUAL, GL_ALWAYS, GL_LESS

	glEnable(GL_POINT_SMOOTH);
	glDisable( GL_LINE_SMOOTH );
	glDisable( GL_POLYGON_SMOOTH ); // THIS MAKES A NICE ARTEFACT :¬D

	
	glHint(GL_LINE_SMOOTH_HINT,GL_FASTEST);
	glHint(GL_POLYGON_SMOOTH_HINT,GL_FASTEST);
	glHint(GL_TEXTURE_COMPRESSION_HINT,GL_FASTEST);
	glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_FASTEST);

	//GL_FASTEST, GL_NICEST, and GL_DONT_CARE
	// glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
	// glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );

	// glEnable(GL_AUTO_NORMAL);
	// glEnable(GL_NORMALIZE);


	Game* game = malloc(sizeof(Game));

	game->update=intro_update;
	game->render=intro_render;

	game->player=player;

	game->HUD_render=HUD;

	game->trigger=trigger;
	game->trigger_value=0;
	game->fire=fire;
	game->fire_value=0;
	game->weapon=0;

	game->mechants=NULL;

	game->arrows=NULL;
	game->arrows_to_update=NULL;
	// game->audio= audio_new (PLAYER_AMBIENT|PLAYER_LOOP);
	// audio_playMusic(game->audio,"music/Goto80_gopho_loop.ogg");

	//===========================
	// 
	//  _|_|_|_|_|  _|_|_|_|    _|_|_|  _|_|_|_|_|  _|_|_|  _|      _|    _|_|_|  
	//      _|      _|        _|            _|        _|    _|_|    _|  _|        
	//      _|      _|_|_|      _|_|        _|        _|    _|  _|  _|  _|  _|_|  
	//      _|      _|              _|      _|        _|    _|    _|_|  _|    _|  
	//      _|      _|_|_|_|  _|_|_|        _|      _|_|_|  _|      _|    _|_|_|  
	//                                                                            
	//THIS IS FOR TESTING PURPOSE
	//===========================

	game->world_x_size=600;
	game->world_y_size=600;

	// glClearColor( 1., 1., 1., 1. );
	// game->update=ingame_level1_update;
	// game->render=ingame_level1_render;


	//===========================
	//===========================


	return game;
}
