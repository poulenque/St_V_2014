#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <math.h>
#include "random.h"
#include "string3d.h"
#include "constants.h"
#include "shader.h"
#include "draw.h"
#include "HUD.h"
#include "levels.h"

//==========================================================
//                                                      
//  _|_|_|_|    _|_|    _|      _|  _|_|_|_|_|          
//  _|        _|    _|  _|_|    _|      _|          _|  
//  _|_|_|    _|    _|  _|  _|  _|      _|              
//  _|        _|    _|  _|    _|_|      _|              
//  _|          _|_|    _|      _|      _|          _|  
//                                                      
//==========================================================
//http://patorjk.com/software/taag/#p=display&f=Block&t=FONT
//==========================================================

static double time_=0;
double get_time_(){
	return time_;
}
void set_time_(double t){
	time_=t;
}

void clear_arrow(Game* game){
	Arrow* arrow = game->arrows;
	Arrow* a;
	while(arrow!=NULL){
		a=arrow->next;	
		free(arrow);
		arrow=a;
	}
	game->arrows=NULL;
	game->arrows_last=NULL;
	game->arrows_to_update=NULL;
}

void clear_mechant(Game* game){
	Mechant* mechant = game->mechants;
	Mechant* m;
	while(mechant!=NULL){
		m=mechant->next;	
		free(mechant);
		mechant=m;
	}
	game->mechants=NULL;
}


static String3d* str;
String3d* get_str(){
	return str;
}

static double trigger_value_MAX[4];
static double fire_value_MAX[4]   ;

static double messages_x[200];
static double messages_y[200];
static double messages_z[200];
static double messages_z_exp_offset[200];
static double messages_z_exp_speed[200];
static double messages_dephasage[200];

static void update_arrow(Game* game){
		Arrow* arrow_before=NULL;
		Arrow* arrow=game->arrows_to_update;
		while(arrow!=NULL){
			arrow->v=sqrt(arrow->dx*arrow->dx + arrow->dy*arrow->dy + arrow->dz*arrow->dz);
			double angle_=-1+acos(arrow->dz/arrow->v)*2./PI;
			if(arrow->z>-4){

				// ACCELERATION g
				arrow->dz -=.0002;

				arrow->x += arrow->dx;
				arrow->y += arrow->dy;
				arrow->z += arrow->dz;

				arrow->alpha=180+acos(arrow->dz/arrow->v)*180/PI;
				arrow->beta=180./PI*atan2(arrow->dy,arrow->dx);

			//TODO COLLISION
			//TODO COLLISION
			//TODO COLLISION
			//TODO COLLISION
			//TODO COLLISION
			//TODO COLLISION
			//TODO COLLISION
			//TODO COLLISION
			//TODO COLLISION
			//TODO COLLISION
			//TODO COLLISION
			//TODO COLLISION
			//TODO COLLISION
			//TODO COLLISION
			//TODO COLLISION

			//WHILE LOOP
				arrow_before=arrow;
				arrow=arrow->next_update;
			//WHILE LOOP
			}else{
				// double k=(-4-angle_*2)/(game->arrows[i].dz);
				// game->arrows[i].x=k*game->arrows[i].dx+x_before;
				// game->arrows[i].y=k*game->arrows[i].dy+y_before;
				// game->arrows[i].z=-4-angle_*2 = k*dz+z_before
				double factor = -arrow->dz*10;
				if(factor>1)
					factor=1;
				arrow->z=-4-angle_*2*factor - random(.1,angle_);
				// arrow->z=-4-angle_*2*factor ;
				//RETIRER DES UPDATABLE
				if(arrow_before != NULL){
					arrow_before->next_update = arrow->next_update;
				}
				if( arrow==game->arrows_to_update){
					game->arrows_to_update=arrow->next_update;
				}
				Arrow* next=arrow->next_update;
				arrow->next_update=NULL;
				//WHILE LOOP
					// arrow_before=arrow;
					arrow=next;
				//WHILE LOOP
	
			}
		}
		// TODO
		// THERE IS A BUG HERE :
		// OLD ARROWS WONT UPDATE IF
		// A MORE RECENT ONE TOUCHED THE GROUND
}

