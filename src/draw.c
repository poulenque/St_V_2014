#include "draw.h"
#include <stdlib.h>
#include <GL/glew.h>


static GLUquadric* quad;

void draw_init(){
	quad=gluNewQuadric();
}

void draw_cube(double size,double noise){
	glBegin( GL_LINES );
		glVertex3d(-size+size*noise-size*noise*rand()/(double)RAND_MAX, -size+size*noise-size*noise*rand()/(double)RAND_MAX, -size+size*noise-size*noise*rand()/(double)RAND_MAX );
		glVertex3d(-size+size*noise-size*noise*rand()/(double)RAND_MAX,  size+size*noise-size*noise*rand()/(double)RAND_MAX, -size+size*noise-size*noise*rand()/(double)RAND_MAX );
		glVertex3d(-size+size*noise-size*noise*rand()/(double)RAND_MAX,  size+size*noise-size*noise*rand()/(double)RAND_MAX,  size+size*noise-size*noise*rand()/(double)RAND_MAX );
		glVertex3d(-size+size*noise-size*noise*rand()/(double)RAND_MAX, -size+size*noise-size*noise*rand()/(double)RAND_MAX,  size+size*noise-size*noise*rand()/(double)RAND_MAX );
		glVertex3d( size+size*noise-size*noise*rand()/(double)RAND_MAX, -size+size*noise-size*noise*rand()/(double)RAND_MAX, -size+size*noise-size*noise*rand()/(double)RAND_MAX );
		glVertex3d( size+size*noise-size*noise*rand()/(double)RAND_MAX,  size+size*noise-size*noise*rand()/(double)RAND_MAX, -size+size*noise-size*noise*rand()/(double)RAND_MAX );
		glVertex3d( size+size*noise-size*noise*rand()/(double)RAND_MAX,  size+size*noise-size*noise*rand()/(double)RAND_MAX,  size+size*noise-size*noise*rand()/(double)RAND_MAX );
		glVertex3d( size+size*noise-size*noise*rand()/(double)RAND_MAX, -size+size*noise-size*noise*rand()/(double)RAND_MAX,  size+size*noise-size*noise*rand()/(double)RAND_MAX );

		glVertex3d(-size+size*noise-size*noise*rand()/(double)RAND_MAX, -size+size*noise-size*noise*rand()/(double)RAND_MAX, -size+size*noise-size*noise*rand()/(double)RAND_MAX );
		glVertex3d( size+size*noise-size*noise*rand()/(double)RAND_MAX, -size+size*noise-size*noise*rand()/(double)RAND_MAX, -size+size*noise-size*noise*rand()/(double)RAND_MAX );
		glVertex3d(-size+size*noise-size*noise*rand()/(double)RAND_MAX,  size+size*noise-size*noise*rand()/(double)RAND_MAX, -size+size*noise-size*noise*rand()/(double)RAND_MAX );
		glVertex3d( size+size*noise-size*noise*rand()/(double)RAND_MAX,  size+size*noise-size*noise*rand()/(double)RAND_MAX, -size+size*noise-size*noise*rand()/(double)RAND_MAX );
		glVertex3d(-size+size*noise-size*noise*rand()/(double)RAND_MAX,  size+size*noise-size*noise*rand()/(double)RAND_MAX,  size+size*noise-size*noise*rand()/(double)RAND_MAX );
		glVertex3d( size+size*noise-size*noise*rand()/(double)RAND_MAX,  size+size*noise-size*noise*rand()/(double)RAND_MAX,  size+size*noise-size*noise*rand()/(double)RAND_MAX );
		glVertex3d(-size+size*noise-size*noise*rand()/(double)RAND_MAX, -size+size*noise-size*noise*rand()/(double)RAND_MAX,  size+size*noise-size*noise*rand()/(double)RAND_MAX );
		glVertex3d( size+size*noise-size*noise*rand()/(double)RAND_MAX, -size+size*noise-size*noise*rand()/(double)RAND_MAX,  size+size*noise-size*noise*rand()/(double)RAND_MAX );


		glVertex3d(-size+size*noise-size*noise*rand()/(double)RAND_MAX,  size+size*noise-size*noise*rand()/(double)RAND_MAX, -size+size*noise-size*noise*rand()/(double)RAND_MAX );
		glVertex3d(-size+size*noise-size*noise*rand()/(double)RAND_MAX,  size+size*noise-size*noise*rand()/(double)RAND_MAX,  size+size*noise-size*noise*rand()/(double)RAND_MAX );
		glVertex3d(-size+size*noise-size*noise*rand()/(double)RAND_MAX, -size+size*noise-size*noise*rand()/(double)RAND_MAX,  size+size*noise-size*noise*rand()/(double)RAND_MAX );
		glVertex3d(-size+size*noise-size*noise*rand()/(double)RAND_MAX, -size+size*noise-size*noise*rand()/(double)RAND_MAX, -size+size*noise-size*noise*rand()/(double)RAND_MAX );
		glVertex3d( size+size*noise-size*noise*rand()/(double)RAND_MAX,  size+size*noise-size*noise*rand()/(double)RAND_MAX, -size+size*noise-size*noise*rand()/(double)RAND_MAX );
		glVertex3d( size+size*noise-size*noise*rand()/(double)RAND_MAX,  size+size*noise-size*noise*rand()/(double)RAND_MAX,  size+size*noise-size*noise*rand()/(double)RAND_MAX );
		glVertex3d( size+size*noise-size*noise*rand()/(double)RAND_MAX, -size+size*noise-size*noise*rand()/(double)RAND_MAX,  size+size*noise-size*noise*rand()/(double)RAND_MAX );
		glVertex3d( size+size*noise-size*noise*rand()/(double)RAND_MAX, -size+size*noise-size*noise*rand()/(double)RAND_MAX, -size+size*noise-size*noise*rand()/(double)RAND_MAX );


	glEnd();

}

