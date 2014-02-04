#include "draw.h"
#include <stdlib.h>
#include <GL/glew.h>
#include "constants.h"
#include "random.h"

static GLUquadric* quad;

void draw_init(){
	quad=gluNewQuadric();
}

void draw_cube(double size,double noise){
	glBegin( GL_LINES );
		glVertex3d(-random(size,size*noise), -random(size,size*noise), -random(size,size*noise) );
		glVertex3d(-random(size,size*noise),  random(size,size*noise), -random(size,size*noise) );
		glVertex3d(-random(size,size*noise),  random(size,size*noise),  random(size,size*noise) );
		glVertex3d(-random(size,size*noise), -random(size,size*noise),  random(size,size*noise) );
		glVertex3d( random(size,size*noise), -random(size,size*noise), -random(size,size*noise) );
		glVertex3d( random(size,size*noise),  random(size,size*noise), -random(size,size*noise) );
		glVertex3d( random(size,size*noise),  random(size,size*noise),  random(size,size*noise) );
		glVertex3d( random(size,size*noise), -random(size,size*noise),  random(size,size*noise) );

		glVertex3d(-random(size,size*noise), -random(size,size*noise), -random(size,size*noise) );
		glVertex3d( random(size,size*noise), -random(size,size*noise), -random(size,size*noise) );
		glVertex3d(-random(size,size*noise),  random(size,size*noise), -random(size,size*noise) );
		glVertex3d( random(size,size*noise),  random(size,size*noise), -random(size,size*noise) );
		glVertex3d(-random(size,size*noise),  random(size,size*noise),  random(size,size*noise) );
		glVertex3d( random(size,size*noise),  random(size,size*noise),  random(size,size*noise) );
		glVertex3d(-random(size,size*noise), -random(size,size*noise),  random(size,size*noise) );
		glVertex3d( random(size,size*noise), -random(size,size*noise),  random(size,size*noise) );


		glVertex3d(-random(size,size*noise),  random(size,size*noise), -random(size,size*noise) );
		glVertex3d(-random(size,size*noise),  random(size,size*noise),  random(size,size*noise) );
		glVertex3d(-random(size,size*noise), -random(size,size*noise),  random(size,size*noise) );
		glVertex3d(-random(size,size*noise), -random(size,size*noise), -random(size,size*noise) );
		glVertex3d( random(size,size*noise),  random(size,size*noise), -random(size,size*noise) );
		glVertex3d( random(size,size*noise),  random(size,size*noise),  random(size,size*noise) );
		glVertex3d( random(size,size*noise), -random(size,size*noise),  random(size,size*noise) );
		glVertex3d( random(size,size*noise), -random(size,size*noise), -random(size,size*noise) );


	glEnd();

}