static void fire_arrow_with_bow(Game* game){
	Arrow* to_add= malloc(sizeof(Arrow));

	double y_offset=-.5  + 2./180.*game->player->theta;
	double z_offset=-1.5 - 5./180.*game->player->theta;

	to_add->x=-game->player->x + y_offset*sin(game->player->phi/360.*2.*PI);
	to_add->y=-game->player->y + y_offset*cos(game->player->phi/360.*2.*PI);
	to_add->z=-game->player->z + z_offset;

	to_add->dx= .6*cos(-game->player->phi/360.*2.*PI)*(1-1.6*fabs(sin(-game->player->theta/360.*2.*PI)))*random(.85,.3) + .6*sin(game->player->phi/360.*2.*PI-180.)*random(-.015,.1);
	to_add->dy= .6*sin(-game->player->phi/360.*2.*PI)*(1-1.6*fabs(sin(-game->player->theta/360.*2.*PI)))*random(.85,.3) + .6*cos(game->player->phi/360.*2.*PI-180.)*random(-.015,.1);
	double dz;
	if(game->player->theta>0){
		//look up
		dz=-.4*sin(-game->player->theta/180.*PI);
	}else{
		//look down
		dz=-.1*sin(-game->player->theta/180.*PI);
		// if(dz>.0001)dz=.001;
		if(dz>0.0001)dz=0.0001;
	}
	to_add->dz=dz;

	//======================
	//UPDATE THE UPDATE_LIST (push front)
	//======================

	//arrow update list
	to_add->next_update=game->arrows_to_update;
	game->arrows_to_update = to_add;

	//arrow list
	to_add->next=game->arrows;
	to_add->prev=NULL;
	if(to_add->next!=NULL)
		to_add->next->prev=to_add;
	game->arrows = to_add;
	if(game->arrows_last==NULL){
		game->arrows_last = to_add;
	}
}

static void fire_arrow_with_sulfateuse(Game* game){
	Arrow* to_add= malloc(sizeof(Arrow));

	double x_offset=1;
	double y_offset=-.5  + 2./180.*game->player->theta;
	double z_offset;
	if(game->player->theta<0){
		x_offset=0;
		z_offset=-1.5 + 5./180.*game->player->theta;
	}else{
		z_offset=-1.5 - 10./180.*game->player->theta;
	}

	to_add->x=-game->player->x + y_offset*sin(game->player->phi/360.*2.*PI) + x_offset*cos(game->player->phi/360.*2.*PI);
	to_add->y=-game->player->y + y_offset*cos(game->player->phi/360.*2.*PI) - x_offset*sin(game->player->phi/360.*2.*PI);
	to_add->z=-game->player->z + z_offset;

	to_add->dx= .6*cos(-game->player->phi/360.*2.*PI)*(1-1.6*fabs(sin(-game->player->theta/360.*2.*PI)))*random(.85,.3) + .6*sin(game->player->phi/360.*2.*PI-180.)*random(-.015,.1);
	to_add->dy= .6*sin(-game->player->phi/360.*2.*PI)*(1-1.6*fabs(sin(-game->player->theta/360.*2.*PI)))*random(.85,.3) + .6*cos(game->player->phi/360.*2.*PI-180.)*random(-.015,.1);
	double dz;
	if(game->player->theta>0){
		//look up
		dz=-.4*sin(-game->player->theta/180.*PI);
	}else{
		//look down
		dz=-.05*sin(-game->player->theta/180.*PI);
		// if(dz>.0001)dz=.001;
		if(dz>0.0001)dz=0.0001;
	}
	to_add->dz=dz;

	//======================
	//UPDATE THE UPDATE_LIST (push front)
	//======================

	//arrow update list
	to_add->next_update=game->arrows_to_update;
	game->arrows_to_update = to_add;

	//arrow list
	to_add->next=game->arrows;
	to_add->prev=NULL;
	if(to_add->next!=NULL)
		to_add->next->prev=to_add;
	game->arrows = to_add;
	if(game->arrows_last==NULL){
		game->arrows_last = to_add;
	}
}

