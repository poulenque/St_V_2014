#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include "string3d.h"
#include "game.h"

typedef struct Game Game;

typedef	struct Camera {
	// double interface_theta;
	// double interface_phi;
	// double interface_rho;
	// String3d* interface_txt;


	unsigned int shader_id_dummy;
	unsigned int shader_id_dof;
	unsigned int shader_dof_color_id;
	//
	unsigned int frame_buffer_id;
	unsigned int color_tex_id;
	unsigned int depth_tex_id;
	// unsigned int depth_tex_id;
	//

	Game* game;

	double theta;
	double phi;
	double rho;

	double dtheta;
	double dphi;
	double drho;

	double ddtheta;
	double ddphi;
	double ddrho;

	double x;
	double y;
	double z;

	double dx;
	double dy;
	double dz;

	double ddx;
	double ddy;
	double ddz;

	//stereoCam
	double mConvergence;
	double mEyeSeparation;
	double mAspectRatio;
	double mFOV;
	double mNearClippingDistance;
	double mFarClippingDistance;

	int avance;

	double angle;//for object culling
	double x_culling;
	double y_culling;


} Camera;

Camera* new_Camera();

void camera_update(Camera* c,int dt);

void camera_render(Camera* c);
void camera_render_stereo(Camera* c);

//this will straf relatively to the camera (dy and dx are relative to the camera)
void camera_move    (Camera* c,double dx ,double dy ,double dz );
void camera_move_acc(Camera* c,double ddx,double ddy,double ddz);

void camera_rotate    (Camera* c,double dtheta ,double dphi ,double drho );
void camera_rotate_acc(Camera* c,double ddtheta,double ddphi,double ddrho);

#endif