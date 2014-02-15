
#ifndef DRAW_H
#define DRAW_H

typedef struct Ennemy{
	double x,y,z;
	double rho,phi,theta;
	struct Ennemy* next;
}Ennemy;

void draw_cheni(double size,double noise, int count);

void draw_cube(double size,double noise);
void draw_cube_simple(double size);
void draw_face(double size,double noise);
void draw_square(double size,double noise);
void draw_sphere(double size,double time,int detail);
void draw_sphere2(double size,double time_,double noise);
void draw_init();

void draw_bow(double noise,double force);
void draw_bow_v2(double noise,double force);
void draw_bow_v3(double noise,double force);
void draw_hand(double force,double distance,int side_view);
void draw_bow_to_take(double noise,double force);
void draw_arrow_high_quality();
void draw_arrow_low_quality();
void draw_arrow_ground_high_quality();
void draw_arrow_ground_low_quality();
void draw_arrow_ground_very_low_quality();

void draw_sulfateuse(double noise,double angle, int color);


void draw_gentil(double noise,int detail);
void draw_mechant(double noise,int detail);

void draw_wing(double noise,int detail);

#endif