//UPDATE PART THAT IS COMMON TO ALL GAMES
void game_update(Game* game,int dt){

	time_+=dt/15.;
	camera_update(game->player,dt);
	fake_walk_update(game,dt);
	//=======================================================
	//=======================================================
	//=======================================================
	//======================FIRE UPDATE======================
	//=======================================================
	//=======================================================
	//=======================================================
		for(int i=0;i<dt;i++){

			if(game->trigger_state){
				//augmente jusqu'a trigger_value_MAX
				game->trigger_value+=1./trigger_value_MAX[game->weapon];
				if(game->trigger_value>1){
					// printf("trigger MAX\n");
					game->trigger_value=1;
				}
			}else{
				//diminue jusqu'a 0
				//!! VITESSE DIMINUTION PLUS GRANDE 
				game->trigger_value-=1.5/trigger_value_MAX[game->weapon];
				if(game->trigger_value<0){
					game->trigger_value=0;
				}
			}

			if(game->fire_value>0){
				game->fire_value-=1./fire_value_MAX[game->weapon];
				if(game->weapon==1 && game->fire_value<=0){
					//set trigger to 0 if using bow
					game->trigger_value=0;
				}
			}

			if(game->fire_state && game->trigger_value==1){
				if(game->fire_value<=0){
					game->fire_value+=1;
					if(game->weapon==1){
						fire_arrow_with_bow(game);
						// fire_arrow_with_sulfateuse(game);
					}else if(game->weapon>=2){
						fire_arrow_with_sulfateuse(game);
					}
				}
			}

			//UPDATE ARROWS 
			update_arrow(game);

		}
	//=======================================================
	//=======================================================
	//=======================================================


	// if(game->trigger_state==0 && game->trigger_value==game->trigger_value_MAX){
	// 	game->fire(game);
	// 	// MAYBE ???
	// 	// game->trigger_value=0;
	// 	//TODO :
	// 	//TO CHECK
	// }



	game->update(game,dt);
}





void game_sort_arrow_distance(Game * game){
	Arrow * arrow=game->arrows;
	Arrow * next;
	Arrow * to_cmp;
	int cont=1;
	while(arrow!=NULL){
		next=arrow->next;
		to_cmp=arrow->prev;
		while(to_cmp!=NULL & cont){
			if(arrow->dist < to_cmp->dist){
				//if to_cmp == head
				if(to_cmp == game->arrows){
				// printf("swap,%i\n",SDL_GetTicks());
					game->arrows=arrow;
				}
				//if to_cmp == last
				// WILL NOT HAPPEN (because to_cmp=arrow->prev)
				// else if(to_cmp == game->arrows_last){
				// 	game->arrows_last=arrow;
				// }

				//if arrow == head
				// WILL NEVER HAPPEN TOO (because to_cmp=arrow-prev would be NULL)
				// if(arrow==game->arrows){
				// 	game->arrows=to_cmp;
				// }
				//if arrow == last
				if(arrow==game->arrows_last){
					game->arrows_last=to_cmp;
				}

				//si consecutif
				if(arrow->prev==to_cmp){
					Arrow* next_1=arrow->next;

					arrow->prev=to_cmp->prev;
					arrow->next=to_cmp;

					to_cmp->prev=arrow;
					to_cmp->next=next_1;

					if(arrow->prev!=NULL)
						arrow->prev->next=arrow;
					// if(arrow->next!=NULL)
					// 	arrow->next->prev=arrow;
					// if(to_cmp->prev!=NULL)
					// 	to_cmp->prev->next=to_cmp;
					if(to_cmp->next!=NULL)
						to_cmp->next->prev=to_cmp;
				}else{
					Arrow* prev_1=arrow->prev;
					Arrow* next_1=arrow->next;

					arrow->prev=to_cmp->prev;
					arrow->next=to_cmp->next;

					to_cmp->prev=prev_1;
					to_cmp->next=next_1;

					if(arrow->prev!=NULL)
						arrow->prev->next=arrow;
					if(arrow->next!=NULL)
						arrow->next->prev=arrow;
					if(to_cmp->prev!=NULL)
						to_cmp->prev->next=to_cmp;
					if(to_cmp->next!=NULL)
						to_cmp->next->prev=to_cmp;
				}
				cont=0;
			}
			cont=1;
			to_cmp=to_cmp->prev;
		}
		arrow = next;
	}


}














