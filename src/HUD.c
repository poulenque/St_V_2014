#include "HUD.h"
#include "draw.h"
#include "constants.h"
#include <math.h>


void empty_HUD(Game* game){}

void HUD(Game* game){
	if(game->weapon==0){

	}
	if(game->weapon==1){
		bow_HUD(game);
	}
}

double HUD_drho_compensation=0;
double fake_rho=0;
double fake_drho=0;
double fake_theta=0;

double fake_HUD_drho_compensation=0;

double fake_walking=0;

void fake_walk_update(Game* game,int dt){
	// fake_drho+=fake_walking*70*sin(PI+PI/2*cos(SDL_GetTicks()*.008))/4.;

	for(int i=0;i<dt;i++){
		fake_drho+=fake_walking*2*cos(SDL_GetTicks()*.008)*cos(SDL_GetTicks()*.008)*cos(SDL_GetTicks()*.008);
		// fake_drho+=fake_walking*2*cos(time_*.12)*cos(time_*.12)*cos(time_*.12);
	
		//================================================
		fake_drho+=-.013*fake_drho;
		fake_theta+=  -.01*fake_theta;
		fake_rho  +=.001*fake_drho -.03*fake_rho ;
	
		fake_HUD_drho_compensation=
							(.2)* fake_drho*(.3) 
							+ (1-.2)*fake_HUD_drho_compensation;

		HUD_drho_compensation= (.02)* game->player->drho*(.3) 
							+ (1-.02)*HUD_drho_compensation;
	}
}

void bow_HUD(Game* game){
	//TODO
	if(game->fire_value==1){
		weapon_HUD_ARM(game);
	}else{
		weapon_HUD_FIRE(game);
	}
}

void viseur(Game * game){
	fake_walking=
		 game->player->dx*game->player->dx
		+game->player->dy*game->player->dy
		+game->player->dz*game->player->dz;
	fake_walking=sqrt(fake_walking);
	fake_walking*=0.007;
	/////////////////////////////////////////////////////////////////////
	glPushMatrix();
		glColor4d(1,0,0,1);
		glPointSize(2.);

		glRotated(game->player->rho*(-2),1,0,0);
		glRotated(game->player->theta*.5, 0.0, 1.0, 0.0);

		glEnable(GL_POINT_SMOOTH);
		glPointSize(6.);

		glBegin(GL_POINTS);
			glVertex3d(.05,.003,0);
			glVertex3d(.05,-.003,0);	glVertex3d(.05,0,0);	glVertex3d(.05,0,.003);
			glVertex3d(.05,0,-.003);
		glEnd();
		glDisable(GL_POINT_SMOOTH);

	glPopMatrix();
}

//==========================================
//==========================================
//==========================================
#define BOW_GL_MATRIX() \
	fake_walking=\
		 game->player->dx*game->player->dx\
		+game->player->dy*game->player->dy\
		+game->player->dz*game->player->dz;\
	fake_walking=sqrt(fake_walking);\
	fake_walking*=0.007;\
	double real_rho=game->player->rho    +fake_rho;\
	double real_theta=game->player->theta+fake_theta;\
	glRotated(real_rho*(-4),1,0,0);\
	glRotated(real_theta*.5, 0.0, 1.0, 0.0);\
	double real_HUD_drho_compensation=HUD_drho_compensation+fake_HUD_drho_compensation;\
	glTranslated(0,0,-real_HUD_drho_compensation*real_HUD_drho_compensation*0.0007);\
	glTranslated(5,0,-3);\
	glTranslated(real_theta*(.05),0,0);\
	glRotated(80, 0, 1, 0);\
	glRotated(70, 1, 0, 0);\
	glRotated(real_theta*(1),0,0,1);\
	glRotated(real_HUD_drho_compensation,0,1,0);\
	glTranslated(0,0,-1);\
	glLineWidth(3.0)
//==========================================
//==========================================
//==========================================

