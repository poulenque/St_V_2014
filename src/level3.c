#include "levels.h"
#include "random.h"

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
void ingame_level3_setup(Game* game){
	audioplayer_set_next(game->audio,"music/Goto80_gopho_level3.ogg");

	game->update=ingame_level3_update;
	game->render=ingame_level3_render;

	set_time_(0);

	glEnable(GL_FOG);

	glFogi(GL_FOG_MODE, GL_LINEAR);//GL_EXP, GL_EXP2, GL_LINEAR
	glFogf(GL_FOG_START, 0);
	glFogf(GL_FOG_END, 250);
	GLfloat fogColor[4]= {0,0, 0, 1};
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.35f);
	glHint(GL_FOG_HINT, GL_DONT_CARE);

}


static int music_started=0;
static double time_offset=0;

double level3_get_time_offset(){
	return time_offset;
}

void ingame_level3_update(Game* game,int dt){
	if(!strcmp(game->audio->now_playing,"music/Goto80_gopho_level3.ogg")){
		//this part is called once
		if(!music_started){


			int mechant_regeneration_type_level3(){
				return rand()%2;
			}

			game->mechant_regeneration_type=mechant_regeneration_type_level3;
			time_offset=SDL_GetTicks()*0.001-.960*3./4.;
			music_started=1;
		}
		audioplayer_set_next(game->audio,"music/Goto80_gopho_level4.ogg");
	}
	if(!strcmp(game->audio->now_playing,"music/Goto80_gopho_level4.ogg")){
		ingame_level4_setup(game);
	}
}