int ARROW_MAX_HIGH_QUALITY = 400 ;
int ARROW_MAX_LOW_QUALITY = 1000 ;
int ARROW_MAX = 1000 ;
int arrow_high_quality_count;
int arrow_low_quality_count;
int arrow_count;

// int last_rendered_total_arrow;
void game_render_one_arrow(Arrow * arrow, Game* game){

	double alpha = atan2((arrow->y+game->player->y_culling),(arrow->x+game->player->x_culling))*180./PI;

	alpha = alpha+game->player->phi;
	while(alpha<=0)
		alpha+=360;
	while(alpha>360)
		alpha-=360;


	// if(alpha <game->player->angle||alpha>360-game->player->angle){
	double angle=80-arrow->dist*4.e-4;
	if(alpha <angle||alpha>360-angle){

		glRotated(arrow->beta,0,0,1);
		glRotated(arrow->alpha,0,1,0);
		if(arrow->dist<500){
			// if flying
			if(!(arrow->z<=-4)){
				glScaled(2,2,2);
				if(arrow_high_quality_count){
					draw_arrow_high_quality();
					arrow_high_quality_count--;
					// last_rendered_total_arrow++;
				}else{
					draw_arrow_low_quality();
				}
			//if not flying
			}else{
				if(arrow_high_quality_count){
					draw_arrow_ground_high_quality();
					// last_rendered_total_arrow++;
					arrow_high_quality_count--;
				}else{
					draw_arrow_ground_low_quality();
				}
			}
		}else{
			//les fleches dans les aires il faut toujours les dessiner
			if(!(arrow->z<=-4)){
				glScaled(2,2,2);
				draw_arrow_low_quality();
			}else if(arrow->dist<30000 && arrow_low_quality_count ){
				draw_arrow_ground_low_quality();
				// last_rendered_total_arrow++;
				arrow_low_quality_count--;
			}else if(arrow_count){
			// }else {
				draw_arrow_ground_very_low_quality();
				// last_rendered_total_arrow++;
				arrow_count--;
			}
		}
	}
}

void game_render_one_arrow_color(Arrow * arrow, Game* game){

	double alpha = atan2((arrow->y+game->player->y_culling),(arrow->x+game->player->x_culling))*180./PI;

	alpha = alpha+game->player->phi;
	while(alpha<=0)
		alpha+=360;
	while(alpha>360)
		alpha-=360;


	// if(alpha <game->player->angle||alpha>360-game->player->angle){
	if(alpha <80||alpha>360-80){

		glRotated(arrow->beta,0,0,1);
		glRotated(arrow->alpha,0,1,0);
		if(arrow->dist<500){
			// if flying
			if(!(arrow->z<=-4)){
				glScaled(2,2,2);
				if(arrow_high_quality_count){
					glColor4d(0,0,1,1);
					draw_arrow_high_quality();
					arrow_high_quality_count--;
				}else{
					glColor4d(0,1,1,1);
					draw_arrow_low_quality();
				}
			//if not flying
			}else{
				if(arrow_high_quality_count){
					glColor4d(0,0,1,1);
					draw_arrow_ground_high_quality();
					arrow_high_quality_count--;
				}else{
					#ifdef COLOR_DEBUG
						glColor4d(0,1,0,1);
					#endif
					draw_arrow_ground_low_quality();
				}
			}
		}else{
			//les fleches dans les aires il faut toujours les dessiner
			if(!(arrow->z<=-4)){
				glScaled(2,2,2);
				glColor4d(0,1,1,1);
				draw_arrow_low_quality();
			}else if(arrow->dist<30000 && arrow_low_quality_count ){
				glColor4d(0,1,0,1);
				draw_arrow_ground_low_quality();
				arrow_low_quality_count--;
			// }else if(arrow_count){
			}else {
				glColor4d(1,0,0,1);
				draw_arrow_ground_very_low_quality();
				arrow_count--;
			}
		}
	}
}


