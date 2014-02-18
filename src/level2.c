#include "levels.h"
#include "random.h"

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
void ingame_level2_setup(Game* game){

	glClearColor(0,0,0,1);

	audioplayer_set_next(game->audio,"music/Goto80_gopho_level2.ogg");
	glEnable(GL_FOG);
	GLfloat fogColor[4]= {0,0, 0, 1};
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.35f);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 20);
	glFogf(GL_FOG_END, 300);

	game->update=ingame_level2_update;
	game->render=ingame_level2_render;
}

double sky_1_x=0;
double sky_1_y=0;
// double sky_1_z=64;
double sky_1_dx=10;
double sky_1_dy=10;

double sky_2_x=0;
double sky_2_y=0;
// double sky_2_z=96;
double sky_2_dx=10;
double sky_2_dy=-5;

double sky_3_x=0;
double sky_3_y=0;
// double sky_3_z=128;
double sky_3_dx=10;
double sky_3_dy=-5;

double sky_1_z=90;
double sky_2_z=30;
double sky_3_z=60;

double sky_transparency=0;

void draw_stuff_in_sky(double x,double y,double z,double dx,double dy,double r,double g,double b){

	glLineWidth(5);
	for(int i=0;i<50;i++){
		for(int j=0;j<50;j++){
			double xx=.5-i/50.;
			double yy=.5-j/50.;
			xx*=2000;
			yy*=2000;
			xx+=x;
			yy+=y;
			glBegin(GL_LINES);
				glColor4d(0,0,0,0);
				glVertex3d(xx,yy,z);
				glColor4d(r,g,b,sky_transparency);
				glVertex3d(xx+dx,yy+dy,z);
			glEnd();
		}
	}
}
void ingame_level2_update(Game* game,int dt){
	if(!strcmp(game->audio->now_playing,"music/Goto80_gopho_level2.ogg")){
		audioplayer_set_next(game->audio,"music/Goto80_gopho_level3.ogg");
		sky_1_x+=.5*sky_1_dx;
		sky_1_y+=.5*sky_1_dy;
		game_loop_coord(game,&sky_1_x,&sky_1_y);
		sky_2_x+=.5*sky_2_dx;
		sky_2_y+=.5*sky_2_dy;
		game_loop_coord(game,&sky_2_x,&sky_2_y);
		sky_3_x+=.5*sky_3_dx;
		sky_3_y+=.5*sky_3_dy;
		game_loop_coord(game,&sky_3_x,&sky_3_y);

	}
	if(!strcmp(game->audio->now_playing,"music/Goto80_gopho_level3.ogg")){
		change_bg_color(0,0,0);
		game->weapon=2;		
		ingame_level3_setup(game);
	}
}
void draw_aurore_boreale(Game * game,double * X, double *Y, double * Z,int partie){
	double time_=SDL_GetTicks()*0.001;
	glDisable( GL_POINT_SMOOTH );
	glPointSize(4);
	glBegin(GL_POINTS);
	glColor4d(.5,0,0,1);


	glDepthFunc(GL_ALWAYS);

	int i_max = 120;
	int j_max = 7;
	double inverse_i_max=1./i_max;
	double inverse_j_max=1./j_max;
	if(partie){
		while(*X-100+game->player->x+game->world_x_size*.5>0)
			*X-=game->world_x_size;
		while(*X-100+game->player->x+game->world_x_size*.5<0)
			*X+=game->world_x_size;
		while(*Y+game->player->y+game->world_y_size*.5>0)
			*Y-=game->world_y_size;
		while(*Y+game->player->y+game->world_y_size*.5<0)
			*Y+=game->world_y_size;
	}else{
		while(*X-200+game->player->x+game->world_x_size*.5>0)
			*X-=game->world_x_size;
		while(*X-200+game->player->x+game->world_x_size*.5<0)
			*X+=game->world_x_size;
		while(*Y+game->player->y+game->world_y_size*.5>0)
			*Y-=game->world_y_size;
		while(*Y+game->player->y+game->world_y_size*.5<0)
			*Y+=game->world_y_size;
	}

	int i_min=-i_max;
	if(partie){
		i_min=0;
	}else{
		i_max=0;
	}

	for(int i=i_min;i<i_max;i++){
		for(int j=-j_max;j<j_max;j++){
			double x=i*inverse_i_max + .1*random(-.5,1);
			double variation = 40*sin(2*x*(1)+.5*time_) +  10*sin(10*x+time_) + 10*sin(24*x-time_) + 3*sin(45*x-5*time_);
			variation=2*variation;

			double y=j*inverse_j_max + .1*random(-.5,1);
			// glColor4d(.5+.5*cos(2*PI*exp(2-2*y)-time_),.5+.5*sin(2*PI*exp(2-2*y)+time_),0,1);
			// glColor4d(0,.5+.5*sin(2*PI*exp(2-2*y)+time_),.5+.5*cos(2*PI*exp(2-2*y)-time_),1);
			double dist_factor=1-exp(-1-1*y);
			double super_z = exp(2*(-y+1))*(1+random(-.5,1));
			glColor4d(0,dist_factor*(.5+.5*sin(2*PI*x+2*PI*exp(-.1-.1*super_z)-time_)),dist_factor*(.5+.5*cos(2*PI*exp(-.1-.1*super_z)-time_)),.4);
			// 	glVertex3d(
			// 		exp(pow(sin(time_),2))*2*i+4*cos(time_*4+i*0.4),
			// 		8*cos(time_*6+i*1.8),
			// 		-4 + 4*cos(time_*8+i*0.8));
				// glColor4d(
				// 	cos(x + y),y,cos(x*6.2 + y*4),1
				// 	);
				// glVertex3d(
				// 	100*x,100*y,16
				// 	// 100*cos(x + y),y,32
				// );
			// glColor4d(.5-.5*y,0,0,1);
			// glVertex3d(
			// 		// x*100 + 10*sin(12*x*(1)+.7*time_) + 10*sin(3*x+time_),
			// 		x*200 + variation * sin(15*x*(1)+time_),
			// 		// 40*sin(2*x+.5*time_) +  10*sin(10*x+time_) + 10*sin(24*x-time_) + 3*sin(45*x-5*time_),
			// 		variation + 5*random(-.5,1),
			// 		64 + 5*exp(2*(-y+1))+ 5*exp(2*(-y+1))*random(-.5,1) + 20*sin(20*x + time_)
			// 		// 32+50+50*y+ random(-.25,5)
			// 	);

			//VERSION LINEAIRE 
			glVertex3d(
					*X+x*200 + variation * sin(15*x*(1)+time_)+ 20*random(-.5,1),
					*Y       + variation                      + 20*random(-.5,1),
					*Z+64 + 5*super_z + 20*sin(20*x + time_)
				);
			// //VERSION CIRCULAIRE 
			// glVertex3d(
			// 		200*sin(PI/2.*x) + variation * sin(15*x*(1)+time_)+ 20*random(-.5,1),
			// 		200*cos(PI/2.*x) + variation                              + 20*random(-.5,1),
			// 		32+5*super_z + 20*sin(20*x + time_)
			// 	);

			//testing
			// if(partie)
			// 	glColor4d(1,0,0,1);
			// else
			// 	glColor4d(0,1,0,1);
			// glVertex3d(*X+x*200,*Y,*Z+64+j);
		}
	}
	glEnd();

	glDepthFunc(GL_LESS);

}

