#include "string3d.h"
#include "constants.h"
#include <GL/glew.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

String3d* new_string3d(){
	String3d* s=malloc(sizeof(String3d));
	s->str=malloc(1024*sizeof(char));

	s->size=0.01;
	s->noise=1/5.;
	s->dist=0.5;
	s->rho=0;
	s->phi=0;
	s->theta=0;

	s->x=0;
	s->y=0;
	s->z=0;

	return s;
}

void string3d_setTxt(String3d* s,const char* str){
	//toLowerCase
	strcpy(s->str,str);
	int i=0;
	while(s->str[i]){
		s->str[i]=tolower(s->str[i]);
		i++;
	}
}

double noise_gen(double around,double noise){
	return around*(1+noise*rand()/RAND_MAX-noise/2);
}

void string3d_draw(String3d* s){

	double size = s->size;	
	double dist= s->dist;
	double noise=s->noise;

	glPushMatrix();//initialise ecriture
		glTranslated(s->x,s->y,s->z);

		//glRotated(rho,1,0,0);
		glTranslated(s->rho,0,0);
		//glRotated(theta, 0.0, 1.0, 0.0);
		glTranslated(0,0,s->theta);
		glRotated(s->phi, 0.0, 0.0, 1.0);
		glTranslated(dist,0,0);
	

	
	int charCount=0;
	int i=0;
	while(s->str[i]){			
			
		glLineWidth(3.0);
		glPointSize(3.0);

		//deplace le curseur
		//glRotated(rho,1,0,0);
		glTranslated(-dist,0,0);
		glRotated(-size/dist*360/2./PI *3/2 , 0.0, 0.0, 1.0);
		glTranslated(dist,0,0);
		charCount++;
		if (s->str[i] == '\n' ){
			glTranslated(-dist,0,0);
			glRotated(+charCount*size/dist*360/2./PI *3/2 , 0.0, 0.0, 1.0);//revient au début de la ligne
			//glRotated(size/dist*360/2./PI *3/2 , 0.0, 1.0, 0.0);
			glTranslated(0,0,-size*1.5);///dist*.75);
			glTranslated(dist,0,0);
			
			charCount=0;
		}
		else if (s->str[i] == 'a' ){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/2);
			glEnd();
		}
		else if (s->str[i] == 'b' ){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,noise_gen(size,noise)/2);
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
				glVertex3d(0,noise_gen(size,noise)-0,0);
			glEnd();
		
		}
		else if (s->str[i] == 'c' ){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
			glEnd();
		}
		else if (s->str[i] == 'd' ){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
				glVertex3d(0,noise_gen(size,noise)-0,0);
			glEnd();
		}
		else if (s->str[i] == 'e' ){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/2);
			glEnd();
		}
		else if (s->str[i] == 'f' ){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/2);
			glEnd();
		}
		else if (s->str[i] == 'g'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,noise_gen(size,noise)/2);
			glEnd();
		}
		else if (s->str[i] == 'h'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/2);
			glEnd();
		}
		else if (s->str[i] == 'i' ){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,noise_gen(size,noise));
			glEnd();
		}
		else if (s->str[i] == 'j' ){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,noise_gen(size,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
			glEnd();
		}
		else if (s->str[i] == 'k'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
			glEnd();
		}
		else if (s->str[i] == 'l' ){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
			glEnd();
		}
		else if (s->str[i] == 'm'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,noise_gen(size,noise)/2);
			glEnd();
		}
		else if (s->str[i] == 'n'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
			glEnd();
		}
		else if (s->str[i] == 'o'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
				glVertex3d(0,noise_gen(size,noise)-0,0);
			glEnd();
		}
		else if (s->str[i] == 'p'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/2);
			glEnd();
		}
		else if (s->str[i] == 'q'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/2);
			glEnd();
		}
		else if (s->str[i] == 'r'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/2);
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,0);
			glEnd();
		}
		else if (s->str[i] == 's'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/4);
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),3.*noise_gen(size,noise)/4.);
			glEnd();
		}
		else if (s->str[i] == 't'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,0);
			glEnd();
		}
		else if (s->str[i] == 'u'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
			glEnd();
		}
		else if (s->str[i] == 'v'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
			glEnd();
		}
		else if (s->str[i] == 'w'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,noise_gen(size,noise)/2);
			glEnd();
		}
		else if (s->str[i] == 'x'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
			glEnd();
		}
		else if (s->str[i] == 'y'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/2);
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
				glVertex3d(0,noise_gen(size,noise)-0,0);
			glEnd();
		}
		else if (s->str[i] == 'z'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
			glEnd();
		}
		else if (s->str[i] == '?'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,noise_gen(size,noise)/2);
			glEnd();
			glBegin(GL_POINTS);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,0);
			glEnd();
		}
		else if (s->str[i] == '!'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,noise_gen(size,noise)/2);
			glEnd();
			glBegin(GL_POINTS);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,0);
			glEnd();
		}
		else if (s->str[i] == '.'){
			glBegin(GL_POINTS);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,0);
			glEnd();
		}
		else if (s->str[i] == ','){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2+noise_gen(size,noise)/4,-noise_gen(size,noise)/4);
			glEnd();
		}
		else if (s->str[i] == ':'){
			glBegin(GL_POINTS);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,noise_gen(size,noise));
			glEnd();
		}
		else if (s->str[i] == '-'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/2);
			glEnd();
		}
		else if (s->str[i] == '('){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,3*noise_gen(size,noise)/4);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,1*noise_gen(size,noise)/4);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
			glEnd();
		}
		else if (s->str[i] == ')'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,3*noise_gen(size,noise)/4);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,1*noise_gen(size,noise)/4);
				glVertex3d(0,noise_gen(size,noise)-0,0);
			glEnd();
		}
		else if (s->str[i] == '+'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/2);
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,noise_gen(size,noise));
			glEnd();
		}
		else if (s->str[i] == '_'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
			glEnd();
		}
		else if (s->str[i] == '0'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
				glVertex3d(0,noise_gen(size,noise)-0,0);
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
			glEnd();
		}
		else if (s->str[i] == '1'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,0);
			glEnd();
		}
		else if (s->str[i] == '2'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
			glEnd();
		}
		else if (s->str[i] == '3'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,noise_gen(size,noise)/2);
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
				glVertex3d(0,noise_gen(size,noise)-0,0);
			glEnd();
		}
		else if (s->str[i] == '4'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
			glEnd();
		}
		else if (s->str[i] == '5'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
				glVertex3d(0,noise_gen(size,noise)-0,0);
			glEnd();
		}
		else if (s->str[i] == '6'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/2);
			glEnd();
		}
		else if (s->str[i] == '7'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-0,0);
			glEnd();
		}
		else if (s->str[i] == '8'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
				glVertex3d(0,noise_gen(size,noise)-0,0);
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/2);
			glEnd();
		}
		else if (s->str[i] == '9'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/2);
			glEnd();
		}
		else if (s->str[i] == '/'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-0,0);
			glEnd();
		}
		else if (s->str[i] == '\\'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
			glEnd();
		}
		else if (s->str[i] == '<'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
			glEnd();
		}
		else if (s->str[i] == '>'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
			glEnd();
		}
		else if (s->str[i] == '='){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/3.);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/3);
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,2.*noise_gen(size,noise)/3.);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),2.*noise_gen(size,noise)/3.);
			glEnd();
		}else if (s->str[i] == '='){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/2);
			glEnd();
			
		}else if (s->str[i] == '^'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)/2);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/2,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)/2);
			glEnd();
			
		}else if (s->str[i] == '@'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,0);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise));
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/3,0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)/3,noise_gen(size,noise)*2./3.);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)*2./3.);
			glEnd();
			
		}else if (s->str[i] == '#'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)*1./4,0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)*1./4,noise_gen(size,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)*3./4,0);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise)*3./4,noise_gen(size,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)*1./4);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)*1./4);
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(0,noise_gen(size,noise)-0,noise_gen(size,noise)*3./4);
				glVertex3d(0,noise_gen(size,noise)-noise_gen(size,noise),noise_gen(size,noise)*3./4);
			glEnd();
			
		}
		else {
		
		}
		i++;
	}
	glPopMatrix();
}