void game_render_one_mechant(Mechant * mechant){
	// double z=exp(-get_time_()*.007);
	// int angle=game->player->mFOV*.5*game->player->mAspectRatio;
	// // angle=60;

	// double alpha = atan2((y_guy+game->player->y),(x_guy+game->player->x))*180./PI;

	// alpha = alpha+game->player->phi;
	// while(alpha<=0)
	// 	alpha+=360;
	// while(alpha>360)
	// 	alpha-=360;


	// if(alpha <angle||alpha>360-angle){
	// 	double dist=(x_guy+game->player->x)*(x_guy+game->player->x)+(y_guy+game->player->y)*(y_guy+game->player->y);

	// 	int quality=0;
	// 	if(dist<20*20*20){
	// 		quality=2;
	// 	}else if(dist<50*20*20){
	// 		quality=1;
	// 	}else if(dist<300*20*20){
	// 		quality=0;
	// 	}else{
	// 		continue;
	// 	}

	// 	glColor4d(z,z,z,1);
	// 	glPushMatrix();
	// 		glTranslated(20*i,20*j,20*z);
	// 		draw_gentil(2*(100-(int)get_time_()%100)*.01,quality);
	// 	glPopMatrix();

	// 	glColor4d(0.9,0.9,0.9,1-z);
	// 	glPushMatrix();
	// 		glTranslated(0,0,-10);
	// 		glScaled(1,1,-1);
	// 		glTranslated(20*i,20*j,20*z);
	// 		draw_gentil(2*(100-(int)get_time_()%100)*.01,quality);
	// 	glPopMatrix();
	// }
}


