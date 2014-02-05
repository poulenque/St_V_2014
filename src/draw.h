
#ifndef DRAW_H
#define DRAW_H

typedef struct Ennemy{
	double x,y,z;
	double rho,phi,theta;
	struct Ennemy* next;
}Ennemy;

void draw_cube(double size,double noise);
void draw_face(double size,double noise);
void draw_sphere(double size,double time,int detail);
void draw_sphere2(double size,double time_,double noise);
void draw_init();

void draw_bow(double noise,double force);
void draw_hand(double force,double distance,int side_view);
void draw_bow_to_take(double noise,double force);
void draw_arrow(double noise);

void draw_gentil(double noise,int detail);
void draw_mechant(double noise,int detail);

void draw_wing(double noise,int detail);

#endif