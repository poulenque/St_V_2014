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

#define GOOD 1
#define BAD 0

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
	game->sorting_arrow=NULL;
	game->sorting_next=NULL;
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

void clear_particles(Game* game){
	Particle* p = game->particles;
	Particle* pp;
	while(p!=NULL){
		pp=p->next;	
		free(p);
		p=pp;
	}
	game->particles=NULL;
	game->particles_update=NULL;
}


static String3d* str;
String3d* get_str(){
	return str;
}

void game_insert_Mechant(Game* game, Mechant * mechant){
	mechant->next=game->mechants;
	mechant->prev=NULL;
	if(mechant->next!=NULL)
		mechant->next->prev=mechant;
	game->mechants = mechant;
	if(game->mechants_last==NULL){
		game->mechants_last = mechant;
	}
}

void game_add_explosion(Game* game,int good,int count,double x,double y, double z,double dx,double dy, double dz){
	for(int i=0;i<count;i++){
		Particle * p = malloc (sizeof(Particle));

		p->next=game->particles;
		p->next_update=game->particles_update;

		p->prev=NULL;
		p->prev_update=NULL;

		if(p->next!=NULL)
			p->next->prev=p;
		if(p->next_update!=NULL)
			p->next_update->prev_update=p;

		game->particles=p;
		game->particles_update=p;

		p->x=x+5*random(0,1);
		p->y=y+5*random(0,1);
		p->z=z+5*random(0,1);
		if(good){
			p->z=z+10*random(0,1);
		}

		p->dx=(.8+.2*random_simple())*dx+0.02*random(0,1);
		p->dy=(.8+.2*random_simple())*dy+0.02*random(0,1);
		p->dz=(.8+.2*random_simple())*dz+0.02*random(1,1);
		if(good){
			p->dz+=.1;
		}

		p->good=good;
		//TODO
		//TODO
		//TODO
		//TODO
		//TODO
		//TODO
		//TODO
		//TODO
		//TODO
		//TODO
		//TODO
		//TODO
		//TODO
		//TODO
		//TODO
		//TODO
		//TODO
		//TODO
		//TODO
		//TODO
		//TODO
		//TODO
		//TODO
		//TODO
		//TODO
	}
}

void game_remove_mechant(Game * game,Mechant * mechant){
	//if head
	if(mechant == game->mechants){
		game->mechants=mechant->next;
	}
	if(mechant == game->mechants_last){
		game->mechants_last=mechant->prev;
	}
	if(mechant->prev != NULL){
		mechant->prev->next = mechant->next;
	}
	if(mechant->next != NULL){
		mechant->next->prev = mechant->prev;
	}
	free(mechant);
}
void game_remove_particle(Game * game,Particle * p){
	//if head
	if(p == game->particles){
		game->particles=p->next;
	}
	if(p == game->particles_update){
		game->particles_update=p->next;
	}

	if(p->prev != NULL){
		p->prev->next = p->next;
	}
	if(p->next != NULL){
		p->next->prev = p->prev;
	}

	if(p->prev_update != NULL){
		p->prev_update->next_update = p->next_update;
	}
	if(p->next_update != NULL){
		p->next_update->prev_update = p->prev_update;
	}
	free(p);
}
void update_one_particle(Particle * p){
	p->x+=p->dx;
	p->y+=p->dy;
	p->z+=p->dz;
	
	p->dx*=0.997;
	p->dy*=0.997;
	p->dz*=0.997;

	if(p->good){
		p->dz-=0.0005;
	}else{
		p->dz+=0.0002;
	}
	if (p->z < -3.95){
		p->dz=-.6*p->dz;
		p->z=-3.95;
	}
}

void update_particles(Game* game){
	Particle * p = game->particles_update;
	while(p!=NULL){
		Particle * next=p->next_update;
		update_one_particle(p);
		double v=fabs(p->dx)+fabs(p->dy)+fabs(p->dz);
		if(v<0.02 && p->z <= -3.9){
			//retirer
			if(p==game->particles_update){
				game->particles_update=p->next_update;
			}
			if(p->prev_update!=NULL){
				p->prev_update->next_update=p->next_update;
			}
			if(p->next_update!=NULL){
				p->next_update->prev_update=p->prev_update;
			}
			p->next_update=NULL;
			p->prev_update=NULL;
		}
		if(p->z>100){
			game_remove_particle(game,p);
		}
		p=next;
	}
}

static void update_mechant(Game* game){
	Mechant* mechant = game->mechants;
	while(mechant!=NULL){
		if(mechant->update!=NULL){
			mechant->update(mechant);
		}
		mechant = mechant->next;
	}
}