void draw_face(double size,double noise){
	glBegin( GL_QUADS );
		glVertex3d(0, -size+size*noise-size*noise*rand()/(double)RAND_MAX, -size+size*noise-size*noise*rand()/(double)RAND_MAX );
		glVertex3d(0,  size+size*noise-size*noise*rand()/(double)RAND_MAX, -size+size*noise-size*noise*rand()/(double)RAND_MAX );
		glVertex3d(0,  size+size*noise-size*noise*rand()/(double)RAND_MAX,  size+size*noise-size*noise*rand()/(double)RAND_MAX );
		glVertex3d(0, -size+size*noise-size*noise*rand()/(double)RAND_MAX,  size+size*noise-size*noise*rand()/(double)RAND_MAX );
	glEnd();
}

void draw_sphere(double size,double time_,int detail){
		GLUquadric* quad=gluNewQuadric();
		glPushMatrix();
		gluQuadricDrawStyle(quad, GLU_FILL);
		glRotated(8*time_,8*time_,8*time_,1);
			gluSphere(quad,size,10,8);
		glPopMatrix();

		gluQuadricDrawStyle(quad, GLU_LINE);
		glLineWidth(3.0);

		for(int i=1;i<detail;i++){
			glPushMatrix();
			// glRotated(
			// 	(sin(1*i)*.5)*7*(1+i*.2)*time_,
			// 	(cos(2*i)*.5)*7*(1+i*.2)*time_,
			// 	(sin(2*i)*.5)*7*(1+i*.2)*time_,1
			// );
				// gluSphere(quad,size+2*exp(-i*.5),10,8);
			glRotated(
				(sin(1*i)*.5)*6*(1+i*.2)*time_,
				(cos(2*i)*.5)*6*(1+i*.2)*time_,
				(sin(2*i)*.5)*6*(1+i*.2)*time_,
				1
			);
				gluSphere(quad,size+1.2*i*(1./detail),10,8);
			glPopMatrix();
		}
		gluDeleteQuadric(quad);
}

