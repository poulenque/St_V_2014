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

void game_update(Game* game,int dt){
	//UPDATE PART THAT IS COMMON TO ALL GAMES

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

	if(game->trigger_state){
		//augmente jusqu'a trigger_value_MAX
		game->trigger_value+=dt/trigger_value_MAX[game->weapon];
		if(game->trigger_value>1){
			// printf("trigger MAX\n");
			game->trigger_value=1;
		}
	}else{
		//diminue jusqu'a 0
		//!! VITESSE DIMINUTION PLUS GRANDE 
		game->trigger_value-=1.5*dt/trigger_value_MAX[game->weapon];
		if(game->trigger_value<0){
			game->trigger_value=0;
		}
	}

	if(game->fire_value>=1){
		game->fire_value=1;
	}else{
		game->fire_value+=dt/fire_value_MAX[game->weapon];
		if(game->fire_value>=1){
			game->trigger_value=0;
		}
	}

	//UPDATE ARROWS 
	for(int i=0;i<game->arrow_count;i++){

		double rayon=sqrt(game->arrows[i].dx*game->arrows[i].dx + game->arrows[i].dy*game->arrows[i].dy + game->arrows[i].dz*game->arrows[i].dz);
		double angle_=-90+acos(game->arrows[i].dz/rayon)*180/PI;
		angle_=angle_/90;
		if(game->arrows[i].z>-4){
			game->arrows[i].dz -=.1;

			game->arrows[i].x +=game->arrows[i].dx;
			game->arrows[i].y +=game->arrows[i].dy;
			game->arrows[i].z +=game->arrows[i].dz;

		//TODO COLLISION
		//TODO COLLISION
		//TODO COLLISION
		}else if(game->arrows[i].z<-4-angle_*2){
			game->arrows[i].z=-4-angle_*2;
		}

	}

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
	for(int i=0;i<game->arrow_count;i++){
		double xx=game->arrows[i].x+game->player->x;
		double yy=game->arrows[i].y+game->player->y;
		double zz=game->arrows[i].z+game->player->z;
		double dist=xx*xx+yy*yy+zz*zz;
		double rayon=sqrt(game->arrows[i].dx*game->arrows[i].dx + game->arrows[i].dy*game->arrows[i].dy + game->arrows[i].dz*game->arrows[i].dz);
		double alpha=180+acos(game->arrows[i].dz/rayon)*180/PI;
		double beta=180./PI*atan2(game->arrows[i].dy,game->arrows[i].dx);

		//reflexion
	glColor4d(1,0,0,.3);
		// glDepthFunc(GL_ALWAYS);//debug
		glDepthFunc(GL_GREATER);
		glDepthMask(GL_FALSE);
		glPushMatrix();
			glTranslated(game->arrows[i].x,game->arrows[i].y,-(game->arrows[i].z+8));
			glScaled(.5,.5,-.5);
			if(!(game->arrows[i].z<=-4)){
				glLineWidth(2);
				glPointSize(2);
				glBegin(GL_LINES);
					glVertex3d(
						+2*game->arrows[i].dx,
						+2*game->arrows[i].dy,
						+2*game->arrows[i].dz
						);
					glVertex3d(
						-2*game->arrows[i].dx,
						-2*game->arrows[i].dy,
						-2*game->arrows[i].dz
						);
				glEnd();
				glBegin(GL_POINTS);
					glVertex3d(
						+2*game->arrows[i].dx,
						+2*game->arrows[i].dy,
						+2*game->arrows[i].dz
						);
					glVertex3d(
						-2*game->arrows[i].dx,
						-2*game->arrows[i].dy,
						-2*game->arrows[i].dz
						);
				glEnd();

			}
			glRotated(beta,0,0,1);
			glRotated(alpha,0,1,0);
			if(dist<500){
				if(!(game->arrows[i].z<=-4)){
					glScaled(2,2,2);
				}
				draw_arrow(1);
			}else{
				if(!(game->arrows[i].z<=-4)){
					glScaled(2,2,2);
				}
				draw_arrow(0);
			}
		glPopMatrix();
		glDepthFunc(GL_LESS);
		glDepthMask(GL_TRUE);

	glColor4d(1,0,0,1);
		//REAL OBJECT
		glPushMatrix();
			glTranslated(game->arrows[i].x,game->arrows[i].y,game->arrows[i].z);
			glScaled(.5,.5,.5);
			if(!(game->arrows[i].z<=-4)){
				glLineWidth(2);
				glPointSize(2);
				glBegin(GL_LINES);
					glVertex3d(
						+2*game->arrows[i].dx,
						+2*game->arrows[i].dy,
						+2*game->arrows[i].dz
						);
					glVertex3d(
						-2*game->arrows[i].dx,
						-2*game->arrows[i].dy,
						-2*game->arrows[i].dz
						);
				glEnd();
				glBegin(GL_POINTS);
					glVertex3d(
						+2*game->arrows[i].dx,
						+2*game->arrows[i].dy,
						+2*game->arrows[i].dz
						);
					glVertex3d(
						-2*game->arrows[i].dx,
						-2*game->arrows[i].dy,
						-2*game->arrows[i].dz
						);
				glEnd();

			}
			glRotated(beta,0,0,1);
			glRotated(alpha,0,1,0);
			if(dist<500){
				if(!(game->arrows[i].z<=-4)){
					glScaled(2,2,2);
				}
				draw_arrow(1);
			}else{
				if(!(game->arrows[i].z<=-4)){
					glScaled(2,2,2);
				}
				draw_arrow(0);
			}
		glPopMatrix();

	}
}

