#include "levels.h"
#include "random.h"


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
static double t;
#define skycubecount 30
static double skycubes[skycubecount][skycubecount][3];
static int skycubeinit=0;
static void draw_sky_random_cubes(Game* game,double dissipation){
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
	double ttt=SDL_GetTicks()*0.001;
	for (int j=0;j<skycubecount;j++){
		for (int i=0;i<skycubecount;i++){
			game_loop_coord(game,&skycubes[i][j][0], &skycubes[i][j][1]);

			double x=i*1./skycubecount;
			double y=j*1./skycubecount;





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
					simple_cube_color(
						(.5-dist*.5)*dissipation + 1-dissipation +(.3+.3*cos(3*2*PI*x+3*2*PI*y+ttt*10-1.2*t))*dissipation,
						0,
						0,
						// (.2+.2*cos(3*2*PI*x+3*2*PI*y+ttt*10))*dissipation,
						0+1-dissipation,
						0,
						0);
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
					simple_cube_color(
						(.2-dist*.2)*dissipation + 1 - dissipation +(.2+.2*cos(-3*2*PI*x-3*2*PI*y+ttt*10-1.2*t))*dissipation,
						0,
						0,
						// .1+.1*cos(-3*2*PI*x-3*2*PI*y+ttt*10),
						// .1+.1*cos(-3*2*PI*x-3*2*PI*y+ttt*10),
						1-dissipation,0,0);
				glPopMatrix();
			}
		}
	}
}














































static time_offset=0;

void ingame_level4_setup(Game* game){
	audioplayer_set_next(game->audio,"music/Goto80_gopho_level4.ogg");

	game->update=ingame_level4_update;
	game->render=ingame_level4_render;

	set_time_(0);

	time_offset=level3_get_time_offset();

	glEnable(GL_FOG);

	glFogi(GL_FOG_MODE, GL_LINEAR);//GL_EXP, GL_EXP2, GL_LINEAR
	glFogf(GL_FOG_START, 20);
	glFogf(GL_FOG_END, 250);
	// GLfloat fogColor[4]= {0,0, 0, 1};
	// glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.35f);
	// glHint(GL_FOG_HINT, GL_DONT_CARE);

	change_bg_color(1,1,1);
}

static ending_cleared=0;
static int mega_sulfateuse_transition=0;
static double deltat=.960;
void ingame_level4_update(Game* game,int dt){

	//================================
	//STOP GENERATING ENEMIES
	//================================
	// int mechant_regeneration_type_suicide(){
	// 	return -1;
	// }
	// game->mechant_regeneration_type=mechant_regeneration_type_suicide;
	//================================
	//================================


	// double time_=SDL_GetTicks()*0.001 - time_offset;
	// double deltat=.960;
	// double t=fmod(time_,deltat);
	// game->heart_beat=2*exp(-4*t)*sin(24*t);

	if(!strcmp(game->audio->now_playing,"music/Goto80_gopho_level4.ogg")){
		audioplayer_set_next(game->audio,"music/silence.ogg");

		double music_time=audioplayer_getTime(game->audio);

		double time_=SDL_GetTicks()*0.001;
		t=fmod(time_,deltat);

		if(music_time>69 && music_time<69+7){
			double xxx =(music_time-69.)/7.;
			change_bg_color(xxx,0.,0.);
		}else if(music_time>76 && music_time<83){
			if(!ending_cleared){
				clear_arrow(game);
				clear_particles(game);
				clear_mechant(game);
				ending_cleared=1;
			}
			double xxx=(music_time-76)/(83.-76.);
			change_bg_color(1.-xxx,0.,0.);
		}
		if(music_time<14.85){
			change_bg_color(1,1,1);
		}
		if(music_time>14.85 && music_time<15.30 ){
			if(music_time>14.85+mega_sulfateuse_transition*(15.30-14.85)/7.){
				mega_sulfateuse_transition++;
				if(mega_sulfateuse_transition%2==0){
					change_bg_color(.5,0,0);
					game->weapon=2;
				}else{
					change_bg_color(1,0,0);
					game->weapon=3;
				}
			}
		}

		if(music_time>15.30 && music_time<69+7 ){
			if(mega_sulfateuse_transition){
				change_bg_color(0,0,0);
				game->weapon=3;
				mega_sulfateuse_transition=0;
			}
			game->heart_beat=2*exp(-4*t)*sin(24*t);
		}

	}
}
void ingame_level4_render(Game* game){

	double music_time=audioplayer_getTime(game->audio);

			// change_bg_color(1-1*t/deltat,.5-.5*t/deltat,.5-.5*t/deltat);
	if(!strcmp(game->audio->now_playing,"music/Goto80_gopho_level4.ogg")){
		if(music_time>15.30 && music_time<69 ){
			draw_sky_random_cubes(game,1);
		}if(music_time>69 && music_time<69+7){
			double k=(music_time-69)/7.;
			draw_sky_random_cubes(game,1-k);
		}
	}
}