void draw_face(double size,double noise){
	glBegin( GL_QUADS );
		glVertex3d(0, -random(size,size*noise), -random(size,size*noise) );
		glVertex3d(0,  random(size,size*noise), -random(size,size*noise) );
		glVertex3d(0,  random(size,size*noise),  random(size,size*noise) );
		glVertex3d(0, -random(size,size*noise),  random(size,size*noise) );
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
			gluSphere(quad,
				random(size,size*noise),10,8);
		glPopMatrix();
		gluQuadricDrawStyle(quad, GLU_LINE);

		glPushMatrix();
		glRotated(time_,2*time_,4*time_,1);
			gluSphere(quad,
				random(size+size/5.*.15,size*noise),10,8);
		glPopMatrix();

		glPushMatrix();
		glRotated(2*time_,3*time_,time_,1);
			gluSphere(quad,
				random(size+size/5.*.25,size*noise),10,8);
		glPopMatrix();

		glPushMatrix();
		glRotated(2*time_,2*time_,2*time_,1);
			gluSphere(quad,
				random(size+size/5.*.5,size*noise),10,8);
		glPopMatrix();

		glPushMatrix();
		glRotated(4.2*time_,3*time_,2*time_,1);
			gluSphere(quad,
				random(size+size/5.*.75,size*noise),10,8);
		glPopMatrix();

		glPushMatrix();
		glRotated(4*time_,5*time_,4*time_,1);
			gluSphere(quad,
				random(size+size/5.*1.,size*noise),10,8);
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

void draw_gentil(double noise,int detail){
	if (detail==0){
		glBegin(GL_LINES);
			glVertex3d(0,0,1);
			glVertex3d(0,0,-5);
		glEnd();
		return;
	}

	gluQuadricDrawStyle(quad, GLU_FILL);

	glPushMatrix();

	glTranslated(0,0,1);
	glColor4d(0,0,0,1);

		//HEAD
		glTranslated(0,0,-1.);
		glPushMatrix();
			// glRotated(random(0,noise*40),random(0,noise*40),random(0,noise*40),1);
			// gluCylinder(quad,1-(1.)*d,1,2.*d,8,1);
			glRotated(random(0,noise*40),random(0,noise*40),random(0,noise*40),1);
			gluCylinder(quad,
				random(.5,noise),
				random(1,noise),
				1.,8,1);
		glPopMatrix();


		glTranslated(0,0,-1.);
		glPushMatrix();
			glRotated(random(0,noise*40),random(0,noise*40),random(0,noise*40),1);
			gluCylinder(quad,
				0.,
				random(.5,noise),
				1.,8,1);
			glPopMatrix();

		//BODY
		glTranslated(0,0,-2.);
		glPushMatrix();

			if(detail>=2){
				glRotated(random(0,noise*40),random(0,noise*40),random(0,noise*40),1);
				gluCylinder(quad,
					random(1-.5,noise),
					random(1+.5,noise),
					2.,8,1);

			}
			glRotated(random(0,noise*40),random(0,noise*40),random(0,noise*40),1);
			gluCylinder(quad,1-.5,1+.5,2.,8,1);
		glPopMatrix();

		glTranslated(0,0,-2.);
		glPushMatrix();

			if(detail>=2){
				glRotated(random(0,noise*40),random(0,noise*40),random(0,noise*40),1);
				gluCylinder(quad,
					random(1+.5,noise),
					random(1-.5,noise),
					2.,8,1);
	
			}
			glRotated(random(0,noise*40),random(0,noise*40),random(0,noise*40),1);
			gluCylinder(quad,1+.5,1-.5,2,8,1);
		glPopMatrix();

	glPopMatrix();




















	glTranslated(0,0,1);
	glColor4d(.9,.9,.9,1);
	glScaled(1,1,-1);
	glTranslated(0,0,12);

		//HEAD
		glTranslated(0,0,-1.);
		glPushMatrix();
			// glRotated(random(0,noise*40),random(0,noise*40),random(0,noise*40),1);
			// gluCylinder(quad,1-(1.)*d,1,2.*d,8,1);
			glRotated(random(0,noise*40),random(0,noise*40),random(0,noise*40),1);
			gluCylinder(quad,
				random(.5,noise),
				random(1,noise),
				1.,8,1);
		glPopMatrix();


		glTranslated(0,0,-1.);
		glPushMatrix();
			glRotated(random(0,noise*40),random(0,noise*40),random(0,noise*40),1);
			gluCylinder(quad,
				0.,
				random(.5,noise),
				1.,8,1);
			glPopMatrix();

		//BODY
		glTranslated(0,0,-2.);
		glPushMatrix();

			if(detail>=2){
				glRotated(random(0,noise*40),random(0,noise*40),random(0,noise*40),1);
				gluCylinder(quad,
					random(1-.5,noise),
					random(1+.5,noise),
					2.,8,1);

			}
			glRotated(random(0,noise*40),random(0,noise*40),random(0,noise*40),1);
			gluCylinder(quad,1-.5,1+.5,2.,8,1);
		glPopMatrix();

		glTranslated(0,0,-2.);
		glPushMatrix();

			if(detail>=2){
				glRotated(random(0,noise*40),random(0,noise*40),random(0,noise*40),1);
				gluCylinder(quad,
					random(1+.5,noise),
					random(1-.5,noise),
					2.,8,1);
	
			}
			glRotated(random(0,noise*40),random(0,noise*40),random(0,noise*40),1);
			gluCylinder(quad,1+.5,1-.5,2,8,1);
		glPopMatrix();

	glPopMatrix();







}

void draw_mechant(double noise,int detail){
	//TODO
}

void draw_half_bow(double noise,double force){
	force+=.5;
	glPushMatrix();
		glColor4d(1,0,0,1);
		gluCylinder(quad,random(1,noise),random(1,noise),3,8,1);
		glTranslated(0,0,3);
		glRotated(force*2,force*2,0.,1.);
		gluCylinder(quad,random(1,noise),random(1.5,noise),1,8,1);
		glTranslated(0,0,1);
		glRotated(force*2,force*2,0.,1.);
		gluCylinder(quad,random(1.5,noise),random(1.5,noise),1,8,1);
		glTranslated(0,0,1);
		gluCylinder(quad,random(1.5,noise),random(.8,noise),0,8,1);
		// glTranslated(0,0,0);
		// glColor4d(1,.6,.6,1);
		glRotated(force*10,force*10,0.,1.);
		gluCylinder(quad,random(.8,noise),random(.7,noise),5,8,1);

		glTranslated(0.,0.,5);

		double length=3.;
		glRotated(force*5,force*5,0.,1.);
		gluCylinder(quad,random(.7,noise),random(.7,noise),length,8,1);
		glTranslated(0.,0.,length);


		glRotated(force*10,force*10,0.,1.);
		gluCylinder(quad,random(.7,noise),random(.7,noise),length,8,1);
		glTranslated(0.,0.,length);


		glRotated(force*20,force*20,0.,1.);
		gluCylinder(quad,random(.7,noise),random(.6,noise),length,8,1);
		glTranslated(0.,0.,length);

		glRotated(force*10,force*10,0.,1.);
		gluCylinder(quad,random(.6,noise),random(.5,noise),length,8,1);
		glTranslated(0.,0.,length);

		force = force +1;
		glRotated(360-10/force,360-10/force,0.,1.);
		gluCylinder(quad,random(.5,noise),random(.4,noise),length,8,1);
		glTranslated(0.,0.,length);

		glRotated(360-20/force,360-20/force,0.,1.);
		gluCylinder(quad,random(.4,noise),random(.3,noise),length,8,1);
		glTranslated(0.,0.,length);


		glRotated(360-5/force,360-5/force,0.,1.);
		gluCylinder(quad,random(.3,noise),random(.2,noise),length,8,1);
		glTranslated(0.,0.,length);


		//le fil
		// glRotated(360-5/force,360-5/force,0.,1.);
		gluCylinder(quad,random(.2,noise),random(.05,noise),0,8,1);
		// glTranslated(0.,0.,0);



		glRotated(05/force,05/force,0.,1.);
		glRotated(20/force,20/force,0.,1.);
		glRotated(10/force,10/force,0.,1.);
		force = force -1;
		glRotated(360-force*10,360-force*10,0.,1.);
		glRotated(360-force*20,360-force*20,0.,1.);
		glRotated(360-force*10,360-force*10,0.,1.);
		glRotated(360-force*05,360-force*05,0.,1.);
		glRotated(360-force*10,360-force*10,0.,1.);
		glRotated(360-force*02,360-force*02,0.,1.);
		glRotated(360-force*02,360-force*02,0.,1.);


		force-=.5; //force entre 0 et 1		
		glRotated(180*(1-force*.3),180*(1-force*.3),0.,1.);
		gluCylinder(quad,random(.05,noise*.1),random(.05,noise*.1),31,8,1);

		// t++;
		// glTranslated(0.,0.,5.);
		// glRotated(t,t,0.,1.);
		// gluCylinder(quad,.7,.7,5,8,1);

		// glTranslated(0.,0.,5.);
		// glRotated(-20,-20,0.,1.);
		// gluCylinder(quad,.7,.7,5,8,1);

		// glTranslated(0.,0.,5.);
		// glRotated(-20,-20,0.,1.);
		// gluCylinder(quad,.7,.7,5,8,1);

	glPopMatrix();
}

void draw_bow(double noise,double force){

	gluQuadricDrawStyle(quad, GLU_FILL);
	glPushMatrix();
	glScaled(.25,.25,.25);
		draw_half_bow(noise,force);
		glPushMatrix();
		glScaled(1,1,-1);
		draw_half_bow(noise,force);
		glPopMatrix();
	glPopMatrix();

	gluQuadricDrawStyle(quad, GLU_LINE);
	glPushMatrix();
	glScaled(.25,.25,.25);
		draw_half_bow(noise,force);
		glPushMatrix();
		glScaled(1,1,-1);
		draw_half_bow(noise,force);
		glPopMatrix();
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













