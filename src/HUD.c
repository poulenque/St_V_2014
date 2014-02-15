#include "HUD.h"
#include "draw.h"
#include "constants.h"
#include <math.h>


void bow_HUD(Game* game, int mode,double time_offset);
void weapon_HUD_ARM(Game* game, int mode,double time_offset);
void weapon_HUD_FIRE(Game* game, int mode,double time_offset);
void sulfateuse_HUD(Game* game, int color,double time_offset);

void empty_HUD(Game* game){}


void HUD(Game* game){

	// glGetError();
	// for(int i=0;i<n;i++){
		// double time_offset=i*.004/n;
		double time_offset=0;
				if(game->weapon==0){

				}
				else if(game->weapon==1){
					bow_HUD(game,0,time_offset);
				}
				else if(game->weapon==2){
					sulfateuse_HUD(game,0,time_offset);
				}else if(game->weapon==3){
					sulfateuse_HUD(game,1,time_offset);
				}else if(game->weapon==4){
					bow_HUD(game,1,time_offset);
				}else if(game->weapon==5){
					bow_HUD(game,2,time_offset);
				}


	// 	if(i == 0)
	// 		glAccum(GL_LOAD, 1.0 / n);
	// 	else
	// 		glAccum(GL_ACCUM, 1.0 / n);

	// }
	// glAccum(GL_RETURN, 1.0);
	// if(glGetError()&GL_INVALID_OPERATION) {
	// 	// gl accum not avaiable
	// 	// printf("GLACCUM UNAVAIABLE\n");
	// 	n=1;
	// }


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

void bow_HUD(Game* game, int mode,double time_offset){
	//TODO
	if(game->fire_value<=0){
		weapon_HUD_ARM(game,mode,time_offset);
	}else{
		weapon_HUD_FIRE(game,mode,time_offset);
	}
}

static double precision=0;
void viseur(Game * game){
	if(SDL_GetMouseState( NULL, NULL )&SDL_BUTTON(1)
		||SDL_GetMouseState( NULL, NULL )&SDL_BUTTON(3)
		||SDL_GetKeyState(NULL)[SDLK_LALT]
		||SDL_GetKeyState(NULL)[SDLK_LCTRL]){
		precision=1;
	}else{
		precision=0;
	}

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
		glRotated(game->player->theta*(.5-precision*.8), 0.0, 1.0, 0.0);

		// glEnable(GL_POINT_SMOOTH);
		glPointSize(6.);

		glBegin(GL_POINTS);
			glVertex3d(.05,.003,0);
			glVertex3d(.05,-.003,0);	glVertex3d(.05,0,0);	glVertex3d(.05,0,.003);
			glVertex3d(.05,0,-.003);
		glEnd();
		// glDisable(GL_POINT_SMOOTH);

	glPopMatrix();
}


void weapon_HUD_ARM(Game* game,int mode,double time_offset){
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

	double time_pos=game->trigger_value+time_offset;


	viseur(game);

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
				draw_arrow_high_quality();
				if(mode){
					glPushMatrix();
						glTranslated(-1.7,0,1.5);
						glRotated(10,0,1,0);
						draw_arrow_high_quality();
					glPopMatrix();
					glPushMatrix();
						glTranslated(1.7,0,0.75);
						glRotated(-10,0,1,0);
						draw_arrow_high_quality();
					glPopMatrix();
					// glPushMatrix();
					// 	glTranslated(-1.3,0,1.7);
					// 	glRotated(10,0,1,0);
					// 	draw_arrow_high_quality();
					// glPopMatrix();
					// glPushMatrix();
					// 	glTranslated(1.3,0,1);
					// 	glRotated(-10,0,1,0);
					// 	draw_arrow_high_quality();
					// glPopMatrix();
				}if(mode==2){
					glPushMatrix();
						glTranslated(-3.2,0,3);
						glRotated(20,0,1,0);
						draw_arrow_high_quality();
					glPopMatrix();
					glPushMatrix();
						glTranslated(3.2,0,1.5);
						glRotated(-20,0,1,0);
						draw_arrow_high_quality();
					glPopMatrix();
				}
				glClear(GL_DEPTH_BUFFER_BIT);

			glPopMatrix();

			TEMP_MACRO();
			if(time_pos){//stable hands
				draw_hand(.3*time_pos,2*time_pos,TRUE);
				if(mode==2){
					draw_bow_v3(.2,.2+.6*time_pos);
				}else if(mode==1){
					draw_bow_v2(.2,.2+.6*time_pos);
				}else{
					draw_bow(.2,.2+.6*time_pos);
				}
			}else{//shaking hands
				draw_hand(  .3+.1*oscill_force,0,FALSE);
				if(mode==2){
					draw_bow_v3(.2,.2+.1*oscill_force);
				}else if(mode==1){
					draw_bow_v2(.2,.2+.1*oscill_force);
				}else{
					draw_bow(.2,.2+.1*oscill_force);
				}
					
					
			}

			#undef TEMP_MACRO


	// glTranslated(                               0, 1, -5+1*oscill_force);
	// glTranslated(-.3+.1*sin(SDL_GetTicks()*.0017), 0, 0);

	// draw_arrow(.2);
	glPopMatrix();
}


void weapon_HUD_FIRE(Game* game, int mode,double time_offset){
	viseur(game);


	glPushMatrix();
	BOW_GL_MATRIX();

	double time_pos=game->fire_value;
	time_pos=1-time_pos + time_offset;

	// time_pos=1;

	//FIRE
	if(time_pos<.1){
	// else {

		//time_pos entre 0 et 1
		time_pos=(time_pos)/.1;
		//time_pos exp entre 0 et 1
		time_pos=(exp( 1-time_pos )-1)/(exp(1)-1);

		// double time_pos=.5*((int)(time_/.15)%152)/152.;

		glTranslated(1*time_pos, 1.5-1+1*time_pos, 2.5);
		glRotated(-130*.5, 0, 1, 0);
		glRotated(-30*.5, 0, 0, 1);
		glRotated(10, 0, 1, 0);

		//ARROW
		glPushMatrix();
			glRotated(90, 0, 1, 0);
			glRotated(90, 1, 0, 0);
			glRotated(3, 1, 0, 0);
			glTranslated(0,.3,-8+5*time_pos);

			glTranslated(0,0,-1*(1-time_pos));

			draw_arrow_high_quality();
		glPopMatrix();

		//BOW + HAND
		draw_hand(.5*time_pos,2.+2-2*time_pos,TRUE);
		if(mode==2){
			draw_bow_v3(.2,.5*time_pos);
		}else if(mode==1){
			draw_bow_v2(.2,.5*time_pos);
		}else{
			draw_bow(.2,.5*time_pos);
		}



	}else if(time_pos<.3){
		//time_pos entre 0 et 1
		time_pos=(time_pos-.1)/.2;

		// double time_pos=.5*((int)(time_/.15)%152)/152.;

		glTranslated(0, 1.5-1, 2.5);
		glRotated(-130*.5, 0, 1, 0);
		glRotated(-30*.5, 0, 0, 1);
		glRotated(10, 0, 1, 0);

		glRotated(-40*time_pos, 1, 0, 0);
		// glRotated(-40*time_pos, 0, 0, 1);


		glTranslated(0, 0, -3*time_pos);

		draw_hand(0,2.+2,TRUE);
		if (mode==2){
			draw_bow_v3(.2,0);
		}else if(mode==1){
			draw_bow_v2(.2,0);
		}else{
			draw_bow(.2,0);
		}


	}else if(time_pos<.6){

		//time_pos entre 0 et 1
		time_pos=(time_pos-.3)/.3;
		// time_pos =1;

		// double time_pos=.5*((int)(time_/.15)%152)/152.;

				// glTranslated(-2*time_pos, 2*time_pos,3*time_pos);

		glTranslated(0, 1.5-1, 2.5);
		glRotated(-130*.5, 0, 1, 0);
		glRotated(-30*.5, 0, 0, 1);
		glRotated(10, 0, 1, 0);

		glRotated(-40, 1, 0, 0);

		glTranslated(0, 0, -3*time_pos);
		glRotated(20*time_pos, 0, 1, 0);

		// glTranslated(-2*time_pos, 0, 2*time_pos);

		// glRotated(-20*time_pos, 0, 1, 1);

		glRotated(20*time_pos, 1, 1, 0);

				// glRotated(30*time_pos, 0, 0, 1);

		glTranslated(0, 0, -3);

		draw_hand(0,2.+2-2*time_pos,TRUE);
		if (mode==2){
			draw_bow_v3(.2,0);
		}else if(mode==1){
			draw_bow_v2(.2,0);
		}else{
			draw_bow(.2,0);
		}

	}else{

		double oscill_force=.5*sin(SDL_GetTicks()*.001)+.5*sin(SDL_GetTicks()*.00085);
	
		//time_pos entre 0 et 1
		time_pos=(time_pos-.6)/.4;

		time_pos=1-time_pos;


		glTranslated(2*time_pos, 0, 0);
		glRotated(30*(time_pos), 0, 1, 0);
		glRotated(-0, 0, 0, 1);


		glPushMatrix();
			//ARROW
			glRotated(60, 0, 1, 0);
			glRotated(60, 1, 0, 0);
			// glTranslated(
			// 	-.3+.1*sin(SDL_GetTicks()*.0017*(1-time_pos)),
			// 	1-.7*time_pos,
			// 	-5+1*oscill_force*(1-time_pos)+2*time_pos
			// 	);
			glTranslated(
				-.3+.1*sin(SDL_GetTicks()*.0017),
				1,
				-5+1*oscill_force
				);

			glTranslated(5*time_pos,5*time_pos,0);

			glTranslated(-10*time_pos,0,0);
			// glRotated(-20+20*cos(SDL_GetTicks()*0.01), 1,-.3,0);
			glRotated(-40*time_pos, 1,0,0);
			glTranslated(10*time_pos,0,0);

			glTranslated(0,2*time_pos,2*time_pos);

			glTranslated(-3*time_pos,0,0);

			draw_arrow_high_quality();
				if(mode){
					glPushMatrix();
						glTranslated(-1.3,0,1.7);
						glRotated(10,0,1,0);
						draw_arrow_high_quality();
					glPopMatrix();
					glPushMatrix();
						glTranslated(1.3,0,1);
						glRotated(-10,0,1,0);
						draw_arrow_high_quality();
					glPopMatrix();

				}
		glPopMatrix();

		draw_hand(  .3+.1*oscill_force,0,FALSE);
		if(mode==2){
			draw_bow_v3(.2,.2+.1*oscill_force);
		}else if(mode==1){
			draw_bow_v2(.2,.2+.1*oscill_force);
		}else{
			draw_bow(.2,.2+.1*oscill_force);
		}


	}


	glPopMatrix();
}

















static int n=10;

static double angle=0;
void sulfateuse_HUD(Game* game, int color,double time_offset){

	viseur(game);

	double oscill_force=.5*sin(SDL_GetTicks()*.001)+.5*sin(SDL_GetTicks()*.00085);

	if(n==1){
		angle+=game->trigger_value*16.;
	}else{
		angle+=game->trigger_value*10.;
	}
	glGetError();
	for(int i=0;i<n;i++){
		double x=1-i*1./n;
		glPushMatrix();
				fake_walking=
					 game->player->dx*game->player->dx
					+game->player->dy*game->player->dy
					+game->player->dz*game->player->dz;
				fake_walking=sqrt(fake_walking);
				fake_walking*=0.007;
				double real_rho=game->player->rho    +fake_rho;
				double real_theta=game->player->theta+fake_theta;
				glRotated(real_rho*(-4),1,0,0);
				glRotated(real_theta*.5, 0, 1, 0);
				double real_HUD_drho_compensation=HUD_drho_compensation+fake_HUD_drho_compensation;
				glTranslated(real_theta*(.05)+5,0,-real_HUD_drho_compensation*real_HUD_drho_compensation*0.0007-3);
				glRotated(80, 0, 1, 0);
				glRotated(70, 1, 0, 0);
				glRotated(real_theta*(1),0,0,1);
				glRotated(real_HUD_drho_compensation,0,1,0);
				glTranslated(0,1-x*game->fire_value,-1);
				glLineWidth(3.0);

				draw_hand(  .3+.1*oscill_force,0,FALSE);
				// printf("%lf\n",i*game->trigger_value );
				draw_sulfateuse(0,angle-4*i*game->trigger_value,color);
				// draw_sulfateuse(0,angle-time_offset*game->trigger_value,color);
		// glTranslated(                               0, 1, -5+1*oscill_force);
		// glTranslated(-.3+.1*sin(SDL_GetTicks()*.0017), 0, 0);
		// draw_arrow(.2);
		glPopMatrix();

		if(i == 0)
			glAccum(GL_LOAD, 1.0 / n);
		else
			glAccum(GL_ACCUM, 1.0 / n);

	}
	glAccum(GL_RETURN, 1.0);
	if(glGetError()&GL_INVALID_OPERATION) {
		// gl accum not avaiable
		// printf("GLACCUM UNAVAIABLE\n");
		n=1;
	}

	// int n=20;
	// for(int i=0;i<n;i++){
	// 	draw();
	// 	if(i == 0)
	// 		glAccum(GL_LOAD, 1.0 / n);
	// 	else
	// 		glAccum(GL_ACCUM, 1.0 / n);
	// }
	// glAccum(GL_RETURN, 1.0);

}