static double t;
#define skycubecount 30
static double skycubes[skycubecount][skycubecount][3];
static int skycubeinit=0;
static void draw_sky_random_cubes(Game* game){
	if(!skycubeinit){
		for(int i=0;i<skycubecount;i++){
			for(int j=0;j<skycubecount;j++){
				skycubes[i][j][0]=(i-skycubecount/2.)*600./skycubecount;
				skycubes[i][j][1]=(j-skycubecount/2.)*600./skycubecount;
				skycubes[i][j][2]=130;
			}
		}
		skycubeinit=1;
	}

	for(int i=0;i<skycubecount;i++){
		for(int j=0;j<skycubecount;j++){
			skycubes[i][j][2]=130;
		}
	}
	double music_time=audioplayer_getTime(game->audio);
	if(!strcmp(game->audio->now_playing,"music/Goto80_gopho_level3.ogg")){
		if(music_time>49.80){
			game->heart_beat=0;
			double xxx =(music_time-49.80)/2.;
			for (int j=0;j<skycubecount;j++){
				for (int i=0;i<skycubecount;i++){
					skycubes[i][j][2]+=150*xxx;
				}
			}
			change_bg_color(xxx,xxx,xxx);

		}
	}


	for (int j=0;j<skycubecount;j++){
		for (int i=0;i<skycubecount;i++){
			game_loop_coord(game,&skycubes[i][j][0], &skycubes[i][j][1]);







			double front_x=game->player->x_culling - game->player->x;
			double front_y=game->player->y_culling - game->player->y;

			front_x*=30;
			front_y*=30;

			front_x=front_x + game->player->x;
			front_y=front_y + game->player->y;			

			double alpha = atan2((skycubes[i][j][1]+front_y),(skycubes[i][j][0]+front_x))*180./PI;

			alpha = alpha+game->player->phi;
			while(alpha<=0)  alpha+=360;
			while(alpha>360) alpha-=360;

			// if(alpha <game->player->angle||alpha>360-game->player->angle){
			if(alpha <90||alpha>360-90){

				double xx=skycubes[i][j][0]+game->player->x;
				double yy=skycubes[i][j][1]+game->player->y;
				xx*=xx;
				yy*=yy;
				double dist= sqrt (xx+yy) / 600.;
				double z_size=80.;
				// skycubes[i][j][2]=130-20*cos(i*4*PI/skycubecount+SDL_GetTicks()*0.001)-30*cos(j*4*PI/skycubecount+SDL_GetTicks()*0.001);
				skycubes[i][j][2]+=
					-20*cos(i*6*PI/skycubecount +SDL_GetTicks()*0.001)
					-10*cos(i*12*PI/skycubecount-SDL_GetTicks()*0.002)
					-20*cos(j*8*PI/skycubecount +SDL_GetTicks()*0.001);
					-10*cos(j*10*PI/skycubecount-SDL_GetTicks()*0.003);
				glPushMatrix();
					// glTranslated(skycubes[i][j][0],skycubes[i][j][1],skycubes[i][j][2] - dist*200);
					glTranslated(
						skycubes[i][j][0],
						skycubes[i][j][1],
						( skycubes[i][j][2] - dist*200 + 20*cos(dist*2*PI+.001*game->heart_beat)*game->heart_beat)
						// skycubes[i][j][2] - dist*200 + 20*cos(dist*2*PI+.001*game->heart_beat)*game->heart_beat
						// skycubes[i][j][2] - dist*200 + 20*cos(dist*2*PI+1*(1-dist/32.)*game->heart_beat)
						+z_size/2.);
					// glRotated(360*cos(SDL_GetTicks()*.0005+skycubes[i][j][2]*.01),0,0,1);
					glScaled(500./skycubecount,500./skycubecount,-z_size);
					simple_cube_color(.5-dist*.5,0,0,0,0,0);
				glPopMatrix();

				glPushMatrix();
					// glTranslated(skycubes[i][j][0],skycubes[i][j][1],-skycubes[i][j][2] + dist*200 - 50*game->heart_beat*(cos(dist*2*PI)));
					glTranslated(
						skycubes[i][j][0],
						skycubes[i][j][1],
						// (-skycubes[i][j][2] + dist*200 - 20*cos(dist*2*PI+.001*game->heart_beat)*game->heart_beat)
						-skycubes[i][j][2] + dist*200 - 20*cos(dist*2*PI)*game->heart_beat
						-z_size/2.);
					// glRotated(360*cos(SDL_GetTicks()*.0005+skycubes[i][j][2]*.01),0,0,1);
					glScaled(500./skycubecount,500./skycubecount,z_size);
					simple_cube_color(.2-dist*.2,0,0,0,0,0);
				glPopMatrix();
			}
		}
	}
}
void ingame_level3_render(Game* game){
	double time_=SDL_GetTicks()*0.001 - time_offset;
	double deltat=.960;
	t=fmod(time_,deltat);
	game->heart_beat=2*exp(-4*t)*sin(24*t);

	double music_time=audioplayer_getTime(game->audio);

	draw_sky_random_cubes(game);


	// // time_*=.2;
	// double R;

	// for(int i=-50;i<50;i++){
	// 	for(int j=-50;j<50;j++){
	// 		double t=fmod(time_,deltat);
	// 		// R=exp(-4*t)*sin(t/deltat*2*PI* (16-16*t/deltat) )+10;
	// 		double theta = PI*i/50.;
	// 		double phi = PI*(50+j/100.);
	// 		// R=2*exp(-4*t)*sin(fabs(.3*theta) * t/deltat*2*PI* 8*exp(-2*t/deltat) )+10;
	// 		// R=2*exp(-4*t)*sin(fabs(2*theta) + t/deltat*2*PI* 8*exp(-2*t/deltat) )+10;
	// 		R=2*exp(-4*t)*sin(fabs(2*theta) + 2*phi + t/deltat*2*PI* 8*exp(-2*t/deltat) )+10;
	// 		// R=((fabs(theta)+1)*10+9*cos(5*time_+2*phi))/(2+sin(phi+time_));
	// 		// R = exp( sin (theta*2*phi*cos(time_*0.05)) );
	// 		// R =  sin (theta*2*phi*(1+cos(time_*0.05))) ;
	// 		// R = (theta-phi)*sin (theta+2*phi+time_) ;
	// 		// R = 10 *sin(2*theta-time_)/(2+cos(2*phi+time_));

	// 		glColor4d(.5+.5*cos(time_),0.4,0,1);
	// 		glBegin(GL_POINTS);
	// 			// glVertex3d(R*cos(theta)*sin(phi),R*sin(theta)*sin(phi),R*cos(theta));
	// 			glVertex3d(R*sin(theta)*cos(phi),R*sin(theta)*sin(phi),R*cos(theta));
	// 		glEnd();
	// 	}
	// }
}