static double trigger_value_MAX[5];
static double fire_value_MAX[5]   ;


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
				Mechant * mechant = game->mechants;
				while(mechant !=NULL){
					Mechant * next = mechant->next;
					if(arrow->z<5){
						double dist_x=mechant->x - arrow->x;
						double dist_y=mechant->y - arrow->y;
						double dist_z=mechant->z - arrow->z;
						// double dist =dist_x*dist_x+dist_y*dist_y+dist_z*dist_z;
						double dist =abs(dist_x)+abs(dist_y)+abs(dist_z);
						if(dist<10){
							game_add_explosion(game,GOOD,50, mechant->x,mechant->y,mechant->z,.3*arrow->dx,.3*arrow->dy,.3*arrow->dz);
							// game_remove_mechant(game,mechant);
							double rayon = random(300,0);
							double angle = random(0,2*PI);
							mechant->x=-game->player->x+rayon*cos(angle);
							mechant->y=-game->player->y+rayon*sin(angle);
							mechant->z=0;

							mechant->dx=random(0,.05);
							mechant->dy=random(0,.05);
							mechant->dz=0;
						}
					}
					mechant = next;
				}
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

void update_interraction_mechant_player(Game* game){
	Mechant * mechant = game->mechants;
	while(mechant !=NULL){
		Mechant * next = mechant->next;
		double dist_x=mechant->x + game->player->x + .05*game->player->dx;
		double dist_y=mechant->y + game->player->y + .05*game->player->dy;
		double dist_z=mechant->z + game->player->z + .05*game->player->dz;
		double dist =dist_x*dist_x+dist_y*dist_y+dist_z*dist_z;
		dist_x=mechant->x + game->player->x;
		dist_y=mechant->y + game->player->y;
		dist_z=mechant->z + game->player->z;
		double dist2 =dist_x*dist_x+dist_y*dist_y+dist_z*dist_z;
			// double dist =abs(dist_x)+abs(dist_y)+abs(dist_z);
			if(dist<20 || dist2<20){
				game_add_explosion(game,BAD,50*6, mechant->x,mechant->y,mechant->z,-.0015*game->player->dx,-.0015*game->player->dy,-.0015*game->player->dz);
				// game_remove_mechant(game,mechant);
				double rayon = random(300,0);
				double angle = random(0,2*PI);
				mechant->x=-game->player->x+rayon*cos(angle);
				mechant->y=-game->player->y+rayon*sin(angle);
				mechant->z=0;

				mechant->dx=random(0,.05);
				mechant->dy=random(0,.05);
				mechant->dz=0;
			}
		mechant = next;
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
				if((game->weapon==1 || game->weapon==4) && game->fire_value<=0){
					//set trigger to 0 if using bow
					game->trigger_value=0;
				}
			}

			if(game->fire_state && game->trigger_value==1){
				if(game->fire_value<=0){
					game->fire_value+=1;
					if(game->weapon==1){
						fire_arrow_with_bow(game);
					}else if(game->weapon==2||game->weapon==3){
						fire_arrow_with_sulfateuse(game);
					}else if(game->weapon==4){
						fire_arrow_with_bow(game);
						fire_arrow_with_bow(game);
						fire_arrow_with_bow(game);
					}
				}
			}

			//UPDATE ARROWS 
			update_arrow(game);
			update_mechant(game);
			update_particles(game);

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

	//INTERRACT_MECHANT_PLAYER
	update_interraction_mechant_player(game);

	game->update(game,dt);
}





