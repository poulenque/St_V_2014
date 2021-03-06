#include "levels.h"
#include "random.h"

int sign(int x) {
    return (x > 0) - (x < 0);
}

static double messages_x[200];
static double messages_y[200];
static double messages_z[200];
static double messages_z_exp_offset[200];
static double messages_z_exp_speed[200];
static double messages_dephasage[200];

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
void intro_setup(Game* game){
	glEnable(GL_FOG);
	GLfloat fogColor[4]= {0,0, 0, 1};
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.35f);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 700);
	glFogf(GL_FOG_END, 1000);

	glClearColor( 0., 0., 0., 1. );
	game->update=intro_update;
	game->render=intro_render;
	// level1_spawn_mechants(game);
}

void intro_update(Game* game,int dt){
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
		intro_get_weapon_setup(game);
	}
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void intro_render(Game* game){

	glMatrixMode(GL_MODELVIEW);

	//TEST SULFATEUSE

	// glPushMatrix();
	// glTranslated(60,-60,-10);
	// glScaled(4,4,4);
	// draw_sulfateuse(0,0);
	// glPopMatrix();

	//TEST BOW 

	#define DRAW_ONE_BOW \
	glTranslated(15,-11,-5);\
	glRotated(60,1,1,0);\
	glScaled(1,1,1);\
	glColor4d(1,0,0,1);\
	draw_bow(0,.5+.5*cos(PI*cos(get_time_()/15.*.1)));\
	glScaled(3,1,3);\
	glTranslated(0,3.2-4*cos(PI*cos(get_time_()/15.*.1)),0);\
	glRotated(90,1,0,0);\
	draw_arrow_high_quality_no_heart();

	glPushMatrix();
	DRAW_ONE_BOW
	glPopMatrix();

	glPushMatrix();
	glScaled(1,-1,1);
	DRAW_ONE_BOW
	glPopMatrix();



	glPushMatrix();
	glTranslated(20,0,0);

		glColor4d(1,1,1,1);

		draw_sphere2(5,SDL_GetTicks()*.05,0);

		String3d* str=get_str();

		str->x=0;
		str->y=0;
		str->z=0;

		//====================================================
		string3d_setTxt(str,"     a game by    \n\nLaurent Rohrbasser");
		// string3d_setTxt(str,"     a game by    \n");
		// string3d_setTxt(str,"\n");
		// string3d_setTxt(str,"Laurent Rohrbasser");

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

		string3d_setTxt(str," ENTER THE SPHERE\n\n     to begin");
		// string3d_setTxt(str," ENTER THE SPHERE \n");
		// string3d_setTxt(str,"     to begin     \n");

		//MAKES THE TEXT ORIENTED TO THE PLAYER
		// glRotated(-90-atan2(-game->player->x-20,-game->player->y)*180/PI,0,0,1);

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
		// glTranslated(0,0,-1);
		glScaled(-1,1,1);
		glColor4d(k,k,k,1);
		string3d_setTxt(str,"music > gopho by goto80 >>>>> music > gopho by goto80 >>>>> ");
		str->size=.5;
		str->dist=7.15;
		str->z=-.25;
		str->phi=SDL_GetTicks()*0.05*.75;
		string3d_draw(str);
		str->phi=0;

		//====================================================

	glPopMatrix();









				double x_temp=(game->player->x+200);
				double y_temp=(game->player->y-0);
				double z_temp=(game->player->z-0);

				x_temp*=x_temp;//square
				y_temp*=y_temp;//square
				z_temp*=z_temp;//square

				double d= (sqrt(x_temp+y_temp+z_temp));
				d=225;
				double tps=get_time_()/15.;
				int i_MAX=100;
				glPushMatrix();

					double kk=20;
					glTranslated(kk,0,0);
					// draw_cube(1,1);
					glRotated(-90-atan2(-game->player->x-kk,-game->player->y)*180/PI,0,0,1);
					// glRotated(-game->player->z*0.15,0,1,0);
					glRotated(atan2(-game->player->z,d)*180/PI,0,1,0);
					glTranslated(-kk,0,0);

					// glTranslated(+kk-200,0,0);


						glLineWidth(1);
						for(int i=0;i<i_MAX;i++){
							for(int j=-20;j<20;j++){
								double pipi=1./(i_MAX);

								double jj=j/2.;

								double xxx=-10*kk*i*pipi+80;
								double yyy=-sin(24*PI*(i+1.2*jj)*pipi+tps*.1) + jj*2 + (i-40)*(jj)*.2;
								double zzz=8-10*exp(-(1+sin(12*PI*(i+2*jj)*pipi+tps*.1))) + 20*cos(jj/30.*2*PI);

								// xxx*=.1;
								// yyy*=.1;
								// zzz*=.1;

									// glColor4d(0,0,1,1);
									// printf("%lf\n",xxx );
									// printf("%lf\n",-d +200);

									// glColor4d(0,0,0,(1-exp(-time_/100.)) * (d/200.) );
									// if(2-d/200.>9){
									// 	d=200.*(-.9+2);
									// }
									double v= (2-d/200.) ;
									if(v<.2)
										v=.2;
									// if(v>.9)
									// 	v=.9;
									// printf("%lf\n",v );
									double e=exp(-(1+sin(12*PI*(i+2*j)*pipi+tps*.1)));
									double k=(1-i*pipi)*3;
									if(k>1)k=1;
									double ddd=d*100./15.;
									if(ddd>1)ddd=1;


									// double hide_behind =exp((xxx+d-kk)*.06);
									double hide_behind =exp((xxx+d-10*kk)*.006)-1;
									// double hide_behind=(xxx+d-10*kk);
									if(hide_behind>1)hide_behind=1;
									// hide_behind=1;

									double vv=v * (i*pipi) *ddd *3. *  k  *.3;
									if (vv>1)vv=1;

									double transparency= vv* hide_behind;
									if(transparency>0.5)transparency=0.5;
									glColor4d(
										e,
										e,
										e,
										transparency);

									// glPointSize(20);
									// glPointSize(d/600. * 20 * i*pipi);
									glPointSize(7);
									glEnable(GL_POINT_SMOOTH);
										// glRotated((j+i+1)*(time_*.1),0,0,1);
										// glScaled(1,1,2);

										glBegin(GL_POINTS);
											glVertex3d(xxx,yyy,zzz);
											glVertex3d(xxx,-yyy,-zzz);
										glEnd();

										// draw_face(1,4);

										// draw_cheni(1,4,3);
										// draw_cube(1,4);

							}
						}
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
static double shared_var1;

void intro_get_weapon_setup(Game* game){


		audioplayer_set_next(game->audio,"music/Goto80_gopho_loop_far.ogg");
		// audioplayer_set_next(game->audio,"music/Goto80_gopho_far.ogg");

		game->player->x=200;
		game->player->y=0;
		game->player->z=0;

		// if(game->player->avance==-1)
			game->player->phi  =0;
		// else
		// 	game->player->phi  =180;

		// game->player->theta=0;
		// game->player->rho  =0;

		set_time_(0);

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
		clear_arrow(game);
}

double fadout=1;

void intro_get_weapon_update(Game* game,int dt){

	//distace player begin square
	double x_temp=(game->player->x+200);
	double y_temp=(game->player->y-0);
	double z_temp=(game->player->z-0);

	x_temp*=x_temp;//square
	y_temp*=y_temp;//square
	z_temp*=z_temp;//square

	double d= (sqrt(x_temp+y_temp+z_temp));

	shared_var1=d;

	// printf("%lf\n", audioplayer_getTime(game->audio));

	if(d<5){
		// GOTO LEVEL 1 !
		game->weapon=1;
		game->render= intro_get_weapon_render_fadout;
		audioplayer_set_next(game->audio,"music/Goto80_gopho_level1.ogg");
	}
	if(!strcmp(game->audio->now_playing,"music/Goto80_gopho_level1.ogg")){
		fadout=1-audioplayer_getTime(game->audio)/6.;
		if(audioplayer_getTime(game->audio)>6.7){
			game->player->z=-100;
			game->player->dz=0;
			game->player->x=0;
			game->player->y=0;
			clear_arrow(game);
			ingame_level1_setup(game);
		}
	}
}

void intro_get_weapon_render_fadout(Game* game){
	String3d* str=get_str();



	double d= shared_var1;
	// glClearColor(d*.01,d*.01,d*.01,1);

	glColor4d(0,0,0,1*fadout);
	double size=10;

	double dd=d;
	if (dd>1/0.02) dd=1/.02;
	dd=dd*.01;
	if(dd<.5)dd=.5;
	if(game->stereo)
		glColor4d(.7,.2,.2,.5*fadout);
	else
		glColor4d(1,0,0,.5*fadout);
	glPushMatrix();
		// glTranslated(200,0,-size*2+exp(6+1-get_time_()/50.));
		glTranslated(200,0,0);
		// glRotated(-45,0,0,1);
		glLineWidth(2);
		draw_cube(size,.1);

	glPopMatrix();

	glLineWidth(3);
	if(game->stereo)
		glColor4d(.7,.2,.2,.5*fadout);
	else
		glColor4d(1,0,0,.5*fadout);
	glPushMatrix();
	glRotated(90,0,1,0);
	glTranslated(10,0,200);
		for(int i=-15;i<=15;i++){
			glPushMatrix();
				glTranslated(5,  sign(i)* exp(3.5+abs(i)*.3) - sign(i)* 30 ,0);
				draw_square(size/2,.1);
				glTranslated(1,0,0);
				draw_square(size/2,.1);
			glPopMatrix();
			glPushMatrix();
				glTranslated(5,0,sign(i)* exp(3.5+abs(i)*.3) - sign(i)* 30);
				draw_square(size/2,.1);
				glTranslated(1,0,0);
				draw_square(size/2,.1);
			glPopMatrix();
		}
	glPopMatrix();

	glPopMatrix();

	glDepthFunc(GL_LESS);

}



































void intro_get_weapon_render(Game* game){

	String3d* str=get_str();


	double tps=get_time_()/15.;



	double d= shared_var1;
	// glClearColor(d*.01,d*.01,d*.01,1);

	glColor4d(0,0,0,1);
	double size=10;

	// glPushMatrix();
	// 	glColor4d(
	// 		1-exp(2.5-tps*0.05),
	// 		1-exp(2.5-tps*0.05),
	// 		1-exp(2.5-tps*0.05),
	// 		1);
	// 	glTranslated(-210-exp(tps*0.05),0,0);
	// 	// draw_face(100*(1-exp(-time_*0.05)),.1);
	// 	draw_face(30,.1);
	// glPopMatrix();


	// glColor4d(0,0,0,exp(-time_/50.));
	// glPushMatrix();
	// 	glTranslated(200,0,size*2-exp(6-time_/50.));
	// 	// glRotated(-45,0,0,1);
	// 	draw_cube(size,.1);
	// glPopMatrix();

	// glColor4d(0,0,0,1);
	double dd=d;
	if (dd>1/0.02) dd=1/.02;
	dd=dd*.01;
	if(dd<.5)dd=.5;
	if(game->stereo)
		glColor4d(.7,.2,.2,(1-exp(-tps/100.))*dd);
	else
		glColor4d(1,0,0,(1-exp(-tps/100.))*dd);
	glPushMatrix();
		// glTranslated(200,0,-size*2+exp(6+1-tps/50.));
		glTranslated(200,0,+exp(6+1-tps/30.));
		// glRotated(-45,0,0,1);
		glLineWidth(2);
		draw_cube(size,.1);

		// glTranslated(0,0,size*2);
		glPushMatrix();
		glRotated(tps,0,0,1);
		glRotated(45,45,0,1);
		// glColor4d(1,0,0,1);
		draw_bow_to_take(.4,0);
		glPopMatrix();

	glPopMatrix();

	glLineWidth(3);
	if(game->stereo)
		glColor4d(.7,.2,.2,(1-exp(-tps/100.))*dd);
	else
		glColor4d(1,0,0,(1-exp(-tps/100.))*dd);
	glPushMatrix();
	glRotated(90,0,1,0);
	glTranslated(10,0,200);
		for(int i=-15;i<=15;i++){
			glPushMatrix();
				glTranslated(5+exp(7-(2000-abs(i*i*i))*tps/40000),  sign(i)* exp(3.5+abs(i)*.3) - sign(i)* 30 ,0);
				draw_square(size/2,.1);
				glTranslated(1,0,0);
				draw_square(size/2,.1);
			glPopMatrix();
			glPushMatrix();
				glTranslated(5+exp(7-(2000-abs(i*i*i))*tps/40000),0,sign(i)* exp(3.5+abs(i)*.3) - sign(i)* 30);
				draw_square(size/2,.1);
				glTranslated(1,0,0);
				draw_square(size/2,.1);
			glPopMatrix();
		}
	glPopMatrix();

	glDepthFunc(GL_ALWAYS);
	int i_MAX=300;
	for(int i=0;i<i_MAX;i++){
		double pipi=1./i_MAX;
		// glColor4d(0,0,0,(1-exp(-time_/100.)) * (d/200.) );
		double v= (2-d/200.) ;
		if(v<.2)
			v=.2;
		double w=d/100;
		if(w>1)w=1;
		double transparency=v*(1-exp(-tps/400.)) * (1-i*pipi) *(d/400.) *dd*w;
		if(transparency>.07)transparency=.07;
		// transparency=.07;
		if(game->stereo)
			glColor4d(.7,.2,.2,transparency);
		else
			glColor4d(1,0,0,transparency);
		double xxx=200;
		double yyy=0;
		double zzz=
				-.3 * size*i*pipi*200.*1*(1+exp(4-tps/50.)) * (1.5+.5*cos(tps*0.1+i*pipi*PI*16))
				-200*exp(-tps/50.)
				- size;
		double angle=180*cos(i*pipi*4*PI+(tps*.01));
		double www=.2*size*i*pipi*100*(1+.9+.3*cos(tps*0.02))+size;
		// double www=size*i*pipi*100*(1+.5+.5*cos((1+i*pipi*16)*tps*0.005))+size;
		// zzz=.3*zzz;
		// www=.2*www;
		// double uuu=.1/(i*pipi*200.);
		
		glPushMatrix();
			glTranslated(0,0,-10 - i*pipi*500 );
			glTranslated(xxx,yyy,zzz);
			// glRotated(i*(tps*.1),0,0,1);
			glRotated(angle,0,0,1);
			// draw_cube(www,uuu);
			draw_cube_simple(www);

			// glTranslated(0,0,30 + i*pipi*500 );
			// glTranslated(0,0,30 + i*pipi*500 );
			// glTranslated(-2*xxx,-2*yyy,-2*zzz);

			// draw_cube(size*i*pipi*200+size,.1/(i*pipi*200.));
		glPopMatrix();

		glPushMatrix();
			glTranslated(0,0, 10 + i*pipi*500 );
			glTranslated(xxx,-yyy,-zzz);
			// glRotated(i*(tps*.1),0,0,1);
			glRotated(angle,0,0,1);
			// draw_cube(www,uuu);
			draw_cube_simple(www);
		glPopMatrix();
	}

	glDepthFunc(GL_LESS);
	glPushMatrix();
				//ALIGNER WORLD A LA CAMERA 
				glTranslated(200,0,0);
				if(game->stereo)
					glColor4d(.7,.2,.2,1);
				else
					glColor4d(1,0,0,1);
				// draw_cube(1,1);
				glRotated(-90-atan2(-game->player->x-200,-game->player->y)*180/PI,0,0,1);
				// glRotated(-game->player->z*0.15,0,1,0);
				glRotated(atan2(-game->player->z,d)*180/PI,0,1,0);
				glTranslated(-200,0,0);

				glPushMatrix();
					glScaled(1,-1,1);
					// glColor4d(0,0,0,1-exp(-time_/100.));
					if(game->stereo)
						glColor4d(.7,0.5,0.5,(1-exp(-tps/100.))*dd);
					else
						glColor4d(1,0.5,0.5,(1-exp(-tps/100.))*dd);
					for(int i=0;i<10;i++){
						string3d_setTxt(str,"go accomplish your mission");
						str->size=1.12 + .15*(1+cos (tps*.1+i));
						str->dist=7.15 + 1+cos (tps*.1+i);
						str->x=200;
						str->y=0;
						str->z=exp(6+1-tps/30.)+i*2 -10;
						// str->z=-.5+exp(6+1-tps/50.)+i*2 -30+1;
						str->phi=tps*.75+i*40;
						string3d_draw(str);
					}
				glPopMatrix();

				glDepthFunc(GL_NOTEQUAL);

				i_MAX=70;
				glPushMatrix();
						glLineWidth(1);
						glDepthFunc(GL_ALWAYS);
						for(int i=0;i<i_MAX;i++){
							for(int j=-20;j<20;j++){
								double pipi=1./i_MAX;

								double jj=j/2.;

								double xxx=-200+400*(1-i*pipi);
								double yyy=-3*sin(24*PI*(i+1.2*jj)*pipi+tps*.1) + jj*10 + (i-40)*(jj)*.2;
								double zzz=8-10*exp(-(1+sin(12*PI*(i+2*jj)*pipi+tps*.1))) + 20*cos(jj/30.*2*PI);

									// glColor4d(0,0,1,1);
									// printf("%lf\n",xxx );
									// printf("%lf\n",-d +200);

									// glColor4d(0,0,0,(1-exp(-time_/100.)) * (d/200.) );
									double v= (2-d/200.) ;
									if(v<.2)
										v=.2;
									double e=exp(-(1+sin(12*PI*(i+2*j)*pipi+tps*.1)));
									double k=(1-i*pipi)*3;
									if(k>1)k=1;
									double ddd=d*100./15.;
									if(ddd>1)ddd=1;


									double hide_behind =exp((xxx+d-200)*.06);
									if(hide_behind>1)hide_behind=1;
									// printf("%lf\n", hide_behind );
									double transparency=v*(1-exp(1-tps/100.)) * (i*pipi) *ddd *3. *  k  *.3 * hide_behind;
									if(transparency>0.5)transparency=0.5;
									glColor4d(
										1,
										1 - e,
										1 - e,
										transparency);

									// glPointSize(20);
									// glPointSize(d/600. * 20 * i*pipi);
									glPointSize(7);
									glEnable(GL_POINT_SMOOTH);
										// glRotated((j+i+1)*(time_*.1),0,0,1);
										// glScaled(1,1,2);

										glBegin(GL_POINTS);
											glVertex3d(xxx,yyy,zzz);
											glVertex3d(xxx,-yyy,-zzz);
										glEnd();

										// draw_face(1,4);

										// draw_cheni(1,4,3);
										// draw_cube(1,4);

							}
						}
				glPopMatrix();
	glPopMatrix();

	glDepthFunc(GL_LESS);

	glPushMatrix();
		glTranslated(200,0,0);
		glRotated(-90-atan2(-game->player->x-200,-game->player->y)*180/PI,0,0,1);
		// glScaled(1,-1,1);
		double col=1-d/150.;
		if(col<0)col=0;
		glColor4d(1,0,0,col);
		char * buffer = malloc(256*sizeof(char));
		snprintf(buffer,256*sizeof(char) , "use <k> and <l>\nto change mouse\n   sensivity   \n     %2.3lf", game->speed_custom);
		// string3d_setTxt(str,"use <k> and <l>\nto change mouse\n   sensivity   ");
		string3d_setTxt(str,buffer);
		str->size=2.3;
		str->dist=16;
		str->x=0;
		str->y=0;
		str->z=exp(6+1-tps/30.) + 5 ;
		str->phi=95;
		string3d_draw(str);
	glPopMatrix();

}
