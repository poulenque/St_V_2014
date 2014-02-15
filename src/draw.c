#include "draw.h"

#include <stdlib.h>
#include <GL/glew.h>
#include <math.h>
#include <SDL/SDL.h>
#include "constants.h"
#include "random.h"

double t=0;

static GLUquadric* quad;

void draw_init(){
	quad=gluNewQuadric();
}

//===============================================
//                                                 
// _|_|_|      _|_|      _|_|_|  _|_|_|    _|_|_|  
// _|    _|  _|    _|  _|          _|    _|        
// _|_|_|    _|_|_|_|    _|_|      _|    _|        
// _|    _|  _|    _|        _|    _|    _|        
// _|_|_|    _|    _|  _|_|_|    _|_|_|    _|_|_|  
//                                                 
//===============================================
//===============================================
//===============================================

void draw_cheni(double size,double noise, int count){
	while(count--){
		glBegin( GL_LINES );
			glVertex3d(random(0,size*noise), random(0,size*noise), random(0,size*noise) );
			glVertex3d(random(0,size*noise), random(0,size*noise), random(0,size*noise) );
		glEnd();
	}
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
void draw_cube_simple(double size){
	glBegin( GL_LINES );
		glVertex3d(-size, -size, -size );
		glVertex3d(-size,  size, -size );
		glVertex3d(-size,  size,  size );
		glVertex3d(-size, -size,  size );
		glVertex3d( size, -size, -size );
		glVertex3d( size,  size, -size );
		glVertex3d( size,  size,  size );
		glVertex3d( size, -size,  size );

		glVertex3d(-size, -size, -size );
		glVertex3d( size, -size, -size );
		glVertex3d(-size,  size, -size );
		glVertex3d( size,  size, -size );
		glVertex3d(-size,  size,  size );
		glVertex3d( size,  size,  size );
		glVertex3d(-size, -size,  size );
		glVertex3d( size, -size,  size );


		glVertex3d(-size,  size, -size );
		glVertex3d(-size,  size,  size );
		glVertex3d(-size, -size,  size );
		glVertex3d(-size, -size, -size );
		glVertex3d( size,  size, -size );
		glVertex3d( size,  size,  size );
		glVertex3d( size, -size,  size );
		glVertex3d( size, -size, -size );
	glEnd();
}
void simple_cube(){
	glBegin(GL_POLYGON);
	glVertex3f(  0.5, -0.5, 0.5 );
	glVertex3f(  0.5,  0.5, 0.5 );
	glVertex3f( -0.5,  0.5, 0.5 );
	glVertex3f( -0.5, -0.5, 0.5 );
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f( 0.5, -0.5, -0.5 );
	glVertex3f( 0.5,  0.5, -0.5 );
	glVertex3f( 0.5,  0.5,  0.5 );
	glVertex3f( 0.5, -0.5,  0.5 );
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f( -0.5, -0.5,  0.5 );
	glVertex3f( -0.5,  0.5,  0.5 );
	glVertex3f( -0.5,  0.5, -0.5 );
	glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(  0.5,  0.5,  0.5 );
	glVertex3f(  0.5,  0.5, -0.5 );
	glVertex3f( -0.5,  0.5, -0.5 );
	glVertex3f( -0.5,  0.5,  0.5 );
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(  0.5, -0.5, -0.5 );
	glVertex3f(  0.5, -0.5,  0.5 );
	glVertex3f( -0.5, -0.5,  0.5 );
	glVertex3f( -0.5, -0.5, -0.5 );
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
void draw_square(double size,double noise){
	double a=random(size,size*noise);
	double b=random(size,size*noise);
	glBegin( GL_LINE_STRIP );
		glVertex3d(0, -a, -b );
		glVertex3d(0,  random(size,size*noise), -random(size,size*noise) );
		glVertex3d(0,  random(size,size*noise),  random(size,size*noise) );
		glVertex3d(0, -random(size,size*noise),  random(size,size*noise) );
		glVertex3d(0, -a, -b );
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

//=========================================================================
//                                                                           
//   _|_|_|    _|_|    _|      _|  _|_|_|    _|        _|_|_|_|  _|      _|  
// _|        _|    _|  _|_|  _|_|  _|    _|  _|        _|          _|  _|    
// _|        _|    _|  _|  _|  _|  _|_|_|    _|        _|_|_|        _|      
// _|        _|    _|  _|      _|  _|        _|        _|          _|  _|    
//   _|_|_|    _|_|    _|      _|  _|        _|_|_|_|  _|_|_|_|  _|      _|  
//                                                                           
//=========================================================================
//=========================================================================
//=========================================================================


//==========================================
//                                           
//   _|_|_|  _|    _|  _|      _|    _|_|_|  
// _|        _|    _|    _|  _|    _|        
// _|  _|_|  _|    _|      _|        _|_|    
// _|    _|  _|    _|      _|            _|  
//   _|_|_|    _|_|        _|      _|_|_|    
//                                           
//==========================================
//==========================================
//==========================================

void draw_gentil(double noise,int detail){
	if (detail==0){

		// glColor4d(0,0,0,1);
		//REAL OBJECT
		glLineWidth(3.0);
		glBegin(GL_LINES);
			glVertex3d(0,0,1);
			glVertex3d(0,0,0);
		glEnd();
		glLineWidth(2.0);
		glBegin(GL_LINES);
			glVertex3d(0,0,0);
			glVertex3d(0,0,-1);
		glEnd();

		glLineWidth(7.0);
		glBegin(GL_LINES);
			glVertex3d(0,0,-1);
			glVertex3d(0,0,-1.4);
		glEnd();
		glLineWidth(4);
		glBegin(GL_LINES);
			glVertex3d(0,0,-1.4);
			glVertex3d(0,0,-2.2);
		glEnd();
		glLineWidth(2.0);
		glBegin(GL_LINES);
			glVertex3d(0,0,-2.2);
			glVertex3d(0,0,-3);
		glEnd();
		glLineWidth(4);
		glBegin(GL_LINES);
			glVertex3d(0,0,-3);
			glVertex3d(0,0,-4);
		glEnd();
		glLineWidth(7);
		glBegin(GL_LINES);
			glVertex3d(0,0,-4);
			glVertex3d(0,0,-5);
		glEnd();
		// //REFLEXION
		// glColor4d(.9,.9,.9,1);
		// glBegin(GL_LINES);
		// 	glVertex3d(0,0,-5);
		// 	glVertex3d(0,0,-11);
		// glEnd();
		return;
	}

	int cylinder_subivision=8;
	if(detail==1)
		cylinder_subivision=4;

	gluQuadricDrawStyle(quad, GLU_FILL);

	//REAL OBJECT
	glPushMatrix();

		glTranslated(0,0,1);
		// glColor4d(0,0,0,1);

		//HEAD
		glTranslated(0,0,-1.);
		glPushMatrix();
			glRotated(random(0,noise*40),random(0,noise*40),random(0,noise*40),1);
			gluCylinder(quad,random(.5,noise), random(1,noise), 1.,cylinder_subivision,1);
		glPopMatrix();


		glTranslated(0,0,-1.);
		glPushMatrix();
			glRotated(random(0,noise*40),random(0,noise*40),random(0,noise*40),1);
			gluCylinder(quad,0.,random(.5,noise),1.,cylinder_subivision,1);
		glPopMatrix();

		//BODY
		glTranslated(0,0,-2.);
		glPushMatrix();

			if(detail>=2){
				glRotated(random(0,noise*40),random(0,noise*40),random(0,noise*40),1);
				gluCylinder(quad,random(1-.5,noise),random(1+.5,noise),2.,cylinder_subivision,1);
			}
			glRotated(random(0,noise*40),random(0,noise*40),random(0,noise*40),1);
			gluCylinder(quad,1-.5,1+.5,2.,cylinder_subivision,1);
		glPopMatrix();

		glTranslated(0,0,-2.);
		glPushMatrix();

			if(detail>=2){
				glRotated(random(0,noise*40),random(0,noise*40),random(0,noise*40),1);
				gluCylinder(quad,random(1+.5,noise),random(1-.5,noise),2.,cylinder_subivision,1);
			}
			glRotated(random(0,noise*40),random(0,noise*40),random(0,noise*40),1);
			gluCylinder(quad,1+.5,1-.5,2,cylinder_subivision,1);
		glPopMatrix();

	glPopMatrix();

}

void draw_mechant(double noise,int detail){
	detail ++;noise++;
	//TODO
}



void draw_wing(double noise,int detail){
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
			glRotated(SDL_GetTicks()*0.05,0,0,1);
			glBegin(GL_LINES);
			glVertex3d(0,0,0);
			glVertex3d(1,1,1);
			glEnd();
		}
	glPopMatrix();

}



//==============================
//                               
// _|    _|  _|    _|  _|_|_|    
// _|    _|  _|    _|  _|    _|  
// _|_|_|_|  _|    _|  _|    _|  
// _|    _|  _|    _|  _|    _|  
// _|    _|    _|_|    _|_|_|    
//                               
//==============================
//==============================
//==============================

//=========================================
//                                           
// _|    _|    _|_|    _|      _|  _|_|_|    
// _|    _|  _|    _|  _|_|    _|  _|    _|  
// _|_|_|_|  _|_|_|_|  _|  _|  _|  _|    _|  
// _|    _|  _|    _|  _|    _|_|  _|    _|  
// _|    _|  _|    _|  _|      _|  _|_|_|    
//                                           
//=========================================
//=========================================
//=========================================

void draw_hand(double force,double distance, int side_view){
	t++;
	glPushMatrix();
	glTranslated(0,-.2,0);
	glTranslated(0,force*.5,0);

		glColor4d(.8,.6,.4,1);
		glPushMatrix();
				glTranslated(0,.3,.8);
				glRotated(24,1,0,0);
				for(int i=0;i<4;i++){
					glRotated(-12,1,0,0);

					glRotated(-5+6*cos(2*PI*cos(t*0.008))+6*sin(2*PI*cos(t*0.007)),0,0,1);
					// glRotated(1,0,0,1);
					glTranslated(0,0,-.34);
					
					if(i==1)
						glTranslated(-.1,0,0);

					if(i==2)
						glTranslated(-.05,0,0);
					glBegin(GL_QUADS);
					// glBegin(GL_LINE_STRIP);

						//index haut
						glVertex3d(-.5, .0, .19);
						glVertex3d(-.5, .0,-.19);
						glVertex3d(-.5, .3,-.16);
						glVertex3d(-.5, .3, .16);

						//index partie devant pour boucher les trous
						glVertex3d(-.5, .0, .19);
						glVertex3d(-.5, .0,-.19);
						glVertex3d( .0, -.2, .19);
						glVertex3d( .0, -.2,-.19);

						//index avant
						glVertex3d(-.5, .3,-.16);
						glVertex3d(-.5, .3, .16);
						glVertex3d(.2, .5, .16);
						glVertex3d(.2, .5,-.16);

						//index droite
						glVertex3d(-.5, .0, .19);
						glVertex3d(-.5, .3, .16);
						glVertex3d( .2, .5, .16);
						glVertex3d( .2, .0, .19);

						//index gauche
						glVertex3d(-.5, .0,-.19);
						glVertex3d(-.5, .3,-.16);
						glVertex3d( .2, .5,-.16);
						glVertex3d( .2, .0,-.19);

					glEnd();
					if(i==1)
						glTranslated(.1,0,0);

					if(i==2)
						glTranslated(.05,0,0);
				}
		glPopMatrix();

		glPushMatrix();
			glTranslated(.2,-.2,.5);
			glRotated(45,1,0,0);
			glRotated(-25,0,0,1);
			glScaled(.4,.7,.4);
			simple_cube();
		glPopMatrix();


		if(side_view){
			glPushMatrix();
				glTranslated(.2,-0,.5);
				glRotated(45,1,0,0);
				glRotated(-30,0,0,1);
				glTranslated(.4,-.4,-.2);
				glScaled(.4,1.3,.5);
				simple_cube();
			glPopMatrix();
		}


		glBegin(GL_QUADS);
		// glBegin(GL_LINE_STRIP);

			//doigts dessus
			glVertex3d(-.5, .4, .6);
			glVertex3d(-.5, .2,-.7);
			glVertex3d(-.0, .6,-.8);
			glVertex3d(-.0, .6, .7);

			//doigts gauche
			glVertex3d(-.5, .2,-.7);
			glVertex3d(-.0, .6,-.8);
			glVertex3d(+.5, .4,-.8);
			glVertex3d(-.0, .6,-.8);

			//main gauche
			glVertex3d(-.5, .2,-.7);
			glVertex3d(-.5,-.6,-.5);
			glVertex3d(-.0,-.4,-.7);
			glVertex3d(-.0, .3,-.8);


			//main dessus
			glVertex3d(-.5, .4, .6);
			glVertex3d(-.5, .2,-.7);
			glVertex3d(-.5,-.6,-.5);
			glVertex3d(-.5,-.6, .4);

			//main droite
			glVertex3d(-.5, .4, .6);
			glVertex3d(-.5,-.6, .4);
			glVertex3d(-.0,-.6, .7);
		// glColor4d(0,1,0,1);
			glVertex3d(.2, .4, 1.);
		// glColor4d(.8,.6,.4,1);

			//doigts dessous
			glVertex3d(+.3,  .1,-.4);
			glVertex3d(+.3,  .1, .5);
			glVertex3d(+.0, -.2, .5);
			glVertex3d(+.0, -.2,-.4);

			//poignee centre
			glVertex3d(-.5,-.6,-.5);
			glVertex3d(-.5,-.6, .4);
			glVertex3d(-.5,-1., .2);
			glVertex3d(-.5,-.8,-.5);

			//poignee droite
			glVertex3d(-.5,-.6, .4);
			glVertex3d(-.5,-1., .2);
			glVertex3d(-.4,-1., .4);
			glVertex3d(-.0,-.6, .7);


			//poignee gauche
			glVertex3d(-.5,-.6,-.5);
			glVertex3d(-.0,-.4,-.7);
			glVertex3d(-.0,-.6,-.7);
			glVertex3d(-.5,-.8,-.5);


			double nb=3;

			glVertex3d(-.4,-1., .4);
			glVertex3d(-.0,-.6, .7);
			glVertex3d(.2,-1., .0-.1);
			glVertex3d(.5-distance,-1.-nb, .4-nb);

			glVertex3d(-.5,-1., .2);
			glVertex3d(-.4,-1., .4);
			glVertex3d(.5-distance,-1.-nb, .4-nb);
			glVertex3d(-.5-distance,-1.-nb, .2-nb);

			glVertex3d(-.0,-.6,-.7);
			glVertex3d(-.5,-.8,-.5);
			glVertex3d(-.5-distance,-nb,-nb+.5);
			glVertex3d(-.0-distance,-nb+1,-nb+.7);

			glVertex3d(-.5,-1., .2);
			glVertex3d(-.5,-.8,-.5);
			glVertex3d(-.5-distance,-nb,-nb+.5);
			glVertex3d(-.5-distance,-nb-1, -nb+.2);


			double nb2=100;


			// glVertex3d(-.4,-1., .4);
			// glVertex3d(-.0,-.6, .7);
			// glVertex3d(.2,-1., .0-.1);
			// glVertex3d(.5,-1.-nb, .4-nb);

			glVertex3d( .5-distance,-1.-nb, .4-nb);
			glVertex3d(-.5-distance,-1.-nb, .2-nb);
			glVertex3d(-.5-distance,-1.-nb-nb2, .2-nb-nb2);
			glVertex3d( .5-distance,-1.-nb-nb2, .4-nb-nb2);

			glVertex3d(-.5-distance,-nb,-nb+.5);
			glVertex3d(-.0-distance,-nb+1,-nb+.7);
			glVertex3d(-.0-distance,-nb-nb2+1,-nb-nb2+.7);
			glVertex3d(-.5-distance,-nb-nb2,-nb-nb2+.5);

			glVertex3d(-.5-distance,-nb,-nb+.5);
			glVertex3d(-.5-distance,-nb-1, -nb+.2);
			glVertex3d(-.5-distance,-nb-nb2-1, -nb-nb2+.2);
			glVertex3d(-.5-distance,-nb-nb2,-nb-nb2+.5);

		glEnd();
		glPopMatrix();

}
//==============================================================================
//                                                                               
// _|          _|  _|_|_|_|    _|_|    _|_|_|      _|_|    _|      _|    _|_|_|  
// _|          _|  _|        _|    _|  _|    _|  _|    _|  _|_|    _|  _|        
// _|    _|    _|  _|_|_|    _|_|_|_|  _|_|_|    _|    _|  _|  _|  _|    _|_|    
//   _|  _|  _|    _|        _|    _|  _|        _|    _|  _|    _|_|        _|  
//     _|  _|      _|_|_|_|  _|    _|  _|          _|_|    _|      _|  _|_|_|    
//                                                                               
//==============================================================================
//==============================================================================
//==============================================================================
void draw_half_bow(double noise,double force){
	force+=.5;
	glPushMatrix();
		glColor4d(1,0,0,1);
		gluCylinder(quad,random(1,noise),random(1,noise),3,8,1);
		glTranslated(0,0,3);
		glRotated(force*2,1,0.,0.);
		gluCylinder(quad,random(1,noise),random(1.5,noise),1,8,1);
		glTranslated(0,0,1);
		glRotated(force*2,1,0.,0.);
		gluCylinder(quad,random(1.5,noise),random(1.5,noise),1,8,1);
		glTranslated(0,0,1);
		gluCylinder(quad,random(1.5,noise),random(.8,noise),0,8,1);
		// glTranslated(0,0,0);
		// glColor4d(1,.6,.6,1);
		glRotated(force*10,1,0.,0.);
		gluCylinder(quad,random(.8,noise),random(.7,noise),5,8,1);

		glTranslated(0.,0.,5);

		double length=3.;
		glRotated(force*5,1,0.,0.);
		gluCylinder(quad,random(.7,noise),random(.7,noise),length,8,1);
		glTranslated(0.,0.,length);


		glRotated(force*10,1,0.,0.);
		gluCylinder(quad,random(.7,noise),random(.7,noise),length,8,1);
		glTranslated(0.,0.,length);


		glRotated(force*20,1,0.,0.);
		gluCylinder(quad,random(.7,noise),random(.6,noise),length,8,1);
		glTranslated(0.,0.,length);

		glRotated(force*10,1,0.,0.);
		gluCylinder(quad,random(.6,noise),random(.5,noise),length,8,1);
		glTranslated(0.,0.,length);

		force = force +1;
		glRotated(360-10/force,1,0.,0.);
		gluCylinder(quad,random(.5,noise),random(.4,noise),length,8,1);
		glTranslated(0.,0.,length);

		glRotated(360-20/force,1,0.,0.);
		gluCylinder(quad,random(.4,noise),random(.3,noise),length,8,1);
		glTranslated(0.,0.,length);


		glRotated(360-5/force,1.,0.,0.);
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
		// glRotated(180*(1-force*.3),180*(1-force*.3),0.,1.);
		glRotated(180*(1-force*.3),1.,0,0.);
		gluCylinder(quad,random(.05,noise*.1),random(.05,noise*.1),30.0-2*force,8,1);

	glPopMatrix();
}

void draw_half_bow_v2(double noise,double force){
	draw_half_bow(noise,force);
	glPushMatrix();
		glTranslated(0,0,4);
		glRotated(-90,0,1,0);
		gluCylinder(quad,.2,.2,2,8,1);
		glTranslated(0,0,2);
		glRotated(45,1,-1,0);
		gluCylinder(quad,.2,.2,2,8,1);
		glTranslated(0,0,2);
		glRotated(90,1,0,0);
		// gluCylinder(quad,.2,.2,2,8,1);
		// glTranslated(0,0,2);

		// glRotated(90+20*cos(SDL_GetTicks()*0.01),0,0,1);
		glRotated(90,0,0,1);
		// glRotated(20*cos(SDL_GetTicks()*0.01),1,0,0);
		glRotated(20,1,0,0);
		// glColor4d(0,1,0,1);
		// glScaled(1,1.5,1);
		for(int i=0;i<20;i++){
			double x=i/20.;
			double x_=(i-1)/20.;
			glRotated(40*x,1,0,0);
			glRotated(-40*x,0,1,0);
			gluCylinder(quad,.2*(1-x_),.2*(1-x),1+x,8,1);
			glTranslated(0,0,1+x);
		}
		// glColor4d(1,0,0,1);

	glPopMatrix();

	glPushMatrix();
		glTranslated(0,0,4);
		for(int i=0;i<20;i++){
			double x=i/20.;
			double x_=(i-1)/20.;
				glRotated(20,0,-.7,1);
				gluCylinder(quad,.2*(1-x_),.2*(1-x),1,8,1);
				glTranslated(0,0,1);
		}

	glPopMatrix();



	glPushMatrix();













		// glColor4d(0,1,0,1);

		glTranslated(0,0,3);
		glRotated(force*2,1,0.,0.);
		glTranslated(0,0,1);
		glRotated(force*2,1,0.,0.);
		glTranslated(0,0,1);
		glRotated(force*10,1,0.,0.);

		glPushMatrix();
			glTranslated(0,0,2);
			glRotated(-90,0,1,0);
			gluCylinder(quad,1,0,3,8,1);
			glRotated(-180,0,1,0);
			gluCylinder(quad,1,0,3,8,1);
		glPopMatrix();

		glTranslated(0.,0.,5);
		double length=3.;
		glRotated(force*5,1,0.,0.);

		glPushMatrix();
			glTranslated(0,-.5,0);
			glRotated(-90,0,1,0);
			gluCylinder(quad,1,0,2,8,1);
			glRotated(-180,0,1,0);
			gluCylinder(quad,1,0,2,8,1);
		glPopMatrix();
		// glPushMatrix();
		// 	glTranslated(0,-2,10);
		// 	glRotated(-90,0,1,0);
		// 	glColor4d(0,1,0,1);
		// 	gluCylinder(quad,1,0,3,8,1);
		// glPopMatrix();

		// glTranslated(0.,0.,length);


		// glRotated(force*10,1,0.,0.);
		// glTranslated(0.,0.,length);


		// glRotated(force*20,1,0.,0.);
		// glTranslated(0.,0.,length);

		// glRotated(force*10,1,0.,0.);
		// glTranslated(0.,0.,length);

		// force = force +1;
		// glRotated(360-10/force,1,0.,0.);
		// glTranslated(0.,0.,length);

		// glRotated(360-20/force,1,0.,0.);
		// glTranslated(0.,0.,length);


		// glRotated(360-5/force,1.,0.,0.);
		// glTranslated(0.,0.,length);




























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

void draw_bow_v2(double noise,double force){
	gluQuadricDrawStyle(quad, GLU_FILL);
	glPushMatrix();
		glScaled(.25,.25,.25);
		draw_half_bow_v2(noise,force);
		glPushMatrix();
			glScaled(1,1,-1);
			draw_half_bow_v2(noise,force);
		glPopMatrix();
	glPopMatrix();

	gluQuadricDrawStyle(quad, GLU_LINE);
	glPushMatrix();
		glScaled(.25,.25,.25);
		draw_half_bow_v2(noise,force);
		glPushMatrix();
			glScaled(1,1,-1);
			draw_half_bow_v2(noise,force);
		glPopMatrix();
	glPopMatrix();
}

void draw_bow_to_take(double noise,double force){
	draw_bow(noise,force);
}
//==================================================
//==================================================
//==================================================
void draw_arrow_high_quality(){
		glPushMatrix();
			// glTranslated(-1,10,0);
			// glRotated(t,1,0,0);
			gluQuadricDrawStyle(quad, GLU_FILL);

			//fleche
			gluCylinder(quad,.04,.2,1,3,1);
			glTranslated(0,0,1);

			//tige
			gluCylinder(quad,.04,.04,9,3,1);

			glTranslated(0,0,7);
			gluCylinder(quad,.08,.2,.5,2,1);
			glTranslated(0,0,.5);
			gluCylinder(quad,.2,.2,1,2,1);

			glTranslated(0,0,-.5);
			glRotated(90,0,0,1);

			gluCylinder(quad,.08,.2,.5,2,1);
			glTranslated(0,0,.5);
			gluCylinder(quad,.2,.2,1,2,1);

		glPopMatrix();
}
void draw_arrow_low_quality(){
		glLineWidth(3);
		glBegin(GL_LINES);
			glVertex3d(0,0,0);
			glVertex3d(0,0,1);
		glEnd();

		glLineWidth(1);
		glBegin(GL_LINES);
			glVertex3d(0,0,1);
			glVertex3d(0,0,10);
		glEnd();

		glLineWidth(4);
		glBegin(GL_LINES);
			glVertex3d(0,0,8);
			glVertex3d(0,0,9.5);
		glEnd();
}
void draw_arrow_ground_high_quality(){
		glPushMatrix();
			// glTranslated(-1,10,0);
			// glRotated(t,1,0,0);
			gluQuadricDrawStyle(quad, GLU_FILL);

			//tige
			gluCylinder(quad,.04,.04,10,3,1);

			glTranslated(0,0,8);
			gluCylinder(quad,.08,.2,.5,2,1);
			glTranslated(0,0,.5);
			gluCylinder(quad,.2,.2,1,2,1);

			glTranslated(0,0,-.5);
			glRotated(90,0,0,1);

			gluCylinder(quad,.08,.2,.5,2,1);
			glTranslated(0,0,.5);
			gluCylinder(quad,.2,.2,1,2,1);

		glPopMatrix();

}
void draw_arrow_ground_low_quality(){
		glLineWidth(1);
		glBegin(GL_LINES);
			glVertex3d(0,0,1);
			glVertex3d(0,0,10);
		glEnd();

		glLineWidth(4);
		glBegin(GL_LINES);
			glVertex3d(0,0,8);
			glVertex3d(0,0,9.5);
		glEnd();
}

void draw_arrow_ground_very_low_quality(){
		glLineWidth(1);
		glBegin(GL_LINES);
			glVertex3d(0,0,1);
			glVertex3d(0,0,10);
		glEnd();
}


































void draw_sulfateuse(double noise,double angle, int color){

	angle=SDL_GetTicks()*0.5;
	gluQuadricDrawStyle(quad, GLU_FILL);
	// gluQuadricDrawStyle(quad, GLU_LINE);

	//POIGNEE
	glPushMatrix();
		glScaled(.25,.25,.25);

		if(color)
			glColor4d(.6,0,0,1);
		else
			glColor4d(1,0,0,1);
		glTranslated(0,0,-4);
		gluCylinder(quad,random(1,noise),0,0,8,1);
		gluCylinder(quad,random(1,noise),random(1,noise),7,8,1);
		// glTranslated(0,0,1);
		glTranslated(0,0,7);
		gluCylinder(quad,random(1,noise),random(1.5,noise),1,8,1);
		glTranslated(0,0,1);
		gluCylinder(quad,random(1.5,noise),random(1.5,noise),1,8,1);
		glTranslated(0,0,1);
		gluCylinder(quad,random(1.5,noise),random(.8,noise),0,8,1);
		glRotated(30,0,1,0);
		gluCylinder(quad,random(.8,noise),random(.7,noise),3,8,1);
		glTranslated(0,0,3);
		glRotated(60-30,0,1,0);
		gluCylinder(quad,random(.8,noise),random(.7,noise),15,8,1);
	glPopMatrix();


	glPushMatrix();
		if(color){
			glScaled(1.7,1,1.7);
			glTranslated(.5,0,-1);
		}

		//a droite
		glTranslated(0,0,3);
		//en bas
		glTranslated(3,0,0);
		// glRotated(90+10*cos(SDL_GetTicks()*0.005),1,0,0);
		glRotated(100,1,0,0);

		glTranslated(0,0,-10);

		double width;
		double diameter;

		//PARTIE ROTATIVE
		glPushMatrix();
		glRotated(angle,0,0,1);
				width =2;
				diameter=2;
				glPushMatrix();
					glTranslated(0,0,1.4);
					gluCylinder(quad,0,diameter ,0  ,8,1);
					gluCylinder(quad,diameter,diameter ,width,8,1);
					glTranslated(0,0,width);
					gluCylinder(quad,0,diameter ,0  ,8,1);
				glPopMatrix();

				// glPushAttrib(GL_CURRENT_BIT);
				// glColor4d(0.8,0,0,1);
				// glPushMatrix();
				// 	glRotated(90,1,0,0);
				// 	glTranslated(0,2,-2.05);
				// 	glScaled(1,2,1);
				// 	gluCylinder(quad,.5,.5 ,4.1  ,8,1);
				// 	// glTranslated(0,2.8,0);
				// 	// gluCylinder(quad,.5,.5 ,2.1  ,8,1);
				// 	// glTranslated(0,0,2.1);
				// 	gluCylinder(quad,.5,0 ,0  ,8,1);
				// 	glTranslated(0,0,4.1);
				// 	gluCylinder(quad,.5,0 ,0  ,8,1);
				// glPopMatrix();
				// glPopAttrib();

				width =.5;
				// glPushMatrix();
				// 	glTranslated(0,0,1);
				// 	gluCylinder(quad,0,diameter ,0  ,8,1);
				// 	gluCylinder(quad,diameter,diameter ,width,8,1);
				// 	glTranslated(0,0,width);
				// 	gluCylinder(quad,0,diameter ,0  ,8,1);
				// glPopMatrix();

				diameter = 1.5;
				glPushMatrix();
					glTranslated(0,0,6);
					gluCylinder(quad,0,diameter ,0  ,8,1);
					gluCylinder(quad,diameter,diameter ,width,8,1);
					glTranslated(0,0,width);
					gluCylinder(quad,0,diameter ,0  ,8,1);
				glPopMatrix();

				glPushMatrix();
					glTranslated(0,0,7);
					gluCylinder(quad,0,diameter ,0  ,8,1);
					gluCylinder(quad,diameter,diameter ,width,8,1);
					glTranslated(0,0,width);
					gluCylinder(quad,0,diameter ,0  ,8,1);
				glPopMatrix();


				//partie qui tourne
				double count=6;
				double cylinder_diameter=.3;
				double cycle_diameter=1;

				// count=3;
				// cylinder_diameter=.5;
				// cycle_diameter=.8;

				glPushAttrib(GL_CURRENT_BIT);
				if(color)
					glColor4d(.8,0,0,1);
				else
					glColor4d(.9,0,0,1);

				if(color){
					count=6;
					cylinder_diameter=.3;
					cycle_diameter=1;
				}

				for (int i=0;i<count;i++){
					glPushMatrix();
						// glColor4d(i/count,0,0,1);
						glRotated(i*360./count,0,0,1);
						glTranslated(0,cycle_diameter,0);
						gluCylinder(quad,cylinder_diameter,cylinder_diameter ,10,8,1);
					glPopMatrix();
				}
				glPopAttrib();


		glPopMatrix();

		width =5;
		diameter = 2;
		glPushMatrix();
			glTranslated(.5,0,9.5);
			gluCylinder(quad,0,diameter ,0  ,7,1);
			gluCylinder(quad,diameter,diameter ,width,7,1);
			glTranslated(0,0,width);
			gluCylinder(quad,0,diameter ,0  ,7,1);
		glPopMatrix();

		width =4;
		diameter = 1;
		// glColor4d(.9,0,0,1);
		glPushMatrix();
			glTranslated(-1,1,11);
			gluCylinder(quad,0,diameter ,0  ,8,1);
			gluCylinder(quad,diameter,diameter ,width,8,1);
			glTranslated(0,0,width);
			gluCylinder(quad,0,diameter ,0  ,8,1);
		glPopMatrix();


	glPopMatrix();
}

