void game_sort_arrow_distance(Game * game){
	Arrow * sort_arrow=game->sorting_arrow;
	Arrow * sort_next=game->sorting_next;

	if(sort_arrow==NULL){
		sort_arrow=game->arrows;
	}
	Arrow * to_cmp;
	int continuing=1;
	int time_before= SDL_GetTicks();
	while(sort_arrow!=NULL){
		// sort_count++;
		sort_next=sort_arrow->next;
		to_cmp=sort_arrow->prev;
		while(to_cmp!=NULL & continuing){
			if(sort_arrow->dist < to_cmp->dist){

				// if to_cmp == heads
				if(to_cmp == game->arrows){
				// printf("swap,%i\n",SDL_GetTicks());
					game->arrows=sort_arrow;
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
				if(sort_arrow==game->arrows_last){
					game->arrows_last=to_cmp;
				}

				//si consecutif
				if(sort_arrow->prev==to_cmp){
					Arrow* next_1=sort_arrow->next;

					sort_arrow->prev=to_cmp->prev;
					sort_arrow->next=to_cmp;

					to_cmp->prev=sort_arrow;
					to_cmp->next=next_1;

					if(sort_arrow->prev!=NULL)
						sort_arrow->prev->next=sort_arrow;
					// if(arrow->next!=NULL)
					// 	arrow->next->prev=arrow;
					// if(to_cmp->prev!=NULL)
					// 	to_cmp->prev->next=to_cmp;
					if(to_cmp->next!=NULL)
						to_cmp->next->prev=to_cmp;
				}else{
					Arrow* prev_1=sort_arrow->prev;
					Arrow* next_1=sort_arrow->next;

					sort_arrow->prev=to_cmp->prev;
					sort_arrow->next=to_cmp->next;

					to_cmp->prev=prev_1;
					to_cmp->next=next_1;

					if(sort_arrow->prev!=NULL)
						sort_arrow->prev->next=sort_arrow;
					if(sort_arrow->next!=NULL)
						sort_arrow->next->prev=sort_arrow;
					if(to_cmp->prev!=NULL)
						to_cmp->prev->next=to_cmp;
					if(to_cmp->next!=NULL)
						to_cmp->next->prev=to_cmp;
				}
				continuing=0;
				// break;
			}
			continuing=1;
			to_cmp=to_cmp->prev;
		}
		sort_arrow = sort_next;
		if(SDL_GetTicks()-time_before > 2){
			break;
		}else{
			// sort_count=0;
		}
	}


	// printf("arrow count : %i\n duration : %i\n\n",sort_count , SDL_GetTicks()-time_before);


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

		if(arrow->dist<500){
			// if flying
			if(!(arrow->z<=-4)){
				if(arrow_high_quality_count){


					if(arrow->dist<200){
						int n=5;
						for(int i=0;i<n;i++){
							glPushMatrix();
								glTranslated(
									-2*i*arrow->dx,
									-2*i*arrow->dy,
									-2*i*arrow->dz);
								glRotated(arrow->beta,0,0,1);
								glRotated(arrow->alpha,0,1,0);
								draw_arrow_high_quality();
							glPopMatrix();
							if(i == 0)
								glAccum(GL_LOAD, 1.0 / n);
							else
								glAccum(GL_ACCUM, 1.0 / n);
						}
						glAccum(GL_RETURN, 1.0);
					}else{
						glPushMatrix();
							glRotated(arrow->beta,0,0,1);
							glRotated(arrow->alpha,0,1,0);
							draw_arrow_high_quality();
						glPopMatrix();

					}


					arrow_high_quality_count--;
					// last_rendered_total_arrow++;
				}else{
					glRotated(arrow->beta,0,0,1);
					glRotated(arrow->alpha,0,1,0);
					draw_arrow_low_quality();
				}
			//if not flying
			}else{
				glRotated(arrow->beta,0,0,1);
				glRotated(arrow->alpha,0,1,0);
				glScaled(.5,.5,.5);
				if(arrow_high_quality_count){
					draw_arrow_ground_high_quality();
					// last_rendered_total_arrow++;
					arrow_high_quality_count--;
				}else{
					draw_arrow_ground_low_quality();
				}
			}
		}else{
		glRotated(arrow->beta,0,0,1);
		glRotated(arrow->alpha,0,1,0);
			//les fleches dans les aires il faut toujours les dessiner
			if(!(arrow->z<=-4)){
				draw_arrow_low_quality();
			}else if(arrow->dist<30000 && arrow_low_quality_count ){
				glScaled(.5,.5,.5);
				draw_arrow_ground_low_quality();
				// last_rendered_total_arrow++;
				arrow_low_quality_count--;
			}else if(arrow_count){
				glScaled(.5,.5,.5);
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
				glScaled(.5,.5,.5);
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
				glColor4d(0,1,1,1);
				draw_arrow_low_quality();
			}else if(arrow->dist<30000 && arrow_low_quality_count ){
				glScaled(.5,.5,.5);
				glColor4d(0,1,0,1);
				draw_arrow_ground_low_quality();
				arrow_low_quality_count--;
			// }else if(arrow_count){
			}else {
				glScaled(.5,.5,.5);
				glColor4d(1,0,0,1);
				draw_arrow_ground_very_low_quality();
				arrow_count--;
			}
		}
	}
}


