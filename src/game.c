#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "string3d.h"
#include "constants.h"
#include <math.h>
#include "shader.h"
#include "draw.h"

double time_=0;

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
void ingame_level3_update(Game* game,int dt);
void ingame_level3_render(Game* game);

static String3d* str;

static double messages_x[200];
static double messages_y[200];
static double messages_z[200];
static double messages_z_exp_offset[200];
static double messages_z_exp_speed[200];
static double messages_dephasage[200];

Game* initGame(Camera* player){

	draw_init();

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

	glDisable(GL_POINT_SMOOTH);
	glDisable( GL_LINE_SMOOTH );

	// glEnable(GL_LIGHTING);
	// glEnable(GL_LIGHT0);

	// glEnable(GL_AUTO_NORMAL);
	// glEnable(GL_NORMALIZE);
	// glDepthFunc(GL_LESS);

	// //glEnable( GL_POLYGON_SMOOTH );
	// //glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
	// glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );

	Game* game = malloc(sizeof(Game));
	game->update=intro_update;
	game->render=intro_render;
	game->player=player;



	return game;
}

//==================================================================
//==================================================================
//==================================================================
void intro_update(Game* game,int dt){
	time_+=dt/15.;
	camera_update(game->player,dt);

	//distace player begin sphere
	double x_temp=(game->player->x+20);
	double y_temp=(game->player->y-0);
	double z_temp=(game->player->z-0);

	x_temp*=x_temp;//square
	y_temp*=y_temp;//square
	z_temp*=z_temp;//square

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!GET INTO START ZONE, LETS BEGIN !!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if(x_temp+y_temp+z_temp<5*5){
		game->player->x=0;
		game->player->y=0;
		game->player->z=0;
		game->player->phi=0;
		game->player->theta=0;
		game->player->rho=0;

		time_=0;

		glClearColor( 1.f, 1.f, 1.f, 1.f );
		game->update=intro_get_weapon_update;
		game->render=intro_get_weapon_render;
	}
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void intro_render(Game* game){



	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(20,0,0);

		glColor4d(1,1,1,1);

		draw_sphere2(5,time_,0);

		//====================================================
		string3d_setTxt(str,"     a game by    \n\nLaurent Rohrbasser");

		glRotated(53,0,0,1);

		glColor4d(1,1,1,1);
		str->size=1;
		str->dist=15;
		str->z=15;
		string3d_draw(str);

		for(int i=1;i<50;i++){
			str->dist=15+i;
			str->size=1+i/15.;
			str->z=15+i*.5;
			double k=exp(-i/5.)/1.5;
			glColor4d(k,k,k,1);
			string3d_draw(str);
		}
		//====================================================

		string3d_setTxt(str,"  ENTER to begin  \n");


		glColor4d(1,1,1,1);
		str->size=1;
		str->dist=15;
		str->z=-15;
		string3d_draw(str);

		for(int i=1;i<50;i++){
			str->dist=15+i;
			str->size=1+i/15.;
			str->z=-15-i*.5;
			double k=exp(-i/5.)/1.5;
			glColor4d(k,k,k,1);
			string3d_draw(str);
		}

		//====================================================

		double k=rand()*1./RAND_MAX;
		k*=0.5;
		glScaled(-1,1,1);
		glColor4d(k,k,k,1);
		string3d_setTxt(str,"music > gopho by goto80 >>>>> music > gopho by goto80 >>>>> ");
		str->size=.5;
		str->dist=7.15;
		str->z=-.25;
		str->phi=time_*.75;
		string3d_draw(str);
		str->phi=0;

	glPopMatrix();
}


//==================================================================
//==================================================================
//==================================================================
void intro_get_weapon_update(Game* game,int dt){
	camera_update(game->player,dt);
	time_+=dt/15.;

	//distace player begin square
	double x_temp=(game->player->x+200);
	double y_temp=(game->player->y-0);
	double z_temp=(game->player->z-0);

	x_temp*=x_temp;//square
	y_temp*=y_temp;//square
	z_temp*=z_temp;//square

	double d= (sqrt(x_temp+y_temp+z_temp));

	game->shared_var1=d;

	if(d<5){
		// MUSIC QUIT LOOP
		// GOTO LEVEL 1 !
	}
}
void intro_get_weapon_render(Game* game){


	// glClearColor(d*.01,d*.01,d*.01,1);

	double d= game->shared_var1;

	glColor4d(0,0,0,1);
	double size=10;
	// glPushMatrix();
	// 	glTranslated(-10,0,0);
	// 	draw_face(size,.1);
	// glPopMatrix();

	// glColor4d(0,0,0,exp(-time_/50.));
	// glPushMatrix();
	// 	glTranslated(200,0,size*2-exp(6-time_/50.));
	// 	// glRotated(-45,0,0,1);
	// 	draw_cube(size,.1);
	// glPopMatrix();

	// glColor4d(0,0,0,1);
	glColor4d(0,0,0,1-exp(-time_/100.));
	glPushMatrix();
		glTranslated(200,0,-size*2+exp(6-time_/50.));
		// glRotated(-45,0,0,1);
		draw_cube(size,.1);
	glPopMatrix();


	for(int i=1;i<50;i++){
		// glColor4d(0,0,0,(1-exp(-time_/100.)) * (d/200.) );
		double v= (2-d/200.) ;
		if(v<.2)
			v=.2;
		glColor4d(0,0,0,v*(1-exp(-time_/400.)) * (1-i/50.) *(d/200.) );
		glPushMatrix();
			glTranslated(200,0,-size*i*1.1*(1+exp(-time_/50.))-200*exp(-time_/50.) - size);
			glRotated((i-1)*(time_*.1),0,0,1);
			draw_cube(size*i,.1/i);
		glPopMatrix();
	}





	// glPushMatrix();
	// glScaled(1,-1,1);
	// for(int i=0;i<50;i++){
	// 	string3d_setTxt(str,"go accomplish your mission");
	// 	str->size=2;
	// 	str->dist=15;

	// 	str->x=100+200.*messages_x[i];
	// 	str->y=100-200.*messages_y[i];
	// 	str->z=15-30.*messages_z[i]+exp(6+1.*messages_z_exp_offset[i]-time_/50.*messages_z_exp_speed[i]);
	// 	str->phi=time_*.75+360.*messages_dephasage[i];

	// 	glColor4d(0,0,0,.5*exp(6-time_/50.*messages_z_exp_speed[i]));
	// 	string3d_draw(str);
	// }
	// glPopMatrix();

	glPushMatrix();
	glScaled(1,-1,1);
	// glColor4d(0,0,0,1);
	glColor4d(0,0,0,1-exp(-time_/100.));
	for(int i=0;i<10;i++){
		string3d_setTxt(str,"go accomplish your mission");
		str->size=1.12 + .15*(1+cos (time_*.1+i));
		str->dist=7.15 + 1+cos (time_*.1+i);
		str->x=200;
		str->y=0;
		str->z=-.5+exp(6-time_/50.)+i*2 -30+1;
		str->phi=time_*.75+i*40;
		string3d_draw(str);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslated(20,20,0);
	glColor4d(1,0,0,1);
	//
	//NOISE SHOULD BE CONTROLLED BY SOUND
	// draw_guy(time_,((int)time_%20)*.02,10);

	// draw_wing(time_,0,10);

	// glColor4d(0,0,0,1);
	// for(int i=0;i<100;i++){
	// 	glTranslated(10,0,0);
	// 	draw_guy(time_,((int)time_%20)*.02,2);
	// }

	// for(int i=0;i<500;i++){
	// 	glTranslated(10,0,0);
	// 	draw_guy(time_,((int)time_%20)*.02,1);
	// }
	//
	glPopMatrix();

}
