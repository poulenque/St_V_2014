#include "draw.h"

#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <SDL/SDL.h>
#include "constants.h"
#include "random.h"


static GLUquadric* quad;

void draw_init(){
	quad=gluNewQuadric();
}


void change_bg_color(double r,double g,double b){
	GLfloat fogColor[4]= {r,g,b, 1};
	glFogfv(GL_FOG_COLOR, fogColor);
	glClearColor(r,g,b,1);
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
	glBegin(GL_QUADS);
		glVertex3f(  0.5, -0.5, 0.5 );
		glVertex3f(  0.5,  0.5, 0.5 );
		glVertex3f( -0.5,  0.5, 0.5 );
		glVertex3f( -0.5, -0.5, 0.5 );

		glVertex3f( 0.5, -0.5, -0.5 );
		glVertex3f( 0.5,  0.5, -0.5 );
		glVertex3f( 0.5,  0.5,  0.5 );
		glVertex3f( 0.5, -0.5,  0.5 );

		glVertex3f( -0.5, -0.5,  0.5 );
		glVertex3f( -0.5,  0.5,  0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
		glVertex3f( -0.5, -0.5, -0.5 );

		glVertex3f(  0.5,  0.5,  0.5 );
		glVertex3f(  0.5,  0.5, -0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
		glVertex3f( -0.5,  0.5,  0.5 );

		glVertex3f(  0.5, -0.5, -0.5 );
		glVertex3f(  0.5, -0.5,  0.5 );
		glVertex3f( -0.5, -0.5,  0.5 );
		glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();
 
}
void simple_cube_color(double r1,double g1,double b1,double r2,double g2,double b2){
	glBegin(GL_QUADS);

		glColor4d(r1,g1,b1,1);
		glVertex3f(  0.5, -0.5, 0.5 );
		glVertex3f(  0.5,  0.5, 0.5 );
		glVertex3f( -0.5,  0.5, 0.5 );
		glVertex3f( -0.5, -0.5, 0.5 );

		glColor4d(r2,g2,b2,1);
		glVertex3f( 0.5, -0.5, -0.5 );
		glVertex3f( 0.5,  0.5, -0.5 );
		glColor4d(r1,g1,b1,1);
		glVertex3f( 0.5,  0.5,  0.5 );
		glVertex3f( 0.5, -0.5,  0.5 );

		glVertex3f( -0.5, -0.5,  0.5 );
		glVertex3f( -0.5,  0.5,  0.5 );
		glColor4d(r2,g2,b2,1);
		glVertex3f( -0.5,  0.5, -0.5 );
		glVertex3f( -0.5, -0.5, -0.5 );
		glColor4d(r1,g1,b1,1);

		glVertex3f(  0.5,  0.5,  0.5 );
		glColor4d(r2,g2,b2,1);
		glVertex3f(  0.5,  0.5, -0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
		glColor4d(r1,g1,b1,1);
		glVertex3f( -0.5,  0.5,  0.5 );


		glVertex3f(  0.5, -0.5,  0.5 );
		glVertex3f( -0.5, -0.5,  0.5 );
		glColor4d(r2,g2,b2,1);
		glVertex3f( -0.5, -0.5, -0.5 );
		glVertex3f(  0.5, -0.5, -0.5 );
		glColor4d(r1,g1,b1,1);

		// glColor4d(1,0,0,1);
		// glColor4d(0,1,0,1);
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



void draw_strange_ball(double heart_beat_time,double heart_beat_time_normalized,int quality){
	int i_max=40;
	int j_max=40;
	if (quality==2){
		i_max=15;
		j_max=15;
	}else if(quality==1){
		i_max=10;
		j_max=10;
	}else if(quality==0){
		i_max=5;
		j_max=5;
	}
	glDisable(GL_POINT_SMOOTH);
	// glColor4d(1,0,0,1);
	glPointSize(10);
	for(int i=-i_max;i<i_max;i++){
		for(int j=-j_max;j<j_max;j++){
			double R;
			// double t=fmod(time_,deltat);
			double t=heart_beat_time;

			// R=exp(-4*t)*sin(heart_beat_time_normalized*2*PI* (16-16*heart_beat_time_normalized) )+10;
			double theta = PI*i/i_max;
			double phi = PI*(i_max+j/(2.*j_max));
			// R=2*exp(-4*t)*sin(fabs(.3*theta) * heart_beat_time_normalized*2*PI* 8*exp(-2*heart_beat_time_normalized) )+10;
			// R=2*exp(-4*t)*sin(fabs(2*theta) + heart_beat_time_normalized*2*PI* 8*exp(-2*heart_beat_time_normalized) )+10;
			R=2*exp(-4*t)*sin(fabs(2*theta) + 2*phi + heart_beat_time_normalized*2*PI* 8*exp(-2*heart_beat_time_normalized) )+3;
			// R=((fabs(theta)+1)*10+9*cos(5*time_+2*phi))/(2+sin(phi+time_));
			// R = exp( sin (theta*2*phi*cos(time_*0.05)) );
			// R =  sin (theta*2*phi*(1+cos(time_*0.05))) ;
			// R = (theta-phi)*sin (theta+2*phi+time_) ;
			// R = 10 *sin(2*theta-time_)/(2+cos(2*phi+time_));

			// glColor4d(.5+.5*cos(time_),0.4,0,1);
			glBegin(GL_POINTS);
				// glVertex3d(R*cos(theta)*sin(phi),R*sin(theta)*sin(phi),R*cos(theta));
				glVertex3d(R*sin(theta)*cos(phi),R*sin(theta)*sin(phi),R*cos(theta));
			glEnd();
		}
	}
}












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

	noise-=.2;

	// if (noise>1)noise=1;

	if (detail==0){

		// glColor4d(0,0,0,1);

		noise=2*noise;

		glLineWidth(3.0+noise);
		glBegin(GL_LINES);
			glVertex3d(0,0,1+noise);
			glVertex3d(0,0,0+noise);
		glEnd();
		glLineWidth(2.0+noise);
		glBegin(GL_LINES);
			glVertex3d(0,0,0+noise);
			glVertex3d(0,0,-1+noise);
		glEnd();

		glLineWidth(7.0+noise);
		glBegin(GL_LINES);
			glVertex3d(0,0,-1+noise);
			glVertex3d(0,0,-1.4+noise);
		glEnd();
		glLineWidth(4+noise);
		glBegin(GL_LINES);
			glVertex3d(0,0,-1.4+noise);
			glVertex3d(0,0,-2.2+noise);
		glEnd();
		glLineWidth(2.0+noise);
		glBegin(GL_LINES);
			glVertex3d(0,0,-2.2+noise);
			glVertex3d(0,0,-3+noise);
		glEnd();
		glLineWidth(4+noise);
		glBegin(GL_LINES);
			glVertex3d(0,0,-3+noise);
			glVertex3d(0,0,-4+noise);
		glEnd();
		glLineWidth(7+noise);
		glBegin(GL_LINES);
			glVertex3d(0,0,-4+noise);
			glVertex3d(0,0,-5);
		glEnd();
		return;
	}

	int cylinder_subivision=8;
	if(detail==1)
		cylinder_subivision=4;

	gluQuadricDrawStyle(quad, GLU_FILL);

	//REAL OBJECT
	glPushMatrix();

		// glTranslated(0,0,1);
		// glColor4d(0,0,0,1);

		double x=noise/4.;
		double y=noise/2.;
		double a=noise*2;
		//HEAD
		// glTranslated(0,0,-1.);
		glTranslated(0,0,3*x);
		glPushMatrix();
			glRotated(random(0,noise*40),random(0,noise*40),random(0,noise*40),1);
			// gluCylinder(quad,random(.5,noise), random(1,noise), 1.,cylinder_subivision,1);
			gluCylinder(quad,random(.5+y,a), random(1+y,a), 1.+x,cylinder_subivision,1);
		glPopMatrix();


		glTranslated(0,0,-1.-x);
		glPushMatrix();
			glRotated(random(0,noise*40),random(0,noise*40),random(0,noise*40),1);
			// gluCylinder(quad,0.,random(.5,noise),1.,cylinder_subivision,1);
			gluCylinder(quad,0.,random(.5+y,a),1.+x,cylinder_subivision,1);
		glPopMatrix();


		//BODY
		glTranslated(0,0,-2.-x);
		glPushMatrix();

			if(detail>=2){
				glRotated(random(0,noise*40),random(0,noise*40),random(0,noise*40),1);
				// gluCylinder(quad,random(1-.5,noise),random(1+.5,noise),2.,cylinder_subivision,1);
				gluCylinder(quad,random(1-.5+y,a),random(1+.5+y,a),2.+x,cylinder_subivision,1);
			}
			glRotated(random(0,noise*40),random(0,noise*40),random(0,noise*40),1);
			gluCylinder(quad,1-.5,1+.5,2.+x,cylinder_subivision,1);
		glPopMatrix();

		glTranslated(0,0,-2.-x);
		glPushMatrix();

			if(detail>=2){
				glRotated(random(0,noise*40),random(0,noise*40),random(0,noise*40),1);
				// gluCylinder(quad,random(1+.5,noise),random(1-.5,noise),2.,cylinder_subivision,1);
				gluCylinder(quad,random(1+.5+y,a),random(1-.5+y,a),2.+x,cylinder_subivision,1);
			}
			glRotated(random(0,noise*40),random(0,noise*40),random(0,noise*40),1);
			gluCylinder(quad,1+.5,1-.5,2+x,cylinder_subivision,1);
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

void draw_heart_half(double lambda0,int quality,int reflexion){
	//source : http://mathworld.wolfram.com/BonneProjection.html
	const double phi1 = 85.*PI/180.;
	double phi;
	double lambda;

	double rho;
	double E;
	double x;
	double y;

	// int i_MAX=30;
	// int j_MAX=30;
	// for(int i=0;i<=i_MAX;i++){
	// 	glBegin(GL_LINE_STRIP);

	// 	for(int j=0;j<=j_MAX;j++){

	// 		lambda=i*2*PI/i_MAX-PI;
	// 		lambda0=0;
	// 		phi=j*PI/j_MAX-PI/2.;


	// 		rho=1./tan(phi1)+phi1 - phi;
	// 		E=(lambda-lambda0)*cos(phi)/rho;
	// 		x=rho*sin(E);
	// 		y=1./tan(phi1)-rho*cos(E) + 1;
	// 		// glVertex3d(x,sin(y+SDL_GetTicks()*0.01),y);
	// 		// printf("%lf\n",x );
	// 		glVertex3d(0,x,y);
	// 		// glVertex3d(x,-cos(x),y);
	// 		// glVertex3d(x,-cos(x)+sin(y),y);
	// 		// glVertex3d(x,0,y);
	// 	}
	// 	glEnd();
	// }

	// double t=fmod(time_,deltat);
	// R=2*exp(-4*t)*sin(fabs(2*theta) + 2*phi + t/deltat*2*PI* 8*exp(-2*t/deltat) )+10;

	int i_MAX=1;
	int j_MAX=20;
	int k_MAX=7;
	double w=1;
	if(quality==1){
		j_MAX=7;
		k_MAX=5;
		w=1.2;
	}else 	if(quality==0){
		j_MAX=5;
		k_MAX=3;
		w=1.5;
	}


	GLfloat bkColor[3];
	glGetFloatv(GL_COLOR_CLEAR_VALUE, bkColor);
	double r_color=.5+.5*bkColor[0];
	double g_color=0+.5*bkColor[1];
	double b_color=0+.5*bkColor[2];

	for (int k=0;k<k_MAX;k++){
		double a=k*1./k_MAX;
		for(int i=0;i<=i_MAX;i++){
			// glBegin(GL_LINE_STRIP);
			glBegin(GL_POLYGON);

			for(int j=0;j<=j_MAX;j++){

				lambda=i*2*PI/i_MAX-PI;
				phi=j*PI/j_MAX-PI/2.;

				double cot=1./tan(phi1);

				rho=cot + phi1 - phi;
				E=(lambda-lambda0)*cos(phi)/rho;
				x=rho*sin(E);
				y=cot-rho*cos(E) + 1;

				if(reflexion){
					glColor4d(r_color,g_color,b_color,1);
				}else{
					glColor4d(1-j*.5/j_MAX,0,0,1);
				}

				if(lambda<0){
					x=x*a- (1-a)*(.0*cos(phi));
					y=y*a+ (1-a)*(.0*sin(phi)+.6);
				}else{
					x=x*a+ (1-a)*(.0*cos(phi));
					y=y*a+ (1-a)*(.0*sin(phi)+.6);
				}
				glVertex3d(-.7*cos(a*PI/2.),w*x,w*y);
			}
			glEnd();
		}
	}

	j_MAX=2;

	for(int i=0;i<=i_MAX;i++){

		for(int j=0;j<=j_MAX;j++){
			// glBegin(GL_LINE_STRIP);
			glBegin(GL_POLYGON);
			for (int k=0;k<k_MAX;k++){
				double a=k*1./k_MAX;


				lambda=i*2*PI/i_MAX-PI;
				phi=j*PI/j_MAX-PI/2.;

				double cot=1./tan(phi1);
				double cosphi=cos(phi);

				rho=cot + phi1 - phi;
				E=(lambda-lambda0)*cosphi/rho;
				x=rho*sin(E);
				y=cot-rho*cos(E) + 1;
				if(reflexion){
					glColor4d(r_color,g_color,b_color,1);
				}else{
					glColor4d(1-j*.5/j_MAX,0,0,1);
				}
				if(lambda<0){
					x=x*a- (1-a)*(.0*cosphi);
					y=y*a+ (1-a)*(.0*sin(phi)+.6);
				}else{
					x=x*a+ (1-a)*(.0*cosphi);
					y=y*a+ (1-a)*(.0*sin(phi)+.6);
				}
				if(k==0||k==k_MAX-1){
					if(reflexion){
						glColor4d(r_color,g_color,b_color,1);
					}else{
						glColor4d(1-.2,0,0,1);
					}
					glVertex3d(0,x,y);
				}
				glVertex3d(-.7*cos(a*PI/2.),w*x,w*y);
			}
			glEnd();
		}
	}

}
void draw_heart(double lambda0,int quality,int reflexion){
	glPushMatrix();
		glScaled(-2,2,2);
		draw_heart_half(lambda0,quality,reflexion);
		glScaled(-1,1,1);
		draw_heart_half(lambda0,quality,reflexion);
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
	double t=SDL_GetTicks()/15.;
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
						glVertex3d(.4, .5, .16);
						glVertex3d(.4, .5,-.16);

						//index droite
						glVertex3d(-.5, .0, .19);
						glVertex3d(-.5, .3, .16);
						glVertex3d( .4, .5, .16);
						glVertex3d( .4, .0, .19);

						//index gauche
						glVertex3d(-.5, .0,-.19);
						glVertex3d(-.5, .3,-.16);
						glVertex3d( .4, .5,-.16);
						glVertex3d( .4, .0,-.19);

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


			//main dessus cache trou
		// glColor4d(0,1,0,1);
			glVertex3d(-.5, .5, .2);
			glVertex3d(-.5, .4,-.3);
		// glColor4d(.8,.6,.4,1);
			glVertex3d(-.5,-.6,-.5);
			glVertex3d(-.5,-.6, .4);
			//main dessus
			glVertex3d(-.5, .4, .6);
			glVertex3d(-.5, .2,-.7);
			glVertex3d(-.5,-.6,-.5);
			glVertex3d(-.5,-.6, .4);

			//main droite
			glVertex3d(-.5, .4, .6);
			glVertex3d(-.5,-.6, .4);
			glVertex3d(-.0,-.6, .7);
			glVertex3d(.2, .4, 1.);

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















void draw_half_bow_v3(double noise,double force){
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
		// glScaled(1,1.5,1);
		for(int i=0;i<20;i++){
			double x=i/20.;
			double x_=(i-1)/20.;
			glRotated(40*x,1,0,0);
			glRotated(-40*x,0,1,0);
			gluCylinder(quad,.2*(1-x_),.2*(1-x),1+x,8,1);
			glTranslated(0,0,1+x);
		}

	glPopMatrix();

	// glColor4d(0,1,0,1);

	// for(int j=0;j<10;j++){
	glPushMatrix();
		// double y=j/10.;
		// glRotated(y*360,0,0,1);
		glTranslated(0,0,4);
		for(int i=0;i<20;i++){
			double x=i/20.;
			double x_=(i-1)/20.;
				// glRotated(20*(1+y),0+cos(SDL_GetTicks()*.005),-.7+sin(SDL_GetTicks()*.005),1);
				// gluCylinder(quad,.2*(1-x_),.2*(1-x),1+y,8,1);
				// glTranslated(0,0,1+y);
				glRotated(20,0,-.7,1);
				gluCylinder(quad,.2*(1-x_),.2*(1-x),1,8,1);
				glTranslated(0,0,1);
		}
	glPopMatrix();
	// }

	// glColor4d(1,0,0,1);

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

void draw_bow_v3(double noise,double force){
	gluQuadricDrawStyle(quad, GLU_FILL);
	glPushMatrix();
		glScaled(.25,.25,.25);
		draw_half_bow_v3(noise,force);
		glPushMatrix();
			glScaled(1,1,-1);
			draw_half_bow_v3(noise,force);
		glPopMatrix();
	glPopMatrix();

	gluQuadricDrawStyle(quad, GLU_LINE);
	glPushMatrix();
		glScaled(.25,.25,.25);
		draw_half_bow_v3(noise,force);
		glPushMatrix();
			glScaled(1,1,-1);
			draw_half_bow_v3(noise,force);
		glPopMatrix();
	glPopMatrix();
}

void draw_bow_to_take(double noise,double force){
	draw_bow(noise,force);
}
//==================================================
//==================================================
//==================================================
void draw_arrow_high_quality_no_heart(){
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
void draw_arrow_high_quality(){
		glPushMatrix();
			// glTranslated(-1,10,0);
			// glRotated(t,1,0,0);
			gluQuadricDrawStyle(quad, GLU_FILL);

			//fleche
			gluCylinder(quad,.04,.2,1,3,1);

			for(int j=-10;j<=10;j++){
			double y=j/10.;
			glPushAttrib(GL_CURRENT_BIT);
			// glBegin(GL_LINE_STRIP);
			glBegin(GL_POLYGON);
				for(int i=0;i<40;i++){
					double x=i/40.*2*PI + PI/2.;
					double r=2-2*sin(x)+sin(x)*sqrt(fabs(cos(x)))/(sin(x)+1.4+fabs(y));
					// r/=6.+fabs(16*y);

					r/=6.;
					r*=cos(PI*y/2.);

					// glColor4d(1,1-fabs(y),0,1);
					double w=0;
					if(i<10){
						w+=(10-i)/10.;
					}
					if(i>30){
						w+=(i-30)/10.;
					}
					glColor4d(1-w/4.,0,0,1);
					glVertex3d(r*cos(x),y*.2,3*r*sin(x)+1);
				}
			glEnd();
			}
			glPopAttrib();

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
		glTranslated(0,0,10);
		glRotated(.5,0,1,0);
		glTranslated(0,0,-10);
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


				if(color){
				// glPushAttrib(GL_CURRENT_BIT);
				// glColor4d(0,1,0,1);
					glLineWidth(4);
					for(int j=0;j<10;j++){
						double y=j/10.;
						// y=sin(y*PI);
					glBegin(GL_LINE_STRIP);
						for(int i=0;i<10;i++){
								double x=(i+1)/10.;
								glVertex3d(1.4*cos(-x*PI+y*2*PI),1.4*sin(-x*PI+y*2*PI),2+x*8);
						}
					glEnd();
					}
				// glPopAttrib();
				}

				glPushAttrib(GL_CURRENT_BIT);
				if(color)
					glColor4d(.8,0,0,1);
				else
					glColor4d(.85,0,0,1);
					// glColor4d(.9,0,0,1);
					// glColor4d(0,0,0,1);

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

























