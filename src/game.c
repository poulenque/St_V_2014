#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <SDL/SDL.h>
#include "string3d.h"
#include "constants.h"
#include <math.h>

double time_=0;

void intro_update(Game* game,int dt);
void intro_render(Game* game);

void ingame_update(Game* game,int dt);
void ingame_render(Game* game);

static String3d* str;

Game* initGame(Camera* player){
	str = new_string3d();
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glClearColor( 0.f, 0.f, 0.f, 1.f );
	//openGL INITIALIZATION
	// glClearColor(0.03/2, 0.16/2, 0.18/2, 0.0);

	glEnable(GL_DEPTH_TEST);
	glEnable (GL_BLEND);
	glDisable(GL_CULL_FACE);

	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_POINT_SMOOTH);
	// glEnable(GL_LIGHTING);
	// glEnable(GL_LIGHT0);

	// glEnable(GL_AUTO_NORMAL);
	// glEnable(GL_NORMALIZE);
	// glDepthFunc(GL_LESS);

	// GLfloat mod_ambt[] = {0.015, 0.062, 0.09, 0.0}; 
	// GLfloat local_view[] = {0.0F}; 
	// glDepthFunc(GL_LESS);
	// glLightModelfv(GL_LIGHT_MODEL_AMBIENT,mod_ambt); 
	// glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER,local_view); 


	// glEnable( GL_LINE_SMOOTH );
	// //glEnable( GL_POLYGON_SMOOTH );
	// //glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
	// glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );

	Game* game = malloc(sizeof(Game));
	game->update=intro_update;
	game->render=intro_render;
	game->player=player;
	return game;
}

void intro_update(Game* game,int dt){
	time_+=dt/15.;
	camera_update(game->player,dt);
}

void intro_render(Game* game){

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
		glClearColor( 1.f, 1.f, 1.f, 1.f );
		game->render=ingame_render;
		game->update=ingame_update;
		//TODO -> send signal to quit music loop
	}
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(20,0,0);

		GLUquadric* sphere=gluNewQuadric();
		glColor4d(1,1,1,1);
		glLineWidth(3.0);
		glPushMatrix();
		glRotated(8*time_,8*time_,8*time_,1);
			gluSphere(sphere,5,10,8);
		glPopMatrix();
		gluQuadricDrawStyle(sphere, GLU_LINE);

		glPushMatrix();
		glRotated(time_,2*time_,4*time_,1);
			gluSphere(sphere,5.15,10,8);
		glPopMatrix();

		glPushMatrix();
		glRotated(2*time_,3*time_,time_,1);
			gluSphere(sphere,5.25,10,8);
		glPopMatrix();

		glPushMatrix();
		glRotated(2*time_,2*time_,2*time_,1);
			gluSphere(sphere,5.5,10,8);
		glPopMatrix();

		glPushMatrix();
		glRotated(4.2*time_,3*time_,2*time_,1);
			gluSphere(sphere,5.75,10,8);
		glPopMatrix();

		glPushMatrix();
		glRotated(4*time_,5*time_,4*time_,1);
			gluSphere(sphere,6,10,8);
		glPopMatrix();

		gluDeleteQuadric(sphere);

		//====================================================
		// string3d_setTxt(str,"qwertyuiop asdfghjkl zxcvbnm\nqwertyuiop asdfghjkl zxcvbnm\nqwertyuiop asdfghjkl zxcvbnm\nqwertyuiop asdfghjkl zxcvbnm ");
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

	// // Render quad
	// glBegin( GL_QUADS );
	// 	glVertex2f( -0.5f+.1-.1*rand()/(double)RAND_MAX, -0.5f+.1-.1*rand()/(double)RAND_MAX );
	// 	glVertex2f(  0.5f+.1-.1*rand()/(double)RAND_MAX, -0.5f+.1-.1*rand()/(double)RAND_MAX );
	// 	glVertex2f(  0.5f+.1-.1*rand()/(double)RAND_MAX,  0.5f+.1-.1*rand()/(double)RAND_MAX );
	// 	glVertex2f( -0.5f+.1-.1*rand()/(double)RAND_MAX,  0.5f+.1-.1*rand()/(double)RAND_MAX );
	// glEnd();

}



void ingame_update(Game* game,int dt){
	camera_update(game->player,dt);
}
void ingame_render(Game* game){
	
	//TODO !!

	// // Render quad
	glColor4d(0,0,0,1);
	double size=10;
	glBegin( GL_QUADS );
		glVertex3d(0, -size+size*.1-size*.1*rand()/(double)RAND_MAX, -size+size*.1-size*.1*rand()/(double)RAND_MAX );
		glVertex3d(0,  size+size*.1-size*.1*rand()/(double)RAND_MAX, -size+size*.1-size*.1*rand()/(double)RAND_MAX );
		glVertex3d(0,  size+size*.1-size*.1*rand()/(double)RAND_MAX,  size+size*.1-size*.1*rand()/(double)RAND_MAX );
		glVertex3d(0, -size+size*.1-size*.1*rand()/(double)RAND_MAX,  size+size*.1-size*.1*rand()/(double)RAND_MAX );
	glEnd();

}