double X1=0;
double Y1=0;
double Z1=0;


double X2=300;
double Y2=300;
double Z2=0;



static int sky_change_counter=0;

void ingame_level2_render(Game* game){

	double music_time=audioplayer_getTime(game->audio);


	// -22:80 !!! 
	// -23:00 !!!

	//	7.45 -> 7.7 ->7.9
			// change_bg_color(.2,0,0);
			// change_bg_color(.2,.2,.2);
			// change_bg_color(.5,.2,.2);
		if(      07.45<music_time && music_time<07.70){
			change_bg_color(.5,.2,.2);
		}else if(22.70<music_time && music_time<22.95){
			change_bg_color(.5,.2,.2);
		}else if(29.70<music_time && music_time<29.80){
			change_bg_color(1,1,1);
		}else if(29.80<music_time && music_time<30.05){
			change_bg_color(1,0,0);
		}else if(30.05<music_time && music_time<30.30){
			change_bg_color(0,0,0);
		}else if(30.30<music_time && music_time<30.50){
			change_bg_color(1,0,0);
		}else if(44.35<music_time && music_time<45.45){
			double x=(music_time-44.35)/(45.45-44.35);
			change_bg_color(x*.5,0,0);
		}else if(45.45<music_time && music_time<45.75){
			change_bg_color(1,0,0);
		}else{
			change_bg_color(0,0,0);
		}
		if(45.75<music_time){
			game->weapon=2;
		}
		
	if(music_time<45.75){
		draw_aurore_boreale(game,&X1,&Y1,&Z1,1);
		draw_aurore_boreale(game,&X1,&Y1,&Z1,0);

		draw_aurore_boreale(game,&X2,&Y2,&Z2,1);
		draw_aurore_boreale(game,&X2,&Y2,&Z2,0);
	}else{
		change_bg_color(0,0,0);
		game->weapon=2;		
		ingame_level3_setup(game);
	}

	// if(22.8<music_time){
	// 	if(music_time<23.00){
	// 		double x=(music_time-22.8)/(23.00-22.8);
	// 		GLfloat fogColor[4]= {x,0, 0, 1};
	// 		glFogfv(GL_FOG_COLOR, fogColor);
	// 		glClearColor(x,0,0,1);
	// 	}else if(music_time<23.00){
	// 		double x=(music_time-22.8)/(23.00-22.8);
	// 		GLfloat fogColor[4]= {x,0, 0, 1};
	// 		glFogfv(GL_FOG_COLOR, fogColor);
	// 		glClearColor(x,0,0,1);			
	// 	}

	//face rouges dans le ciel a vive allure
	// 15:50 -> 23:10
	//   16:40 = max , diminuendo
	// change de forme/couleur en
	// 15:80
	// 16:80
	// 17:75
	// 18:70
	// 19:65
	// 20:60
	// 21:55
	// 22:55
	// 23:50
	// 24:45
	// 25:40
	// 26:35
	// 27:35
	// 28:25
	// 29:25


	//change 4*16 fois de 15:50 a 29:65
	if(music_time+.1>sky_change_counter*(15.325)/64.){
		sky_change_counter++;

		double angle=random(0.,PI/4.);
		if(angle<0)	angle-=PI/8.;
		else angle+=PI/8.;
		double newx=cos(angle)*sky_1_dx-sin(angle)*sky_1_dy;
		double newy=sin(angle)*sky_1_dx+cos(angle)*sky_1_dy;
		sky_1_dx=newx;
		sky_1_dy=newy;

		angle=random(0,PI/4.);
		if(angle<0)	angle-=PI/8.;
		else angle+=PI/8.;
		newx=cos(angle)*sky_2_dx-sin(angle)*sky_2_dy;
		newy=sin(angle)*sky_2_dx+cos(angle)*sky_2_dy;
		sky_2_dx=newx;
		sky_2_dy=newy;

		angle=random(0,PI/4.);
		if(angle<0)	angle-=PI/8.;
		else angle+=PI/8.;
		newx=cos(angle)*sky_3_dx-sin(angle)*sky_3_dy;
		newy=sin(angle)*sky_3_dx+cos(angle)*sky_3_dy;
		sky_3_dx=newx;
		sky_3_dy=newy;
	}
	if(15.50<music_time && music_time<29.65){
		draw_stuff_in_sky(sky_1_x,sky_1_y,sky_1_z,sky_1_dx,sky_1_dy,0,.3,0);
		draw_stuff_in_sky(sky_2_x,sky_2_y,sky_2_z,sky_2_dx,sky_2_dy,0,.3,0);
		draw_stuff_in_sky(sky_3_x,sky_3_y,sky_3_z,sky_3_dx,sky_3_dy,0,1.,0);
		draw_stuff_in_sky(sky_1_x,sky_1_y,-sky_1_z,sky_1_dx,sky_1_dy,0,.3,0);
		draw_stuff_in_sky(sky_2_x,sky_2_y,-sky_2_z,sky_2_dx,sky_2_dy,0,.3,0);
		draw_stuff_in_sky(sky_3_x,sky_3_y,-sky_3_z,sky_3_dx,sky_3_dy,0,1.,0);
		if(music_time<19.10){
			sky_transparency=(music_time-15.5)/(19.1-15.50);
		}else if(music_time<23.3){
			sky_transparency=1 - (music_time-19.1)/(23.3-19.1);
		}else if(music_time<26.7){
			sky_transparency=(music_time-23.3)/(26.7-23.3);
		}else{
			sky_transparency=1 - (music_time-26.7)/(29.65-26.7);
		}
		// change_bg_color(1,1,1);
	}
	if(30.50<music_time && music_time<44.65){
		draw_stuff_in_sky(sky_1_x,sky_1_y,sky_1_z,sky_1_dx,sky_1_dy,0,1,0);
		draw_stuff_in_sky(sky_2_x,sky_2_y,sky_2_z,sky_2_dx,sky_2_dy,0,1,0);
		draw_stuff_in_sky(sky_3_x,sky_3_y,sky_3_z,sky_3_dx,sky_3_dy,0,1,0);
		draw_stuff_in_sky(sky_1_x,sky_1_y,-sky_1_z,sky_1_dx,sky_1_dy,0,1,0);
		draw_stuff_in_sky(sky_2_x,sky_2_y,-sky_2_z,sky_2_dx,sky_2_dy,0,1,0);
		draw_stuff_in_sky(sky_3_x,sky_3_y,-sky_3_z,sky_3_dx,sky_3_dy,0,1,0);
		if(music_time<34.10){
			sky_transparency=(music_time-30.5)/(34.1-30.50);
		}else if(music_time<38.3){
			sky_transparency=1 - (music_time-34.1)/(38.3-34.1);
		}else if(music_time<41.7){
			sky_transparency=(music_time-38.3)/(41.7-38.3);
		}else{
			sky_transparency=1 - (music_time-41.7)/(44.65-41.7);
		}
		// change_bg_color(1,1,1);
	}

}
