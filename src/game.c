#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
// #include <GL/freeglut.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "string3d.h"
#include "constants.h"
#include <math.h>
#include "shader.h"
#include "draw.h"
// #include <GL/glew.h>

double time_=0;

void intro_update(Game* game,int dt);
void intro_render(Game* game);

void ingame_update(Game* game,int dt);
void ingame_render(Game* game);

static String3d* str;

static double messages_x[200];
static double messages_y[200];
static double messages_z[200];
static double messages_z_exp_offset[200];
static double messages_z_exp_speed[200];
static double messages_dephasage[200];

//creer un texture vide
//creer frame buffer -> bind -> dessine -> unbind


//1 texture pour couleur
//1 texture depth
//1 frame buffer -> attacher les 2 textures

//rendre une fois dans le framebuffer

//rendre un carre de la taille de l'ecran

//fragmenet shader -> fx qui donne la couleur du pixel a partir de x,y



// unsigned int
// lr_texture_depthmap (int width, int height)
// {
//     unsigned int tex_id;

//     glGenTextures (1, &tex_id);

//     glBindTexture (GL_TEXTURE_2D, tex_id);

//     glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//     glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//     glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//     glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

//     glTexImage2D (GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);

//     glBindTexture (GL_TEXTURE_2D, 0);

//     return tex_id;
// }



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
	//openGL INITIALIZATION
	// glClearColor(0.03/2, 0.16/2, 0.18/2, 0.0);

	glEnable(GL_DEPTH_TEST);
	glEnable (GL_BLEND);
	glDisable(GL_CULL_FACE);

	glEnable(GL_TEXTURE_2D);

	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_POINT_SMOOTH);
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


	glDisable( GL_LINE_SMOOTH );
	// //glEnable( GL_POLYGON_SMOOTH );
	// //glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
	// glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );

	Game* game = malloc(sizeof(Game));
	game->update=intro_update;
	game->render=intro_render;
	game->player=player;

	// glGenFramebuffers (1, &game->frame_buffer_id);
	// game->depth_tex_id=lr_texture_depthmap (800,600);

	game->shader_id_dummy=shader_createProgram("dummy");
	game->shader_id_dof=shader_createProgram("dof");
	glGenFramebuffers(1,& (game->frame_buffer_id));

	glGenTextures (1, &(game->depth_tex_id));
	glBindTexture (GL_TEXTURE_2D, game->depth_tex_id);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 800, 600, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);


	glGenTextures (1, &(game->color_tex_id));
	glBindTexture (GL_TEXTURE_2D, game->color_tex_id);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	glBindTexture (GL_TEXTURE_2D, 0);

	game->shader_dof_color_id = glGetUniformLocation(game->shader_id_dof,"color");
	// glUniform4f (color_id, 1, 0, 0, 1);


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
		game->player->x=0;
		game->player->y=0;
		game->player->z=0;
		game->player->phi=0;
		game->player->theta=0;
		game->player->rho=0;

		time_=0;

		glClearColor( 1.f, 1.f, 1.f, 1.f );
		game->render=ingame_render;
		game->update=ingame_update;
		//TODO -> send signal to quit music loop
		//and also something that play that music :¬P
	}
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	// // glFramebufferTexture2D (GL_FRAMEBUFFER, GL_DEPTH_COMPONENT, GL_TEXTURE_2D, game->depth_tex_id, 0);

	// glUseProgram(game->shader_id_dummy);
	// glFramebufferTexture2D(game->frame_buffer_id,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,game->color_tex_id,0);
	// // glFramebufferTexture2D(game->frame_buffer_id,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,game->depth_tex_id,0);

	// glBindFramebuffer(GL_FRAMEBUFFER,game->frame_buffer_id);

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

	// // SDL_Surface * image = IMG_Load("screenshot/01.png");
	// // glTexImage2D (GL_TEXTURE_2D, 0, 3,
	// // 	image->w, image->h, 0,
	// // 	GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

	// glBindFramebuffer(GL_FRAMEBUFFER,0);
	// glUseProgram(game->shader_id_dof);
	// glActiveTexture (GL_TEXTURE0);
	// glBindTexture (GL_TEXTURE_2D, game->color_tex_id);
	// // glBindTexture (GL_TEXTURE_2D, game->depth_tex_id);
	// glUniform1i(game->shader_dof_color_id,GL_TEXTURE0);


	// glBegin( GL_QUADS );
	// 	glVertex2d(-1,-1);
	// 	glVertex2d(-1, 1);
	// 	glVertex2d( 1, 1);
	// 	glVertex2d( 1,-1);
	// glEnd();


}



void ingame_update(Game* game,int dt){
	camera_update(game->player,dt);
	time_+=dt/15.;
}
void ingame_render(Game* game){
	
	//TODO !!

	// //distace player begin square
	// double x_temp=(game->player->x+200);
	// double y_temp=(game->player->y-0);
	// double z_temp=(game->player->z-0);

	// x_temp*=x_temp;//square
	// y_temp*=y_temp;//square
	// z_temp*=z_temp;//square

	// double d= (sqrt(x_temp+y_temp+z_temp))*.01;
	// printf("%lf\n",d);


	// glClearColor(d,d,d,1);

	glColor4d(0,0,0,1);
	double size=10;
	glPushMatrix();
		glTranslated(-10,0,0);
		draw_face(size,.1);
	glPopMatrix();

	glColor4d(0,0,0,exp(-time_/50.));
	glPushMatrix();
		glTranslated(200,0,size*2-exp(6-time_/50.));
		// glRotated(-45,0,0,1);
		draw_cube(size,.1);
	glPopMatrix();

	glColor4d(0,0,0,1);
	glPushMatrix();
		glTranslated(200,0,-size*2+exp(6-time_/50.));
		// glRotated(-45,0,0,1);
		draw_cube(size,.1);
	glPopMatrix();




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
	for(int i=0;i<10;i++){
		glColor4d(0,0,0,1);
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
	// for(int i=0;i<10;i++){
	// 	glTranslated(10,0,0);
	// 	draw_guy(time_,((int)time_%20)*.02);
	// }
	//
	glPopMatrix();

}