void weapon_HUD_ARM(Game* game){

	viseur(game);
	double time_pos=game->trigger_value;

	double oscill_force=.5*sin(SDL_GetTicks()*.001)+.5*sin(SDL_GetTicks()*.00085);

	glPushMatrix();
	BOW_GL_MATRIX();
			#define TEMP_MACRO() \
			glTranslated(0, 1.5*time_pos, 2*time_pos);\
			glRotated(-130*.5*time_pos, 0, 1, 0);\
			glRotated(-30*.5*time_pos, 0, 0, 1);

			glPushMatrix();
				TEMP_MACRO();

				//ARROW
				glRotated(60+30*time_pos, 0, 1, 0);
				glRotated(60+30*time_pos, 1, 0, 0);
				// glTranslated(
				// 	-.3+.1*sin(SDL_GetTicks()*.0017*(1-time_pos)),
				// 	1-.7*time_pos,
				// 	-5+1*oscill_force*(1-time_pos)+2*time_pos
				// 	);
				glTranslated(
					-.3+.1*sin(SDL_GetTicks()*.0017)*(1-time_pos)-.7*time_pos,
					1-.8*time_pos,
					-5+1*oscill_force*(1-time_pos)+2*time_pos
					);

				glScaled(1,1,1+.2*time_pos);
				draw_arrow(.2);
				glClear(GL_DEPTH_BUFFER_BIT);

			glPopMatrix();

			TEMP_MACRO();
			if(time_pos){//stable hands
				draw_hand(.3*time_pos,2*time_pos,TRUE);
				draw_bow(.2,.2+.6*time_pos);
			}else{//shaking hands
				draw_hand(  .3+.1*oscill_force,0,FALSE);
				draw_bow(.2,.2+.1*oscill_force);
			}

			#undef TEMP_MACRO


	// glTranslated(                               0, 1, -5+1*oscill_force);
	// glTranslated(-.3+.1*sin(SDL_GetTicks()*.0017), 0, 0);

	// draw_arrow(.2);
	glPopMatrix();
}


void weapon_HUD_FIRE(Game* game){
	viseur(game);


	glPushMatrix();
	BOW_GL_MATRIX();

	double time_pos=game->fire_value;
	double force=	time_pos*.5+.5;

	//FIRE
	if(force<.55){
	// else {

		//force entre 0 et 1
		force=(force-.5)/.05;
		//force exp entre 0 et 1
		force=(exp( 1-force )-1)/(exp(1)-1);

		// double force=.5*((int)(time_/.15)%152)/152.;

		glTranslated(1*force, 1.5-1+1*force, 2.5);
		glRotated(-130*.5, 0, 1, 0);
		glRotated(-30*.5, 0, 0, 1);
		glRotated(10, 0, 1, 0);

		draw_hand(.5*force,2.+2-2*force,TRUE);
		draw_bow(.2,.5*force);

		//ARROW
		glRotated(90, 0, 1, 0);
		glRotated(90, 1, 0, 0);
		glRotated(3, 1, 0, 0);
		glTranslated(0,.3,-8+5*force);

		draw_arrow(.2);


	}else if(force<.65){
		//force entre 0 et 1
		force=(force-.55)/.1;

		// double force=.5*((int)(time_/.15)%152)/152.;

		glTranslated(0, 1.5-1, 2.5);
		glRotated(-130*.5, 0, 1, 0);
		glRotated(-30*.5, 0, 0, 1);
		glRotated(10, 0, 1, 0);

		glRotated(-40*force, 1, 0, 0);
		// glRotated(-40*force, 0, 0, 1);


		glTranslated(0, 0, -3*force);

		draw_hand(0,2.+2,TRUE);
		draw_bow(.2,0);


	}else{

		//force entre 0 et 1
		force=(force-.65)/.25;

		// double force=.5*((int)(time_/.15)%152)/152.;

		glTranslated(0, 1.5-1, 2.5);
		glRotated(-130*.5, 0, 1, 0);
		glRotated(-30*.5, 0, 0, 1);
		glRotated(10, 0, 1, 0);

		glRotated(-40, 1, 0, 0);

		glTranslated(0, 0, -3*force);
		glRotated(20*force, 0, 1, 0);

		// glTranslated(-2*force, 0, 2*force);

		// glRotated(-20*force, 0, 1, 1);

		glRotated(40*force, 1, 1, 0);

		glTranslated(0, 0, -3);

		draw_hand(0,2.+2-2*force,TRUE);
		draw_bow(.2,0);

		//ARROW
		// glRotated(90, 0, 1, 0);
		// glRotated(90, 1, 0, 0);
		// glRotated(3, 1, 0, 0);
		// glTranslated(0,.3,-8);

		// draw_arrow(.2);

	}


	glPopMatrix();
}



























