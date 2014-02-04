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

//===============================================================
//                                                      
//  _|_|_|_|    _|_|    _|      _|  _|_|_|_|_|          
//  _|        _|    _|  _|_|    _|      _|          _|  
//  _|_|_|    _|    _|  _|  _|  _|      _|              
//  _|        _|    _|  _|    _|_|      _|              
//  _|          _|_|    _|      _|      _|          _|  
//                                                      
//===============================================================
//http://patorjk.com/software/taag/#p=display&f=Block&t=LEVEL%202
//===============================================================

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
void ingame_level4_update(Game* game,int dt);
void ingame_level4_render(Game* game);

static String3d* str;

static double messages_x[200];
static double messages_y[200];
static double messages_z[200];
static double messages_z_exp_offset[200];
static double messages_z_exp_speed[200];
static double messages_dephasage[200];

void empty_HUD(Game* game){
	// glColor4d(1,0,0,1);
	// glPointSize(2.);
	// glBegin(GL_POINTS);
	// 	glVertex3d(.05,.003,0);
	// 	glVertex3d(.05,-.003,0);	glVertex3d(.05,0,0);	glVertex3d(.05,0,.003);
	// 	glVertex3d(.05,0,-.003);
	// glEnd();
}


double HUD_drho_compensation=0;

void weapon_HUD(Game* game){
	glPushMatrix();
	glColor4d(1,0,0,1);
	glPointSize(2.);

	glRotated(game->player->rho*(-4),1,0,0);
	glRotated(game->player->theta*.5, 0.0, 1.0, 0.0);
	// glRotated(game->player->phi, 0.0, 0.0, 1.0);

	glBegin(GL_POINTS);
		glVertex3d(.05,.003,0);
		glVertex3d(.05,-.003,0);	glVertex3d(.05,0,0);	glVertex3d(.05,0,.003);
		glVertex3d(.05,0,-.003);
	glEnd();



	// glTranslated(0,0,10);

	HUD_drho_compensation= (.2)* game->player->drho*(.3) 
                         + (1-.2)*HUD_drho_compensation;

	glTranslated(5,0,-3);
	// glRotated(45, 0, 0, 1);
	// glTranslated(game->player->theta*(-.05),0,game->player->theta*(.05));
	glTranslated(game->player->theta*(.05),0,0);

	// glRotated(45, 0, 1, 0);
	glRotated(80, 0, 1, 0);
	glRotated(70, 1, 0, 0);

	// glRotated(game->player->theta*(-4),0,1,0);


	glRotated(game->player->theta*(1),0,0,1);
	// printf("%lf\n",game->player->rho);


	glRotated(HUD_drho_compensation,0,1,0);
	// glRotated(game->player->theta*(2),1,0,0);

	glLineWidth(3.0);

	draw_bow(.2,.5+.1*sin(time_*.02));

	draw_arrow(.2);

	// draw_bow(.2,.5+.5*cos(PI*sin(time_*.05)));
	// draw_bow(.2,0);
	glPopMatrix();

}


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

	game->HUD_render=empty_HUD;

	//===========================
	//THIS IS FOR TESTING PURPOSE
	//===========================
	// glClearColor( 1., 1., 1., 1. );
	// game->HUD_render=weapon_HUD;
	// game->update=ingame_level1_update;
	// game->render=ingame_level1_render;
	//===========================
	//===========================


	return game;
}