void game_render(Game* game){
	game->render(game);
	int time_render_begin = SDL_GetTicks();
	
	//RENDER AN INVISIBLE PLANE FOR GROUND DEPTH
	glPushMatrix();
		glTranslated(-game->player->x,-game->player->y,0);
		glTranslated(0,0,-4);
		glRotated(90,0,1,0);
		glColor4d(0,0,0,0);
		draw_face(600,0);
	glPopMatrix();
	GLfloat bkColor[3];
	glGetFloatv(GL_COLOR_CLEAR_VALUE, bkColor);

	//=======================LOOP TEST=========================
	//=======================LOOP TEST=========================
	//=======================LOOP TEST=========================
	// glPushMatrix();
	// 	glTranslated(-game->player->x,-game->player->y,-4);
	// 	glRotated(90,0,1,0);
	// 	glScaled(1,game->world_y_size,game->world_x_size);
	// 	glLineWidth(5);
	// 	glColor4d(0,0,1,1);
	// 	draw_square(.5,0);
	// glPopMatrix();


	Arrow* arrow;
	Mechant* mechant;

	//REFLEXIONS
	glDepthFunc(GL_GREATER);
	glDepthMask(GL_FALSE);
	glPushMatrix();
		//TO THE GROUND
		glTranslated(0,0,-8);


		//=======================ARROWS=======================
		//=======================ARROWS=======================
		//=======================ARROWS=======================
		if(game->sorting){
			if(game->next_sort_time<SDL_GetTicks()){
				// printf("SORT!\n");
				game_sort_arrow_distance(game);
				game->next_sort_time=SDL_GetTicks()+1000;
			}
		}
		double r_color=.5+.5*bkColor[0];
		double g_color=0+.5*bkColor[1];
		double b_color=0+.5*bkColor[2];
		glColor4d(r_color,g_color,b_color,1);
		arrow=game->arrows;
		void (*draw_arrow)(Arrow * arrow, Game* game);
		if(game->color_debug){
			draw_arrow=game_render_one_arrow_color;
		}else{
			draw_arrow=game_render_one_arrow;
		}
		int i=0;
		// double last_rendered_total_arrow_copy=last_rendered_total_arrow;
		// last_rendered_total_arrow=0;
		while(arrow!=NULL){
			// glColor4d(r_color,g_color,b_color,1-i/last_rendered_total_arrow_copy);
			// i++;
			
			double xx=arrow->x+game->player->x;
			double yy=arrow->y+game->player->y;
			double zz=arrow->z+game->player->z;
			arrow->dist=xx*xx+yy*yy+zz*zz;

			if(arrow->dist<90000){
				// glDepthFunc(GL_ALWAYS);//debug
				glPushMatrix();
					glTranslated(arrow->x,arrow->y,-arrow->z);
					glScaled(.5,.5,-.5);
					draw_arrow(arrow,game);
				glPopMatrix();
			}
			arrow=arrow->next;
		}
		arrow_high_quality_count=ARROW_MAX_HIGH_QUALITY;
		arrow_low_quality_count=ARROW_MAX_LOW_QUALITY;
		arrow_count=ARROW_MAX;
		//======================MECHANTS======================
		//======================MECHANTS======================
		//======================MECHANTS======================
		mechant=game->mechants;
		while(mechant!=NULL){
			// WORLD LOOP
			while(mechant->x+game->player->x+game->world_x_size/2.>0)
				mechant->x-=game->world_x_size;
			while(mechant->x+game->player->x+game->world_x_size/2.<0)
				mechant->x+=game->world_x_size;
			while(mechant->y+game->player->y+game->world_y_size/2.>0)
				mechant->y-=game->world_y_size;
			while(mechant->y+game->player->y+game->world_y_size/2.<0)
				mechant->y+=game->world_y_size;

			double xx=mechant->x+game->player->x;
			double yy=mechant->y+game->player->y;
			double zz=mechant->z+game->player->z;
			mechant->dist=xx*xx+yy*yy+zz*zz;

			mechant=mechant->next;
		}

	glPopMatrix();
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);




	//REAL WORLD
	r_color=1;
	g_color=0;
	b_color=0;
	glColor4d(r_color,g_color,b_color,1);
	arrow=game->arrows;
	// i=0;
	while(arrow!=NULL){
		if(arrow->dist<90000){
			// glColor4d(r_color,g_color,b_color,1-i/last_rendered_total_arrow_copy);
			// i++;
			glPushMatrix();
				glTranslated(arrow->x,arrow->y,arrow->z);
				glScaled(.5,.5,.5);
				draw_arrow(arrow,game);
			glPopMatrix();
		}
		arrow=arrow->next;
	}
	arrow_high_quality_count=ARROW_MAX_HIGH_QUALITY;
	arrow_low_quality_count=ARROW_MAX_LOW_QUALITY;
	arrow_count=ARROW_MAX;

	int duration=SDL_GetTicks()-time_render_begin;
	if(duration>20){
		// printf("reducing arrow limits\n");
		ARROW_MAX_HIGH_QUALITY-=random(1,10)+ARROW_MAX_HIGH_QUALITY/16.;
		ARROW_MAX_LOW_QUALITY -=random(1,10)+ARROW_MAX_LOW_QUALITY/16.;
		ARROW_MAX             -=random(1,10)+ARROW_MAX/16.;
		if(ARROW_MAX_HIGH_QUALITY<70)ARROW_MAX_HIGH_QUALITY=70;
		if(ARROW_MAX_LOW_QUALITY<70)ARROW_MAX_LOW_QUALITY=70;
		// if(ARROW_MAX<50)ARROW_MAX=50;
		// printf("%i,%i,%i\n",ARROW_MAX_HIGH_QUALITY,ARROW_MAX_LOW_QUALITY,ARROW_MAX);

	}else if(duration<15){
		// printf("unreducing arrow limits\n");
		// ARROW_MAX_HIGH_QUALITY+=log(1+ARROW_MAX_HIGH_QUALITY*.2);
		// ARROW_MAX_LOW_QUALITY+=log(1+ARROW_MAX_LOW_QUALITY*.2);
		// ARROW_MAX+=log(1+ARROW_MAX*.2);
		ARROW_MAX_HIGH_QUALITY+=random(10,10)+ARROW_MAX_HIGH_QUALITY/128.;
		ARROW_MAX_LOW_QUALITY +=random(10,10)+ARROW_MAX_LOW_QUALITY/128.;
		ARROW_MAX             +=random(10,10)+ARROW_MAX/128.;
		if(ARROW_MAX_HIGH_QUALITY>10000)ARROW_MAX_HIGH_QUALITY=10000;
		if(ARROW_MAX_LOW_QUALITY>10000)ARROW_MAX_LOW_QUALITY=10000;
		if(ARROW_MAX>10000)ARROW_MAX=10000;
		// if(ARROW_MAX!=10000)
		// 	printf("%i,%i,%i\n",ARROW_MAX_HIGH_QUALITY,ARROW_MAX_LOW_QUALITY,ARROW_MAX);
	}

}

