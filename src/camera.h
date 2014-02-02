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

// void ApplyLeftFrustum();
// void ApplyRightFrustum();
// void look();
	
// void focusMove(double const& var);
// void perspectiveMove(double const& var);
// void motionBlurMove(double const& var);
// double getMotionBlur();
// double getPerspective();
// double getFocus();
// int getCompassState();
	
// void dispRepere();
// void dispInterface();
	
// void update(double deltaT);
	
// double fast;
// int showBoussole;
// bool showTerminal;

// void PanelBackground(int );

// void message(string const&,double timedisp = 1500);


// string messagestr;
// string leftPanelstr;
// string rightPanelstr;
// string titlestr;

// Vect posLIGHT;

// Vect w,s,q;
// double camSpeed;
// double thetaInterface;
// double phiInterface;
// double rhoInterface;
// double motionBlur;
// double dmotionBlur;

#endif