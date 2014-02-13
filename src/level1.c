#include "levels.h"
#include "random.h"

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
void level1_spawn_mechants(Game* game){
	void local_update(Mechant * mechant){
		// printf("caca\n");
		mechant->x+=mechant->dx;
		mechant->y+=mechant->dy;
		mechant->z+=mechant->dz;
	}
	Mechant * mechant;
	// for(int i=-15;i<15;i++){
	// 	for(int j=-15;j<15;j++){
	// 		mechant = malloc(sizeof(Mechant));
	// 		mechant->x=20*i;
	// 		mechant->y=20*j;
	// 		mechant->z=0;

	// 		mechant->dx=0;
	// 		mechant->dy=0;
	// 		mechant->dz=0;

	// 		mechant->update=NULL;
	// 		game_insert_Mechant(game, mechant);
	// 	}
	// }


	for(int i=-10;i<10;i++){
		for(int j=-10;j<10;j++){
			mechant = malloc(sizeof(Mechant));
			double rayon = random(300,0);
			double angle = random(0,2*PI);
			mechant->x=rayon*cos(angle);
			mechant->y=rayon*sin(angle);
			mechant->z=0;

			mechant->dx=random(0,.05);
			mechant->dy=random(0,.05);
			mechant->dz=0;

			mechant->update=local_update;
			// mechant->update=NULL;
			game_insert_Mechant(game, mechant);
		}
	}

}
void ingame_level1_setup(Game* game){
	audioplayer_set_next(game->audio,"music/Goto80_gopho_level1.ogg");

	game->player->x=0;
	game->player->y=0;
	game->player->z=0;
	game->player->theta=0;
	game->update=ingame_level1_update;
	game->render=ingame_level1_render;
	game->weapon=1;

	set_time_(0);

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
void ingame_level1_update_waiting_music_sync(Game* game,int dt){

}
static int generated=0;
static int landed=0;
void ingame_level1_update(Game* game,int dt){
	if(!strcmp(game->audio->now_playing,"music/Goto80_gopho_level1.ogg")){
		printf("%lf\n", audioplayer_getTime(game->audio));
		if(audioplayer_getTime(game->audio)<6.7){
			// printf("FLYING\n");
			game->player->z=-100;
			game->player->dz=0;
		}else if(audioplayer_getTime(game->audio)<7.65){
			if(!generated){
				level1_spawn_mechants(game);
				generated=1;
				// clear_arrow(game);
				game->player->z=-100;
				game->player->y=0;
				game->player->x=0;
			}
			// game->player->z=100-100*(audioplayer_getTime(game->audio)-6.7)/(7.65-6.7);
			// game->player->dz=-10;
		}else{
			if(!landed){
				for(int i=0;i<20;i++){
					game_add_explosion(game,
						-game->player->x + random(0,20),
						-game->player->y + random(0,20),
						-game->player->z + random(0,20));
				}
				landed=1;
				// printf("BOOM\n");
			}
		}

	}else{
		game->player->z=-100;
		game->player->dz=0;
	}

}
void ingame_level1_render(Game* game){

	// // double z=exp(-time_*.07);
	// double z=exp(-get_time_()*.007);
	// int angle=game->player->angle;
	// // printf("%i\n",angle);
	// // angle=60;

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
void ingame_level2_setup(Game* game){
	game->update=ingame_level2_update;
	game->render=ingame_level2_render;
}

void ingame_level2_update(Game* game,int dt){

}
void ingame_level2_render(Game* game){
	double time_=SDL_GetTicks()*0.001;
	glDisable( GL_POINT_SMOOTH );
	glPointSize(1);
	glBegin(GL_POINTS);
	glColor4d(.5,0,0,1);

	// glClearColor(1.,1.,1.,0.);

	glDepthFunc(GL_ALWAYS);

	int i_max = 400;
	int j_max = 10;
	double inverse_i_max=1./i_max;
	double inverse_j_max=1./j_max;
	for(int i=-i_max;i<i_max;i++){
		for(int j=-j_max;j<j_max;j++){

			double x=i*inverse_i_max + .1*random(-.5,1);
			double y=j*inverse_j_max + .1*random(-.5,1);
			// glColor4d(.5+.5*cos(2*PI*exp(2-2*y)-time_),.5+.5*sin(2*PI*exp(2-2*y)+time_),0,1);
			// glColor4d(0,.5+.5*sin(2*PI*exp(2-2*y)+time_),.5+.5*cos(2*PI*exp(2-2*y)-time_),1);
			double dist_factor=1-exp(-1-1*y);
			double super_z = exp(2*(-y+1))*(1+random(-.5,1));
			glColor4d(0,dist_factor*(.5+.5*sin(2*PI*x+2*PI*exp(-.1-.1*super_z)-time_)),dist_factor*(.5+.5*cos(2*PI*exp(-.1-.1*super_z)-time_)),.2);
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
			double variation = 40*sin(2*x*(1)+.5*time_) +  10*sin(10*x+time_) + 10*sin(24*x-time_) + 3*sin(45*x-5*time_);
			variation=2*variation;
			// glVertex3d(
			// 		// x*100 + 10*sin(12*x*(1)+.7*time_) + 10*sin(3*x+time_),
			// 		x*200 + variation * sin(15*x*(1)+time_),
			// 		// 40*sin(2*x+.5*time_) +  10*sin(10*x+time_) + 10*sin(24*x-time_) + 3*sin(45*x-5*time_),
			// 		variation + 5*random(-.5,1),
			// 		64 + 5*exp(2*(-y+1))+ 5*exp(2*(-y+1))*random(-.5,1) + 20*sin(20*x + time_)
			// 		// 32+50+50*y+ random(-.25,5)
			// 	);
			glVertex3d(
					x*200 + variation * sin(15*x*(1)+time_),
					variation + 20*random(-.5,1),
					64 + 5*super_z + 20*sin(20*x + time_)
				);
		}
	}
	glEnd();

	glDepthFunc(GL_LESS);
}
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
void ingame_level3_update(Game* game,int dt){

}
void ingame_level3_render(Game* game){
	double time_=SDL_GetTicks()*0.001;
	// time_*=.2;
	double R;
	double deltat=1;

	for(int i=-50;i<50;i++){
		for(int j=-50;j<50;j++){
			double t=fmod(time_,deltat);
			// R=exp(-4*t)*sin(t/deltat*2*PI* (16-16*t/deltat) )+10;
			double theta = PI*i/50.;
			double phi = PI*(50+j/100.);
			// R=2*exp(-4*t)*sin(fabs(.3*theta) * t/deltat*2*PI* 8*exp(-2*t/deltat) )+10;
			// R=2*exp(-4*t)*sin(fabs(2*theta) + t/deltat*2*PI* 8*exp(-2*t/deltat) )+10;
			// R=2*exp(-4*t)*sin(fabs(2*theta) + 2*phi + t/deltat*2*PI* 8*exp(-2*t/deltat) )+10;
			// R=((fabs(theta)+1)*10+9*cos(5*time_+2*phi))/(2+sin(phi+time_));
			// R = exp( sin (theta*2*phi*cos(time_*0.05)) );
			// R =  sin (theta*2*phi*(1+cos(time_*0.05))) ;
			// R = (theta-phi)*sin (theta+2*phi+time_) ;
			// R = 10 *sin(2*theta-time_)/(2+cos(2*phi+time_));

			glColor4d(.5+.5*cos(time_),0.4,0,1);
			glBegin(GL_POINTS);
				// glVertex3d(R*cos(theta)*sin(phi),R*sin(theta)*sin(phi),R*cos(theta));
				glVertex3d(R*sin(theta)*cos(phi),R*sin(theta)*sin(phi),R*cos(theta));
			glEnd();
		}
	}
}
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