void fire(Game* game,int state){
	game->fire_state=state;
}

void trigger(Game* game,int state){
	game->trigger_state=state;
	// if(state)
	// 	printf("trigger_ON\n");
	// else
	// 	printf("trigger_OFF\n");
}

void game_pause(Game * game,int state){
	if(state){
		//TODO PAUSE MUSIC
	}else{
		//TODO UNPAUSE MUSIC
	}
}















Game* initGame(Camera* player){

	//no weapon
	trigger_value_MAX[0]=1;//avoid 1./0.
	fire_value_MAX[0]   =1;//avoid 1./0.
	//bow
	trigger_value_MAX[1]=200;
	fire_value_MAX[1]   =300;
	// fire_value_MAX[1]   =1800;
	// la sulfateuse
	trigger_value_MAX[2]=400;
	fire_value_MAX[2]   =100;
	// la sulfateuse BOURRIN
	trigger_value_MAX[3]=400;
	fire_value_MAX[3]   =10;
	// fire_value_MAX[3]   =1;

	draw_init();
	// audio_init();

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
	glDepthFunc(GL_LESS);//GL_NEVER, GL_LESS, GL_EQUAL, GL_LEQUAL, GL_GREATER, GL_NOTEQUAL, GL_GEQUAL, GL_ALWAYS, GL_LESS

	glEnable(GL_POINT_SMOOTH);
	glDisable( GL_LINE_SMOOTH );
	glDisable( GL_POLYGON_SMOOTH ); // THIS MAKES A NICE ARTEFACT :¬D

	
	glHint(GL_LINE_SMOOTH_HINT,GL_FASTEST);
	glHint(GL_POLYGON_SMOOTH_HINT,GL_FASTEST);
	glHint(GL_TEXTURE_COMPRESSION_HINT,GL_FASTEST);
	glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,GL_FASTEST);

	//GL_FASTEST, GL_NICEST, and GL_DONT_CARE
	// glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
	// glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );

	// glEnable(GL_AUTO_NORMAL);
	// glEnable(GL_NORMALIZE);


	Game* game = malloc(sizeof(Game));

	game->update=intro_update;
	game->render=intro_render;

	game->player=player;

	game->HUD_render=HUD;

	game->color_debug=0;
	game->sorting=1;
	game->next_sort_time=SDL_GetTicks();

	game->trigger=trigger;
	game->trigger_value=0;
	game->fire=fire;
	game->fire_value=0;
	game->weapon=0;

	game->mechants=NULL;

	game->arrows=NULL;
	game->arrows_last=NULL;
	game->arrows_to_update=NULL;
	// game->audio= audio_new (PLAYER_AMBIENT|PLAYER_LOOP);
	// audio_playMusic(game->audio,"music/Goto80_gopho_loop.ogg");

	//===========================
	// 
	//  _|_|_|_|_|  _|_|_|_|    _|_|_|  _|_|_|_|_|  _|_|_|  _|      _|    _|_|_|  
	//      _|      _|        _|            _|        _|    _|_|    _|  _|        
	//      _|      _|_|_|      _|_|        _|        _|    _|  _|  _|  _|  _|_|  
	//      _|      _|              _|      _|        _|    _|    _|_|  _|    _|  
	//      _|      _|_|_|_|  _|_|_|        _|      _|_|_|  _|      _|    _|_|_|  
	//                                                                            
	//THIS IS FOR TESTING PURPOSE
	//===========================

	game->world_x_size=600;
	game->world_y_size=600;

	// glClearColor( 1., 1., 1., 1. );
	game->update=ingame_level2_update;
	game->render=ingame_level2_render;


	//===========================
	//===========================


	return game;
}