void fire(Game* game){
	if(game->weapon==0)return;
	if(game->trigger_value==1 & game->fire_value==1){
		// printf("fire BENG BENG BENG BENG !!!\n");
		//ALLOC MORE MEMORY IF NEEDED
		if(game->arrow_count+1==game->arrow_limit){
			game->arrow_limit*=2;
			// printf("%i\n",sizeof(Arrow)*game->arrow_limit);
			// printf("%i\n\n",game->arrow_limit);
			game->arrows=realloc(game->arrows,sizeof(Arrow)*game->arrow_limit);
		}
		//PUT THAT THING
		//TODO PRENDRE EN COMPTE L'ORIENTATION DE LA CAMERA
		//TODO PRENDRE EN COMPTE L'ORIENTATION DE LA CAMERA
		//TODO PRENDRE EN COMPTE L'ORIENTATION DE LA CAMERA
		double y_offset=-.5  + 2./180.*game->player->theta;
		double z_offset=-1.5 - 5./180.*game->player->theta;
		game->arrows[game->arrow_count].x=-game->player->x + y_offset*sin(game->player->phi/360*2*PI);
		game->arrows[game->arrow_count].y=-game->player->y + y_offset*cos(game->player->phi/360*2*PI);
		game->arrows[game->arrow_count].z=-game->player->z + z_offset;

		// printf("%lf\n",game->player->theta);
		// printf("%lf\n",random(0,1));

		// game->arrows[game->arrow_count].dx=30*cos(-game->player->phi/360*2*PI)*(1-1.6*fabs(sin(-game->player->theta/360*2*PI)))*random(.8,.4) + 30*sin(game->player->phi/360*2*PI)*random(.8,.4);
		// game->arrows[game->arrow_count].dy=30*sin(-game->player->phi/360*2*PI)*(1-1.6*fabs(sin(-game->player->theta/360*2*PI)))*random(.8,.4) + 30*cos(game->player->phi/360*2*PI)*random(.8,.4);
		game->arrows[game->arrow_count].dx=30*cos(-game->player->phi/360*2*PI)*(1-1.6*fabs(sin(-game->player->theta/360*2*PI)))*random(.85,.3) + 30*sin(game->player->phi/360*2*PI-180)*random(-.015,.1);
		game->arrows[game->arrow_count].dy=30*sin(-game->player->phi/360*2*PI)*(1-1.6*fabs(sin(-game->player->theta/360*2*PI)))*random(.85,.3) + 30*cos(game->player->phi/360*2*PI-180)*random(-.015,.1);
		game->arrows[game->arrow_count].dz=-20*sin(-game->player->theta/180*PI);
		// game->arrows[game->arrow_count].dz=10;

		game->arrow_count+=1;
		game->fire_value=0;
	}else{
		// printf("fire failed \n");
	}
}

void game_pause(Game * game,int state){
	if(state){
		//TODO PAUSE MUSIC
	}else{
		//TODO UNPAUSE MUSIC
	}
}

void trigger(Game* game,int state){
	game->trigger_state=state;
	// if(state)
	// 	printf("trigger_ON\n");
	// else
	// 	printf("trigger_OFF\n");
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
	trigger_value_MAX[2]=200;
	fire_value_MAX[2]   =10;

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
	game->fire_value=1;
	game->weapon=0;

	game->arrow_count=0;
	game->mechant_count=0;
	game->arrow_limit=1;
	game->mechant_limit=1;
	game->arrows=malloc(sizeof(Arrow)*game->arrow_limit);
	game->mechants=malloc(sizeof(Mechant)*game->arrow_limit);
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

//==================================================================
//                                                                    
//  _|        _|_|_|_|  _|      _|  _|_|_|_|  _|              _|_|    
//  _|        _|        _|      _|  _|        _|            _|    _|  
//  _|        _|_|_|    _|      _|  _|_|_|    _|                _|    
//  _|        _|          _|  _|    _|        _|              _|      
//  _|_|_|_|  _|_|_|_|      _|      _|_|_|_|  _|_|_|_|      _|_|_|_|  
//                                                                    
//==================================================================
//==================================================================
//==================================================================
void ingame_level2_update(Game* game,int dt);
void ingame_level2_render(Game* game);
//==================================================================
//                                                                    
//  _|        _|_|_|_|  _|      _|  _|_|_|_|  _|            _|_|_|    
//  _|        _|        _|      _|  _|        _|                  _|  
//  _|        _|_|_|    _|      _|  _|_|_|    _|              _|_|    
//  _|        _|          _|  _|    _|        _|                  _|  
//  _|_|_|_|  _|_|_|_|      _|      _|_|_|_|  _|_|_|_|      _|_|_|    
//                                                                    
//==================================================================
//==================================================================
//==================================================================
void ingame_level3_update(Game* game,int dt);
void ingame_level3_render(Game* game);
//==================================================================
//                                                                    
//  _|        _|_|_|_|  _|      _|  _|_|_|_|  _|            _|  _|    
//  _|        _|        _|      _|  _|        _|            _|  _|    
//  _|        _|_|_|    _|      _|  _|_|_|    _|            _|_|_|_|  
//  _|        _|          _|  _|    _|        _|                _|    
//  _|_|_|_|  _|_|_|_|      _|      _|_|_|_|  _|_|_|_|          _|    
//                                                                    
//==================================================================
//==================================================================
//==================================================================
void ingame_level4_update(Game* game,int dt);
void ingame_level4_render(Game* game);
