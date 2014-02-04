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
	c->drho+=drho + dphi/4.;
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

	// glGenFramebuffers (1, &c->frame_buffer_id);
	// c->depth_tex_id=lr_texture_depthmap (800,600);

	c->shader_id_dummy=shader_createProgram("dummy");
	c->shader_id_dof=shader_createProgram("dof");
	glGenFramebuffers(1,& (c->frame_buffer_id));

	glGenTextures (1, &(c->depth_tex_id));
	glBindTexture (GL_TEXTURE_2D, c->depth_tex_id);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 800, 600, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);


	glGenTextures (1, &(c->color_tex_id));
	glBindTexture (GL_TEXTURE_2D, c->color_tex_id);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	glBindTexture (GL_TEXTURE_2D, 0);

	c->shader_dof_color_id = glGetUniformLocation(c->shader_id_dof,"color");
	// glUniform4f (color_id, 1, 0, 0, 1);
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

	// // glFramebufferTexture2D (GL_FRAMEBUFFER, GL_DEPTH_COMPONENT, GL_TEXTURE_2D, game->depth_tex_id, 0);

	// glUseProgram(game->shader_id_dummy);
	// glFramebufferTexture2D(game->frame_buffer_id,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,game->color_tex_id,0);
	// // glFramebufferTexture2D(game->frame_buffer_id,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,game->depth_tex_id,0);

	// glBindFramebuffer(GL_FRAMEBUFFER,game->frame_buffer_id);

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
	// // SDL_Surface * image = IMG_Load("screenshot/01.png");
	// // glTexImage2D (GL_TEXTURE_2D, 0, 3,
	// // 	image->w, image->h, 0,
	// // 	GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

	// glBindFramebuffer(GL_FRAMEBUFFER,0);
	// glUseProgram(game->shader_id_dof);
	// glActiveTexture (GL_TEXTURE0);
	// glBindTexture (GL_TEXTURE_2D, game->color_tex_id);
	// // glBindTexture (GL_TEXTURE_2D, game->depth_tex_id);
	// glUniform1i(game->shader_dof_color_id,GL_TEXTURE0);


	// glBegin( GL_QUADS );
	// 	glVertex2d(-1,-1);
	// 	glVertex2d(-1, 1);
	// 	glVertex2d( 1, 1);
	// 	glVertex2d( 1,-1);
	// glEnd();

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

	for(int i=0;i<dt;i++){
		double dt=1;

		double lambda=.2;

		// c->dx+=.001*dt*c->ddx;
		// c->dy+=.001*dt*c->ddy;
		// c->dz+=.001*dt*c->ddz;
		c->dx+=.001*dt*c->ddx;
		c->dy+=.001*dt*c->ddy;
		c->dz+=.001*dt*c->ddz;

		// c->dx+= -.05*.05*dt*dt*lambda*c->dx;
		// c->dy+= -.05*.05*dt*dt*lambda*c->dy;
		// c->dz+= -.05*.05*dt*dt*lambda*c->dz;
		c->dx+= -.011*c->dx;
		c->dy+= -.011*c->dy;
		c->dz+= -.011*c->dz;
		// c->dx/= .07*dt;
		// c->dy/= .07*dt;
		// c->dz/= .07*dt;

		c->x+=.001*dt*c->dx;
		c->y+=.001*dt*c->dy;
		c->z+=.001*dt*c->dz;


		//================================================

		c->dtheta+=.001*dt*c->ddtheta;
		c->dphi  +=.001*dt*c->ddphi;
		c->drho  +=.001*dt*c->ddrho;

		// c->dtheta+= - .05*.05*dt*dt*lambda*c->dtheta;
		// c->dphi+=   - .05*.05*dt*dt*lambda*c->dphi;
		// c->drho+=   - .05*.05*dt*dt*lambda*c->drho;
		c->dtheta+= - .013*c->dtheta;
		c->dphi+=   - .013*c->dphi;
		c->drho+=   - .013*c->drho;

		// c->dtheta/= .07*dt;
		// c->dphi  /= .07*dt;
		// c->drho  /= .07*dt;

		c->theta+=.001*dt*c->dtheta -.01*c->theta;
		c->phi  +=.001*dt*c->dphi ;
		c->rho  +=.001*dt*c->drho -.03*c->rho ;


		// c->dtheta=0;
		// c->dphi=0;
		// c->drho=0;
	}	
c->ddx=0;
c->ddy=0;
c->ddz=0;

c->ddtheta=0;
c->ddphi=0;
c->ddrho=0;

}


