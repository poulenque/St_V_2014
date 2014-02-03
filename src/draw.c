#include "draw.h"
#include <stdlib.h>
#include <GL/glew.h>
#include "constants.h"

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

// void draw_guy(double time_,double noise){
// 	draw_sphere2(1,time_,noise);

// 	gluQuadricDrawStyle(quad, GLU_FILL);

// 	glPushMatrix();
// 		glTranslated(0,0,-5);
// 		gluCylinder(quad,1,0.5,5,8,1);
// 	glPopMatrix();

// 	gluQuadricDrawStyle(quad, GLU_LINE);

// 	glPushMatrix();
// 		glTranslated(0,0,-5);
// 		glRotated(time_*8,0,0,1);
// 		gluCylinder(quad,1.1,0.6,5,8,5);
// 	glPopMatrix();


// 	glPushMatrix();
// 		glTranslated(0,0,-4);
// 		draw_sphere2(1.,time_,noise);
// 	glPopMatrix();

// 	glPushMatrix();
// 		glTranslated(0,0,-3);
// 		draw_sphere2(.9,time_,noise);
// 	glPopMatrix();

// 	glPushMatrix();
// 		glTranslated(0,0,-2);
// 		draw_sphere2(.8,time_,noise);
// 	glPopMatrix();

// 	glPushMatrix();
// 		glTranslated(0,0,-1);
// 		draw_sphere2(.7,time_,noise);
// 	glPopMatrix();

// 	glBegin(GL_LINES);
// 		for (int i = 0; i < 100; ++i){
// 			glVertex3d(2*noise-((double)rand()/RAND_MAX)*4.*noise, 2*noise-((double)rand()/RAND_MAX)*noise*4.,2*noise-((double)rand()/RAND_MAX)*noise*4.+4*(i/100.)-5);
// 			glVertex3d(2*noise-((double)rand()/RAND_MAX)*4.*noise, 2*noise-((double)rand()/RAND_MAX)*noise*4.,2*noise-((double)rand()/RAND_MAX)*noise*4.+4*(1-i/100.)-5);
// 		}
// 	glEnd();


// 	// glPushMatrix();
// 	// 	glTranslated(0,0,-4);
// 	// 	glRotated(2*time_,3*time_,time_,1);
// 	// 	gluSphere(quad,1.1+noise*rand()/RAND_MAX,10,8);
// 	// glPopMatrix();

// 	// glPushMatrix();
// 	// 	glTranslated(0,0,-3);
// 	// 	glRotated(2*time_,3*time_,time_,1);
// 	// 	gluSphere(quad,1.0+noise*rand()/RAND_MAX,10,8);
// 	// glPopMatrix();

// 	// glPushMatrix();
// 	// 	glTranslated(0,0,-2);
// 	// 	glRotated(2*time_,3*time_,time_,1);
// 	// 	gluSphere(quad,.9+noise*rand()/RAND_MAX,10,8);
// 	// glPopMatrix();

// 	// glPushMatrix();
// 	// 	glTranslated(0,0,-1);
// 	// 	glRotated(2*time_,3*time_,time_,1);
// 	// 	gluSphere(quad,.8+noise*rand()/RAND_MAX,10,8);
// 	// glPopMatrix();

// }

double random(){
	return (double)rand()/RAND_MAX;
}

void draw_guy(double time_,double noise,int detail){

	if (detail==1){
		glBegin(GL_LINES);
			glVertex3d(0,0,1);
			glVertex3d(0,0,-5);
		glEnd();
		return;
	}

	gluQuadricDrawStyle(quad, GLU_FILL);

	double d= 1./detail;

	glPushMatrix();
		glTranslated(0,0,1);
		// for(int i=0;i<detail;i++){
		// 	glTranslated(0,0,-2./detail);
		// 	gluCylinder(quad,sin(PI*i/detail),sin(PI*(i+1)/detail),2./detail,8,1);
		// }

		for(int i=0;i<detail;i++){
			glTranslated(0,0,-2.*d);
			glRotated(random()*noise*180,0,0,1);
			gluCylinder(quad,1-(i+1.)*d,1-i*d,2.*d,8,1);
			gluCylinder(quad,random()*noise+(1-(i+1.)*d),random()*noise+(1-i*1.*d),(2.*d),8,1);
		}

		for(int i=0;i<detail;i++){
			glTranslated(0,0,-4.*d);
			gluCylinder(quad,1+.5*cos(2*PI*(i+1)*d),1+.5*cos(2*PI*i*d),4.*d,8,1);
			gluCylinder(quad,random()*noise+1+.5*cos(2*PI*(i+1)*d),random()*noise+1+.5*cos(2*PI*i*d),4.*d,8,1);
		}
	glPopMatrix();

	gluQuadricDrawStyle(quad, GLU_LINE);

	glPushMatrix();
		glTranslated(0,0,1);
		for(int i=0;i<detail;i++){
			glTranslated(0,0,-2.*d);
			glRotated(random()*noise*360,0,0,1);
			gluCylinder(quad,random()*noise+1.1*(1-(i+1.)*d),random()*noise+1.1*(1-i*1.*d),1.1*(2.*d),8,1);
		}
		for(int i=0;i<detail;i++){
			glTranslated(0,0,-4.*d);
			gluCylinder(quad,random()*noise+1.1*(1+.5*cos(2*PI*(i+1)*d)),random()*noise+1.1*(1+.5*cos(2*PI*i*d)),1.1*(4.*d),8,1);
		}
	glPopMatrix();
	glPushMatrix();
		glTranslated(0,0,1);
		for(int i=0;i<detail;i++){
			glTranslated(0,0,-2.*d);
			glRotated(random()*noise*360,0,0,1);
			gluCylinder(quad,random()*noise+1.1*(1-(i+1.)*d),random()*noise+1.1*(1-i*1.*d),1.1*(2.*d),8,1);
		}
		for(int i=0;i<detail;i++){
			glTranslated(0,0,-4.*d);
			gluCylinder(quad,random()*noise+1.1*(1+.5*cos(2*PI*(i+1)*d)),random()*noise+1.1*(1+.5*cos(2*PI*i*d)),1.1*(4.*d),8,1);
		}
	glPopMatrix();


}



void draw_wing(double time_,double noise,int detail){
	// glPushMatrix();
	// 	glBegin(GL_LINES);
	// 	for(int i=0;i<detail;i++){
	// 		glVertex3d(0,0,0);
	// 		// glRotated(time_,0,0,1);
	// 		glVertex3d(
	// 			(pow(1.15,i)*cos(5./4.*PI+(1.9*PI-5./4.*PI)*i/(double)detail) )+sin(pow(cos(time_*.05),2)*5.*i/detail),
	// 			(pow(1.15,i)*cos(5./4.*PI+(1.9*PI-5./4.*PI)*i/(double)detail) )+cos(pow(cos(time_*.05),2)*5.*i/detail),
	// 			(pow(1.15,i)*sin(5./4.*PI+(1.9*PI-5./4.*PI)*i/(double)detail) ) );
	// 	}
	// 	glEnd();
	// glPopMatrix();
	glPushMatrix();
		for(int i=0;i<detail;i++){
			glRotated(time_,0,0,1);
			glBegin(GL_LINES);
			glVertex3d(0,0,0);
			glVertex3d(1,1,1);
			glEnd();
		}
	glPopMatrix();

}













