#include "camera.h"
#include <math.h>
#include <GL/glew.h>
// #include <GL/freeglut.h>
#include "constants.h"

double hyperbolicLimit(const double nb,const double limit){
	return (nb*limit)/sqrt(limit*limit+nb*nb);
}

void camera_move (Camera* c,double dx ,double dy ,double dz ){
	c->dx=dx*cos(-c->phi/360*2*PI)  +  dy*cos(-c->phi/360*2*PI+PI/2);
	c->dy=dx*sin(-c->phi/360*2*PI)  +  dy*sin(-c->phi/360*2*PI+PI/2);
	c->dz=dz;
	c->dtheta+=dx/50.;
}

void camera_move_acc(Camera* c,double ddx,double ddy,double ddz){
	c->ddx+=ddx*cos(-c->phi/360*2*PI)  +  ddy*cos(-c->phi/360*2*PI+PI/2);
	c->ddy+=ddx*sin(-c->phi/360*2*PI)  +  ddy*sin(-c->phi/360*2*PI+PI/2);
	c->ddz+=ddz;
	c->dtheta+=ddx/50.;
	c->drho+=ddy/50.;
}

void camera_rotate    (Camera* c,double dtheta ,double dphi ,double drho ){
	c->dtheta+=dtheta;
	c->dphi+=dphi;
	c->drho+=drho + dphi;
}
void camera_rotate_acc(Camera* c,double ddtheta,double ddphi,double ddrho){
	c->ddtheta+=ddtheta;
	c->ddphi+=ddphi;
	c->ddrho+=ddrho + ddphi/4.;
}


Camera* new_Camera(){

	Camera* c= malloc(sizeof(Camera));


	c->theta=0;
	c->phi=0;
	c->rho=0;

	c->dtheta=0;
	c->dphi=0;
	c->drho=0;

	c->ddtheta=0;
	c->ddphi=0;
	c->ddrho=0;

	c->x=0;
	c->y=0;
	c->z=0;

	c->dx=0;
	c->dy=0;
	c->dz=0;

	c->ddx=0;
	c->ddy=0;
	c->ddz=0;

	//stereoCam
	c->mConvergence=1000;
	c->mEyeSeparation=.1;

	c->mAspectRatio=4./3;
	c->mFOV=90;
	c->mNearClippingDistance=.01;
	c->mFarClippingDistance=1000.;

	// c->interface_theta=0;
	// c->interface_phi=0;
	// c->interface_rho=0;
	// c->interface_txt=new_string3d();
	// string3d_setTxt(c->interface_txt,"");
	// c->interface_txt->size=.02;
	// c->interface_txt->phi=45;
	// c->interface_txt->z=.2;

	return c;
}


void camera_look(Camera* c){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double vitesse_avant =
						sqrt(
							pow(
								c->dx*cos(-c->phi/360*2*PI) 
								// +c->dy*cos(-c->phi/360*2*PI+PI/2)
								,2)
							+
							pow(
								c->dx*sin(-c->phi/360*2*PI)
								// +c->dy*sin(-c->phi/360*2*PI+PI/2)
								,2)
							);

	// gluPerspective(c->mFOV, c->mAspectRatio, c->mNearClippingDistance, c->mFarClippingDistance);
	// gluLookAt(
	// 0,0,0,//pos
	// 1,0,0,//pt visé
	// 0,0,1);//up

	// double r= rand()*1./RAND_MAX;
	// glColor4d(r,r,r,1);
	// string3d_draw(c->interface_txt);
	
	// glColor4d(1,1,1,1);
	// glPointSize(2.);
	// glBegin(GL_POINTS);
	// 	glVertex3d(.05,.003,0);
	// 	glVertex3d(.05,-.003,0);	glVertex3d(.05,0,0);	glVertex3d(.05,0,.003);
	// 	glVertex3d(.05,0,-.003);
	// glEnd();

	glLoadIdentity();

	gluPerspective(c->mFOV-hyperbolicLimit(.05*vitesse_avant,60), c->mAspectRatio, c->mNearClippingDistance, c->mFarClippingDistance);
	gluLookAt(
	0,0,0,//pos
	1,0,0,//pt visé
	0,0,1);//up

	

}

void camera_render(Camera* c){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera_look(c);
	glRotated(c->rho,1,0,0);
	glRotated(c->theta, 0.0, 1.0, 0.0);
	glRotated(c->phi, 0.0, 0.0, 1.0);
	glTranslated(c->x, c->y, c->z);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	c->game->render(c->game);

	glFlush();
	SDL_GL_SwapBuffers();
}

void camera_ApplyLeftFrustum(Camera* c){
	glMatrixMode(GL_PROJECTION);
	glTranslated(c->mConvergence,0,0);
	glRotated( -180/PI*atan(c->mEyeSeparation/c->mConvergence),0,0,1);
	glTranslated(-c->mConvergence,0,0);
}
void camera_ApplyRightFrustum(Camera* c){
	glMatrixMode(GL_PROJECTION);
	glTranslated(c->mConvergence,0,0);
	glRotated( +180/PI*atan(c->mEyeSeparation/c->mConvergence),0,0,1);
	glTranslated(-c->mConvergence,0,0);
}

void camera_render_stereo(Camera* c){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//left
	camera_look(c);
	camera_ApplyLeftFrustum(c);
	glColorMask(1, 0, 0, 0);// bloque Green et Blue et Transparence
	glRotated(c->rho,1,0,0);
	glRotated(c->theta, 0.0, 1.0, 0.0);
	glRotated(c->phi, 0.0, 0.0, 1.0);
	glTranslated(c->x, c->y, c->z);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	c->game->render(c->game);

	//clear buffer
	glClear(GL_DEPTH_BUFFER_BIT) ;

	//right
	camera_look(c);
	camera_ApplyRightFrustum(c);
	glColorMask(0, 1, 1, 0);//bloque Red et Transparence
	glRotated(c->rho,1,0,0);
	glRotated(c->theta, 0.0, 1.0, 0.0);
	glRotated(c->phi, 0.0, 0.0, 1.0);
	glTranslated(c->x, c->y, c->z);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	c->game->render(c->game);

	//
	glColorMask(1, 1, 1, 1);

	//update screen
	SDL_GL_SwapBuffers();
}

void camera_update(Camera* c,int dt){

	double lambda=.2;

	c->dx+=.001*dt*c->ddx - lambda*c->dx;
	c->dy+=.001*dt*c->ddy - lambda*c->dy;
	c->dz+=.001*dt*c->ddz - lambda*c->dz;

	c->x+=.001*dt*c->dx;
	c->y+=.001*dt*c->dy;
	c->z+=.001*dt*c->dz;

	c->ddx=0;
	c->ddy=0;
	c->ddz=0;

	//================================================

	c->dtheta+=.001*dt*c->ddtheta - lambda*c->dtheta;
	c->dphi+=.001*dt*c->ddphi - lambda*c->dphi;
	c->drho+=.001*dt*c->ddrho - lambda*c->drho;

	c->theta+=.001*dt*c->dtheta -lambda*c->theta;
	c->phi+=.001*dt*c->dphi ;
	c->rho+=.001*dt*c->drho -lambda*c->rho ;

	c->ddtheta=0;
	c->ddphi=0;
	c->ddrho=0;
	
}


