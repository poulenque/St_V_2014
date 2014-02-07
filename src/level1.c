#include "levels.h"
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

	// if(!audio_isPlaying(game->audio)){
	// 	audio_playMusic(game->audio,"music/Goto80_gopho.ogg");
	// }
}
void ingame_level1_render(Game* game){

	// double z=exp(-time_*.07);
	double z=exp(-get_time_()*.007);
	int angle=game->player->mFOV*.5*game->player->mAspectRatio;
	// printf("%i\n",angle);
	angle=60;

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