//==================================================================
//                                                                    
//  _|_|_|  _|      _|  _|_|_|_|_|  _|_|_|      _|_|          _|_|    
//    _|    _|_|    _|      _|      _|    _|  _|    _|      _|    _|  
//    _|    _|  _|  _|      _|      _|_|_|    _|    _|      _|_|_|_|  
//    _|    _|    _|_|      _|      _|    _|  _|    _|      _|    _|  
//  _|_|_|  _|      _|      _|      _|    _|    _|_|        _|    _|  
//                                                                    
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
		game->player->x=200;
		game->player->y=0;
		game->player->z=0;
		if(game->player->avance==-1)
			game->player->phi  =0;
		else
			game->player->phi  =180;
		game->player->theta=0;
		game->player->rho  =0;

		time_=0;

		glClearColor( 1.f, 1.f, 1.f, 1.f );
		game->update=intro_get_weapon_update;
		game->render=intro_get_weapon_render;

		glEnable(GL_FOG);

		GLfloat fogColor[4]= {1,1, 1, 1};
		glFogi(GL_FOG_MODE, GL_LINEAR);//GL_EXP, GL_EXP2, GL_LINEAR
		glFogf(GL_FOG_START, 700);
		glFogf(GL_FOG_END, 1000);

		// glFogi(GL_FOG_MODE, GL_EXP);//GL_EXP, GL_EXP2, GL_LINEAR
		// glFogi(GL_FOG_MODE, GL_EXP2);//GL_EXP, GL_EXP2, GL_LINEAR
		// glFogf(GL_FOG_START, 2000);
		// glFogf(GL_FOG_END, 3000);

		glFogfv(GL_FOG_COLOR, fogColor);
		glFogf(GL_FOG_DENSITY, 0.35f);
		glHint(GL_FOG_HINT, GL_DONT_CARE);

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
//                                                                    
//  _|_|_|  _|      _|  _|_|_|_|_|  _|_|_|      _|_|        _|_|_|    
//    _|    _|_|    _|      _|      _|    _|  _|    _|      _|    _|  
//    _|    _|  _|  _|      _|      _|_|_|    _|    _|      _|_|_|    
//    _|    _|    _|_|      _|      _|    _|  _|    _|      _|    _|  
//  _|_|_|  _|      _|      _|      _|    _|    _|_|        _|_|_|    
//                                                                    
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
		game->player->x=0;
		game->player->y=0;
		game->player->z=0;
		game->player->theta=0;
		game->player->phi  =0;
		game->player->rho  =0;
		game->update=ingame_level1_update;
		game->render=ingame_level1_render;
		game->HUD_render=weapon_HUD;

		time_=0;

		glEnable(GL_FOG);

		GLfloat fogColor[4]= {1,1, 1, 1};
		glFogi(GL_FOG_MODE, GL_LINEAR);//GL_EXP, GL_EXP2, GL_LINEAR
		glFogf(GL_FOG_START, 20);
		glFogf(GL_FOG_END, 300);

		// glFogi(GL_FOG_MODE, GL_EXP);//GL_EXP, GL_EXP2, GL_LINEAR
		// glFogi(GL_FOG_MODE, GL_EXP2);//GL_EXP, GL_EXP2, GL_LINEAR
		// glFogf(GL_FOG_START, 2000);
		// glFogf(GL_FOG_END, 3000);

		glFogfv(GL_FOG_COLOR, fogColor);
		glFogf(GL_FOG_DENSITY, 0.35f);
		glHint(GL_FOG_HINT, GL_DONT_CARE);

	}
}
void intro_get_weapon_render(Game* game){


	// glClearColor(d*.01,d*.01,d*.01,1);

	double d= game->shared_var1;

	glColor4d(0,0,0,1);
	double size=10;

	glPushMatrix();
		glColor4d(
			1-exp(2.5-time_*0.05),
			1-exp(2.5-time_*0.05),
			1-exp(2.5-time_*0.05),
			1);
		glTranslated(-210-exp(time_*0.05),0,0);
		// draw_face(100*(1-exp(-time_*0.05)),.1);
		draw_face(30,.1);
	glPopMatrix();

	// glColor4d(0,0,0,exp(-time_/50.));
	// glPushMatrix();
	// 	glTranslated(200,0,size*2-exp(6-time_/50.));
	// 	// glRotated(-45,0,0,1);
	// 	draw_cube(size,.1);
	// glPopMatrix();

	// glColor4d(0,0,0,1);
	double dd=d;
	if (d>1/0.02) dd=1/.02;
	glColor4d(0,0,0,(1-exp(-time_/100.))*dd*.02);
	glPushMatrix();
		glTranslated(200,0,-size*2+exp(6+1-time_/50.));
		// glRotated(-45,0,0,1);
		draw_cube(size,.1);

		glTranslated(0,0,size*2);
		glPushMatrix();
		glRotated(time_,0,0,1);
		glRotated(45,45,0,1);
		glColor4d(1,0,0,1);
		draw_bow(.4,0);
		glPopMatrix();

	glPopMatrix();

	// glColor4d(1,0,0,1);
	// draw_bow(0,.5+.5*cos(PI*cos(time_*.1)));

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
	// glColor4d(0,0,0,1-exp(-time_/100.));
	glColor4d(0,0,0,(1-exp(-time_/100.))*dd*.02);
	for(int i=0;i<10;i++){
		string3d_setTxt(str,"go accomplish your mission");
		str->size=1.12 + .15*(1+cos (time_*.1+i));
		str->dist=7.15 + 1+cos (time_*.1+i);
		str->x=200;
		str->y=0;
		str->z=-.5+exp(6+1-time_/50.)+i*2 -30+1;
		str->phi=time_*.75+i*40;
		string3d_draw(str);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslated(20,20,0);
	glColor4d(1,0,0,1);
	//
	//NOISE SHOULD BE CONTROLLED BY SOUND
	glColor4d(0,0,0,1);
	// draw_gentil(time_,((int)time_%100)*.02,2);
	// draw_gentil(time_,(1+cos(time_*.1) )*(100-(int)time_%100)*.01,2);
	// draw_gentil(time_,(1+cos(time_*.1) ),2);

	// draw_gentil(time_,2*(100-(int)time_%100)*.01,2);
	// for(int i=0;i<200;i++){
	// 	glPushMatrix();
	// 		glRotated(i*10,0,0,1);
	// 		glTranslated(0,1*i,0);
	// 		draw_gentil(time_,2*i/200.,2);
	// 	glPopMatrix();
	// }
	// glTranslated(0,5,0);
	// draw_gentil(time_,0,2);

	// draw_wing(time_,0,10);

	// glColor4d(0,0,0,1);
	// for(int i=0;i<100;i++){
	// 	glTranslated(10,0,0);
	// 	draw_gentil(time_,((int)time_%20)*.02,2);
	// }

	// for(int i=0;i<500;i++){
	// 	glTranslated(10,0,0);
	// 	draw_gentil(time_,((int)time_%20)*.02,1);
	// }
	//
	glPopMatrix();

	// glScaled(-1,-1,1);
	// glColor4d(0,1,0,1);
	// string3d_setTxt(str,"abcdefghijklmnopqrstuvwxyz1234567890");
	// str->size=1;
	// str->dist=10;
	// str->z=-.5;
	// str->phi=0;
	// string3d_draw(str);

}
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
void ingame_level1_update(Game* game,int dt){
	camera_update(game->player,dt);
	time_+=dt/15.;
}
void ingame_level1_render(Game* game){


	// for(int i=0;i<200;i++){
	// 	glPushMatrix();
	// 		// glRotated(i*10,0,0,1);
	// 		// glTranslated(0,1*i,0);
	// 		draw_gentil(time_,2*i/200.,2);
	// 	glPopMatrix();
	// }
	// for(int i=200;i<800;i++){
	// 	glPushMatrix();
	// 		glRotated(i*10,0,0,1);
	// 		glTranslated(0,1*i,0);
	// 		draw_gentil(time_,2*i/200.,1);
	// 	glPopMatrix();
	// }


	for(int i=-100;i<100;i++){
		for(int j=-100;j<100;j++){
			glPushMatrix();
				glTranslated(20*i,20*j,20*exp(-time_*.07));
				// draw_gentil(time_,4*(i+j)/200.,2);

				double x_guy=20*i;
				double y_guy=20*j;
				// double alpha = atan((x_guy+game->player->x)/(y_guy+game->player->y))*180./PI;
				double alpha = atan2((y_guy+game->player->y),(x_guy+game->player->x))*180./PI;

				alpha = alpha+game->player->phi;
				while(alpha<=0)
					alpha+=360;
				while(alpha>360)
					alpha-=360;

				int angle=55;

				if(
					 (alpha <angle||alpha>360-angle)
					){
					double dist=(x_guy+game->player->x)*(x_guy+game->player->x)+(y_guy+game->player->y)*(y_guy+game->player->y);

					if(dist<20*20*20)
						draw_gentil(2*(100-(int)time_%100)*.01,2);
					else if(dist<50*20*20)
						draw_gentil(2*(100-(int)time_%100)*.01,1);
					else if(dist<600*20*20)
						draw_gentil(2*(100-(int)time_%100)*.01,0);
				}
			glPopMatrix();
		}
	}


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