void draw_sphere2(double size,double time_,double noise){
		glLineWidth(3.0);
		glPushMatrix();
		gluQuadricDrawStyle(quad, GLU_FILL);
		glRotated(8*time_,8*time_,8*time_,1);
			gluSphere(quad,size+size*noise*rand()/RAND_MAX,10,8);
		glPopMatrix();
		gluQuadricDrawStyle(quad, GLU_LINE);

		glPushMatrix();
		glRotated(time_,2*time_,4*time_,1);
			gluSphere(quad,size+size/5.*.15+size*noise*rand()/RAND_MAX,10,8);
		glPopMatrix();

		glPushMatrix();
		glRotated(2*time_,3*time_,time_,1);
			gluSphere(quad,size+size/5.*.25+size*noise*rand()/RAND_MAX,10,8);
		glPopMatrix();

		glPushMatrix();
		glRotated(2*time_,2*time_,2*time_,1);
			gluSphere(quad,size+size/5.*.5+size*noise*rand()/RAND_MAX,10,8);
		glPopMatrix();

		glPushMatrix();
		glRotated(4.2*time_,3*time_,2*time_,1);
			gluSphere(quad,size+size/5.*.75+size*noise*rand()/RAND_MAX,10,8);
		glPopMatrix();

		glPushMatrix();
		glRotated(4*time_,5*time_,4*time_,1);
			gluSphere(quad,size+size/5.*1.+size*noise*rand()/RAND_MAX,10,8);
		glPopMatrix();

		// gluDeleteQuadric(quad);
}

void draw_guy(double time_,double noise){
	draw_sphere2(1,time_,noise);

	gluQuadricDrawStyle(quad, GLU_FILL);

	glPushMatrix();
		glTranslated(0,0,-5);
		gluCylinder(quad,1,0.5,5,8,1);
	glPopMatrix();

	gluQuadricDrawStyle(quad, GLU_LINE);

	glPushMatrix();
		glTranslated(0,0,-5);
		glRotated(time_*8,0,0,1);
		gluCylinder(quad,1.1,0.6,5,8,5);
	glPopMatrix();


	glPushMatrix();
		glTranslated(0,0,-4);
		draw_sphere2(1.,time_,noise);
	glPopMatrix();

	glPushMatrix();
		glTranslated(0,0,-3);
		draw_sphere2(.9,time_,noise);
	glPopMatrix();

	glPushMatrix();
		glTranslated(0,0,-2);
		draw_sphere2(.8,time_,noise);
	glPopMatrix();

	glPushMatrix();
		glTranslated(0,0,-1);
		draw_sphere2(.7,time_,noise);
	glPopMatrix();

	glBegin(GL_LINES);
		for (int i = 0; i < 100; ++i){
			glVertex3d(2*noise-((double)rand()/RAND_MAX)*4.*noise, 2*noise-((double)rand()/RAND_MAX)*noise*4.,2*noise-((double)rand()/RAND_MAX)*noise*4.+4*(i/100.)-5);
			glVertex3d(2*noise-((double)rand()/RAND_MAX)*4.*noise, 2*noise-((double)rand()/RAND_MAX)*noise*4.,2*noise-((double)rand()/RAND_MAX)*noise*4.+4*(1-i/100.)-5);
		}
	glEnd();


	// glPushMatrix();
	// 	glTranslated(0,0,-4);
	// 	glRotated(2*time_,3*time_,time_,1);
	// 	gluSphere(quad,1.1+noise*rand()/RAND_MAX,10,8);
	// glPopMatrix();

	// glPushMatrix();
	// 	glTranslated(0,0,-3);
	// 	glRotated(2*time_,3*time_,time_,1);
	// 	gluSphere(quad,1.0+noise*rand()/RAND_MAX,10,8);
	// glPopMatrix();

	// glPushMatrix();
	// 	glTranslated(0,0,-2);
	// 	glRotated(2*time_,3*time_,time_,1);
	// 	gluSphere(quad,.9+noise*rand()/RAND_MAX,10,8);
	// glPopMatrix();

	// glPushMatrix();
	// 	glTranslated(0,0,-1);
	// 	glRotated(2*time_,3*time_,time_,1);
	// 	gluSphere(quad,.8+noise*rand()/RAND_MAX,10,8);
	// glPopMatrix();

}