void game_render_one_mechant(Mechant * mechant, Game * game){
	// double z=exp(-get_time_()*.007);



	int quality=0;
	if(mechant->dist<20*20*20){
		quality=2;
	}else if(mechant->dist<50*20*20){
		quality=1;
	}else if(mechant->dist<300*20*20){
		quality=0;
	}else{
		return;
	}

	double alpha = atan2((mechant->y+game->player->y_culling),(mechant->x+game->player->x_culling))*180./PI;

	alpha = alpha+game->player->phi;
	while(alpha<=0)
		alpha+=360;
	while(alpha>360)
		alpha-=360;


	if(alpha <game->player->angle||alpha>360-game->player->angle){
	// if(alpha <80||alpha>360-80){
		// glColor4d(z,z,z,1);
		// glPushMatrix();
			// glTranslated(mechant->x,mechant->y,mechant->z+8);
			// glTranslated(mechant->x,mechant->y,mechant->z);
		if(mechant->type==0){
			draw_gentil(audioplayer_getAmplitude(game->audio,.05),quality);
		}else{

		}
			// draw_gentil(2*(100-(int)get_time_()%100)*.01,quality);
		// glPopMatrix();
	}
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
			game_sort_arrow_distance(game);
		}
		double r_color=.5+.5*bkColor[0];
		double g_color=0+.5*bkColor[1];
		double b_color=0+.5*bkColor[2];
		if(game->stereo){
			r_color=.35+.5*bkColor[0];
			g_color=.1+.5*bkColor[1];
			b_color=.1+.5*bkColor[2];

		}

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
					glScaled(1,1,-1);
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

			glPushMatrix();
				glScaled(1,1,-1);
				glTranslated(mechant->x,mechant->y,mechant->z+1);
				game_render_one_mechant(mechant,game);
			glPopMatrix();

			mechant=mechant->next;
		}

	glPopMatrix();
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);




	//REAL WORLD
	r_color=1;
	g_color=0;
	b_color=0;
	if(game->stereo){
		r_color=.7;
		g_color=.2;
		b_color=.2;
	}
	glColor4d(r_color,g_color,b_color,1);
	arrow=game->arrows;
	// i=0;
	while(arrow!=NULL){
		if(arrow->dist<90000){
			// glColor4d(r_color,g_color,b_color,1-i/last_rendered_total_arrow_copy);
			// i++;
			glPushMatrix();
				glTranslated(arrow->x,arrow->y,arrow->z);
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

		glPushMatrix();
			// glScaled(1,1,-1);
			glTranslated(mechant->x,mechant->y,mechant->z+1);
			game_render_one_mechant(mechant,game);
		glPopMatrix();

		mechant=mechant->next;
	}




	Particle* p=game->particles;
	glDisable(GL_POINT_SMOOTH);
	glPointSize(7);
	while(p!=NULL){
		glBegin(GL_POINTS);
			glVertex3d(p->x,p->y,p->z);
		glEnd();
		p=p->next;
	}
	glEnable(GL_POINT_SMOOTH);




	//==================================================
	//==================================================
	//==================================================
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
}

void game_pause(Game * game,int state){
	if(state){
		printf("PAUSE\n");
		audioplayer_pause(game->audio);
		//TODO PAUSE MUSIC
	}else{
		printf("PLAY\n");
		audioplayer_play(game->audio);
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
	trigger_value_MAX[4]=200;
	fire_value_MAX[4]   =300;
	// fire_value_MAX[1]   =1800;
	// la sulfateuse
	trigger_value_MAX[2]=400;
	fire_value_MAX[2]   =100;
	// la sulfateuse BOURRIN
	trigger_value_MAX[3]=400;
	fire_value_MAX[3]   =10;
	// fire_value_MAX[3]   =1;

	draw_init();
	audio_init();


	str = new_string3d();
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

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


	game->player=player;

	game->HUD_render=HUD;

	game->color_debug=0;
	game->sorting=1;
	game->sorting_arrow=NULL;
	game->sorting_next=NULL;


	game->trigger=trigger;
	game->trigger_value=0;
	game->fire=fire;
	game->fire_value=0;
	game->weapon=0;

	game->mechants=NULL;
	game->particles=NULL;
	game->particles_update=NULL;

	game->arrows=NULL;
	game->arrows_last=NULL;
	game->arrows_to_update=NULL;
	game->audio= new_audioplayer();

	intro_setup(game);

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

	// audio_playMusic(game->audio,"music/Goto80_gopho_loop.ogg");
	// audio_playMusic(game->audio,"music/short_test.ogg");
	// audio_playMusic(game->audio,"music/INEXISTANT_FILE");
	// audio_playMusic(game->audio,"music/Goto80_gopho.ogg");

	// ingame_level2_setup(game);
	game->world_x_size=600;
	game->world_y_size=600;
	// audioplayer_set_next(game->audio,"music/Goto80_gopho_loop.ogg");

	// Mechant * mechant = malloc(sizeof(mechant));
	// mechant->x =0;
	// mechant->y =0;
	// mechant->z =0;
	// mechant->update =NULL;

	// game_insert_Mechant(game, mechant);


	// glClearColor( 1., 1., 1., 1. );
	// game->update=ingame_level1_update;
	// game->render=ingame_level1_render;

	// game->update=ingame_level3_update;
	// game->render=ingame_level3_render;

	//===========================
	//===========================


	return game;
}
