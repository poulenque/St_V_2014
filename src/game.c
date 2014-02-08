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

static double trigger_value_MAX[3]={0,200,200};
static double fire_value_MAX[3]   ={0,200,200};

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

//UPDATE PART THAT IS COMMON TO ALL GAMES
void game_update(Game* game,int dt){

	//=======================================================
	//=======================================================
	//=======================================================
	//======================FIRE UPDATE======================
	//=======================================================
	//=======================================================
	//=======================================================
	if(game->weapon!=0){
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
					if(game->fire_value<=0){
						game->trigger_value=0;
					}
				}

				if(game->fire_state && game->trigger_value==1){
					if(game->fire_value<=0){
						game->fire_value+=1;
						fire_arrow_with_bow(game);
					}
				}

				//UPDATE ARROWS 
				update_arrow(game);

			}
	}
	//=======================================================
	//=======================================================
	//=======================================================

	time_+=dt/15.;
	camera_update(game->player,dt);
	fake_walk_update(game,dt);

	// if(game->trigger_state==0 && game->trigger_value==game->trigger_value_MAX){
	// 	game->fire(game);
	// 	// MAYBE ???
	// 	// game->trigger_value=0;
	// 	//TODO :
	// 	//TO CHECK
	// }



	game->update(game,dt);
}































void game_render(Game* game){
	game->render(game);
	//RENDER AN INVISIBLE PLANE FOR GROUND DEPTH
	glPushMatrix();
		glTranslated(-game->player->x,-game->player->y,0);
		glTranslated(0,0,-4);
		glRotated(90,0,1,0);
		glColor4d(0,0,0,0);
		draw_face(200,0);
	glPopMatrix();
	//RENDER ARROWS
	Arrow* arrow=game->arrows;
	while(arrow!=NULL){
		double xx=arrow->x+game->player->x;
		double yy=arrow->y+game->player->y;
		double zz=arrow->z+game->player->z;
		double dist=xx*xx+yy*yy+zz*zz;
		double alpha=180+acos(arrow->dz/arrow->v)*180/PI;
		double beta=180./PI*atan2(arrow->dy,arrow->dx);


		double linewidth=3;
		double pointsize=1;
		//reflexion

	glColor4d(1,0,0,.3);
		// glDepthFunc(GL_ALWAYS);//debug
		glDepthFunc(GL_GREATER);
		glDepthMask(GL_FALSE);
		glPushMatrix();
			glTranslated(arrow->x,arrow->y,-(arrow->z+8));
			glScaled(.5,.5,-.5);
			glRotated(beta,0,0,1);
			glRotated(alpha,0,1,0);

			glLineWidth(linewidth);
			glPointSize(pointsize);

			// if(!(arrow->z<=-4)){
			// 	glBegin(GL_LINES);
			// 		glVertex3d(
			// 			+2*arrow->dx,
			// 			+2*arrow->dy,
			// 			+2*arrow->dz
			// 			);
			// 		glVertex3d(
			// 			-2*arrow->dx,
			// 			-2*arrow->dy,
			// 			-2*arrow->dz
			// 			);
			// 	glEnd();
			// 	glBegin(GL_POINTS);
			// 		glVertex3d(
			// 			+2*arrow->dx,
			// 			+2*arrow->dy,
			// 			+2*arrow->dz
			// 			);
			// 		glVertex3d(
			// 			-2*arrow->dx,
			// 			-2*arrow->dy,
			// 			-2*arrow->dz
			// 			);
			// 	glEnd();
			// }
			if(dist<500){
				// glColor4d(1,0,0,1);
				if(!(arrow->z<=-4)){
					glScaled(2,2,2);
				}
				draw_arrow_high_quality();
			}else{
				// glColor4d(0,0,1,1);
				if(!(arrow->z<=-4)){
					glScaled(2,2,2);
					draw_arrow_low_quality();
				}else
				// if(dist<1500){
					draw_arrow_very_low_quality();
				// }else {
					// draw_arrow_ultra_low_quality();
				// }
			}
		glPopMatrix();
		glDepthFunc(GL_LESS);
		glDepthMask(GL_TRUE);

	glColor4d(1,0,0,1);
		//REAL OBJECT
		glPushMatrix();
			glTranslated(arrow->x,arrow->y,arrow->z);
			glScaled(.5,.5,.5);
			glRotated(beta,0,0,1);
			glRotated(alpha,0,1,0);

			glLineWidth(linewidth);
			glPointSize(pointsize);

			// if(!(arrow->z<=-4)){
			// 	glBegin(GL_LINES);
			// 		glVertex3d(
			// 			+2*arrow->dx,
			// 			+2*arrow->dy,
			// 			+2*arrow->dz
			// 			);
			// 		glVertex3d(
			// 			-2*arrow->dx,
			// 			-2*arrow->dy,
			// 			-2*arrow->dz
			// 			);
			// 	glEnd();
			// 	glBegin(GL_POINTS);
			// 		glVertex3d(
			// 			+2*arrow->dx,
			// 			+2*arrow->dy,
			// 			+2*arrow->dz
			// 			);
			// 		glVertex3d(
			// 			-2*arrow->dx,
			// 			-2*arrow->dy,
			// 			-2*arrow->dz
			// 			);
			// 	glEnd();

			// }
			if(dist<500){
				// glColor4d(1,0,0,1);
				if(!(arrow->z<=-4)){
					glScaled(2,2,2);
				}
				draw_arrow_high_quality();
			}else{
				// glColor4d(0,0,1,1);
				if(!(arrow->z<=-4)){
					glScaled(2,2,2);
					draw_arrow_low_quality();
				}else
				// if(dist<1500){
					draw_arrow_very_low_quality();
				// }else {
					// draw_arrow_ultra_low_quality();
				// }
			}
		glPopMatrix();
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
	trigger_value_MAX[0]=0;
	fire_value_MAX[0]   =0;
	//bow
	trigger_value_MAX[1]=200;
	fire_value_MAX[1]   =300;
	// fire_value_MAX[1]   =1800;
	// la sulfateuse
	trigger_value_MAX[2]=20;
	fire_value_MAX[2]   =.1;

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
	// glClearColor( 1., 1., 1., 1. );
	
	// game->update=ingame_level1_update;
	// game->render=ingame_level1_render;


	//===========================
	//===========================


	return game;
}
