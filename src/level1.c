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
void ingame_level1_update(Game* game,int dt){

	// game->render = ingame_level2_render;
	// game->update = ingame_level2_update;

	// if(!audio_isPlaying(game->audio)){
	// 	audio_playMusic(game->audio,"music/Goto80_gopho.ogg");
	// }
}
void ingame_level1_render(Game* game){

	// double z=exp(-time_*.07);
	double z=exp(-get_time_()*.007);
	int angle=game->player->angle;
	// printf("%i\n",angle);
	// angle=60;

	for(int i=-100;i<100;i++){
		for(int j=-100;j<100;j++){
			double x_guy=20*i;
			double y_guy=20*j;
			// double alpha = atan((x_guy+game->player->x)/(y_guy+game->player->y))*180./PI;
			double alpha = atan2((y_guy+game->player->y),(x_guy+game->player->x))*180./PI;

			alpha = alpha+game->player->phi;
			while(alpha<=0)
				alpha+=360;
			while(alpha>360)
				alpha-=360;


			if(
				 (alpha <angle||alpha>360-angle)
				){
				double dist=(x_guy+game->player->x)*(x_guy+game->player->x)+(y_guy+game->player->y)*(y_guy+game->player->y);

				int quality=0;
				if(dist<20*20*20){
					quality=2;
				}else if(dist<50*20*20){
					quality=1;
				}else if(dist<300*20*20){
					quality=0;
				}else{
					continue;
				}

				glColor4d(z,z,z,1);
				glPushMatrix();
					glTranslated(20*i,20*j,20*z);
					draw_gentil(2*(100-(int)get_time_()%100)*.01,quality);
				glPopMatrix();

				glColor4d(0.9,0.9,0.9,1-z);
				glPushMatrix();
					glTranslated(0,0,-10);
					glScaled(1,1,-1);
					glTranslated(20*i,20*j,20*z);
					draw_gentil(2*(100-(int)get_time_()%100)*.01,quality);
				glPopMatrix();

			}
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
			glColor4d(0,.5+.5*sin(2*PI*exp(2-2*y)+time_),.5+.5*cos(2*PI*exp(2-2*y)-time_),1);
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
			glVertex3d(
					// x*100 + 10*sin(12*x*(1)+.7*time_) + 10*sin(3*x+time_),
					x*200 + variation * sin(15*x*(1)+time_),
					// 40*sin(2*x+.5*time_) +  10*sin(10*x+time_) + 10*sin(24*x-time_) + 3*sin(45*x-5*time_),
					variation + 5*random(-.5,1),
					64 + 5*exp(2*(-y+1))+ 5*exp(2*(-y+1))*random(-.5,1) + 20*sin(20*x + time_)
					// 32+50+50*y+ random(-.25,5)
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
