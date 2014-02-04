#include "string3d.h"
#include "constants.h"
#include <GL/glew.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "random.h"

// #define  letterA_SIZE 3*8
// float letterA[letterA_SIZE] = {
// 	0,1,0,
// 	0,1,1,

// 	0,1,1,
// 	0,0,1,

// 	0,0,1,
// 	0,0,0,

// 	0,1,.5,
// 	0,0,.5
// };

String3d* new_string3d(){


	String3d* s=malloc(sizeof(String3d));

	// glGenBuffers (1, &s->vbo_buff_a);
	// glBindBuffer (GL_ARRAY_BUFFER, s->vbo_buff_a);
	// glBufferData (GL_ARRAY_BUFFER, letterA_SIZE * sizeof (float), letterA, GL_STATIC_DRAW);
	// glBindBuffer (GL_ARRAY_BUFFER,0);

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


void string3d_draw(String3d* s){

	double size = s->size;	
	double size_half=size*.5;
	double dist= s->dist;
	double noise=size*s->noise;

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

		// glPushMatrix();
		// glScaled(size,random(size     ,noise),random(size     ,noise));
		// 	glEnableClientState (GL_VERTEX_ARRAY);
		// 	glBindBuffer (GL_ARRAY_BUFFER, s->vbo_buff_a);

		// 	glVertexPointer ( 3, GL_FLOAT, GL_FALSE, 0);

		// 	glDrawArrays (GL_LINES, 0, letterA_SIZE);

		// 	glBindBuffer (GL_ARRAY_BUFFER, 0);
		// 	glDisableClientState (GL_VERTEX_ARRAY);
		// glPopMatrix();
			
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
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise)   );
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise)   ,random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise)   ,random(0        ,noise)   );
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise)   ,random(size_half,noise));
			glEnd();
		}
		else if (s->str[i] == 'b' ){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise)     ,random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise)     ,random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size_half,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size_half,noise),random(size_half,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise)   ,random(size_half,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise)   ,random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
			glEnd();
		
		}
		else if (s->str[i] == 'c' ){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
			glEnd();
		}
		else if (s->str[i] == 'd' ){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size_half,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
			glEnd();
		}
		else if (s->str[i] == 'e' ){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size_half,noise));
			glEnd();
		}
		else if (s->str[i] == 'f' ){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise)   ,random(size_half,noise));
			glEnd();
		}
		else if (s->str[i] == 'g'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(size_half,noise),random(size_half,noise));
			glEnd();
		}
		else if (s->str[i] == 'h'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size_half,noise));
			glEnd();
		}
		else if (s->str[i] == 'i' ){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size_half,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size_half,noise),random(size     ,noise));
			glEnd();
		}
		else if (s->str[i] == 'j' ){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size_half,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size_half,noise),random(size     ,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
			glEnd();
		}
		else if (s->str[i] == 'k'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
			glEnd();
		}
		else if (s->str[i] == 'l' ){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
			glEnd();
		}
		else if (s->str[i] == 'm'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size_half,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size_half,noise),random(size_half,noise));
			glEnd();
		}
		else if (s->str[i] == 'n'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size_half,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size_half,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
			glEnd();
		}
		else if (s->str[i] == 'o'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
			glEnd();
		}
		else if (s->str[i] == 'p'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size_half,noise));
			glEnd();
		}
		else if (s->str[i] == 'q'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size_half,noise));
			glEnd();
		}
		else if (s->str[i] == 'r'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size_half,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size_half,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(size_half,noise),random(0        ,noise));
			glEnd();
		}
		else if (s->str[i] == 's'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise)/4);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),3.*size/4.);
			glEnd();
		}
		else if (s->str[i] == 't'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size_half,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size_half,noise),random(0        ,noise));
			glEnd();
		}
		else if (s->str[i] == 'u'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
			glEnd();
		}
		else if (s->str[i] == 'v'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
			glEnd();
		}
		else if (s->str[i] == 'w'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size_half,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size_half,noise),random(size_half,noise));
			glEnd();
		}
		else if (s->str[i] == 'x'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
			glEnd();
		}
		else if (s->str[i] == 'y'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size_half,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
			glEnd();
		}
		else if (s->str[i] == 'z'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
			glEnd();
		}
		else if (s->str[i] == '?'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(size_half,noise),random(size_half,noise));
			glEnd();
			glBegin(GL_POINTS);
				glVertex3d(random(0        ,noise),random(size_half,noise),random(0        ,noise));
			glEnd();
		}
		else if (s->str[i] == '!'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size_half,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size_half,noise),random(size_half,noise));
			glEnd();
			glBegin(GL_POINTS);
				glVertex3d(random(0        ,noise),random(size_half,noise),random(0        ,noise));
			glEnd();
		}
		else if (s->str[i] == '.'){
			glBegin(GL_POINTS);
				glVertex3d(random(0        ,noise),random(size_half,noise),random(0        ,noise));
			glEnd();
		}
		else if (s->str[i] == ','){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size_half,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size_half,noise)+size/4,-size/4);
			glEnd();
		}
		else if (s->str[i] == ':'){
			glBegin(GL_POINTS);
				glVertex3d(random(0        ,noise),random(size_half,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size_half,noise),random(size     ,noise));
			glEnd();
		}
		else if (s->str[i] == '-'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size_half,noise));
			glEnd();
		}
		else if (s->str[i] == '('){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size_half,noise),3*size/4);
				glVertex3d(random(0        ,noise),random(size_half,noise),1*size/4);
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
			glEnd();
		}
		else if (s->str[i] == ')'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size_half,noise),3*size/4);
				glVertex3d(random(0        ,noise),random(size_half,noise),1*size/4);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
			glEnd();
		}
		else if (s->str[i] == '+'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size_half,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size_half,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size_half,noise),random(size     ,noise));
			glEnd();
		}
		else if (s->str[i] == '_'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
			glEnd();
		}
		else if (s->str[i] == '0'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
			glEnd();
		}
		else if (s->str[i] == '1'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(size_half,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size_half,noise),random(0        ,noise));
			glEnd();
		}
		else if (s->str[i] == '2'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
			glEnd();
		}
		else if (s->str[i] == '3'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size_half,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size_half,noise),random(size_half,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
			glEnd();
		}
		else if (s->str[i] == '4'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
			glEnd();
		}
		else if (s->str[i] == '5'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
			glEnd();
		}
		else if (s->str[i] == '6'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size_half,noise));
			glEnd();
		}
		else if (s->str[i] == '7'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
			glEnd();
		}
		else if (s->str[i] == '8'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size_half,noise));
			glEnd();
		}
		else if (s->str[i] == '9'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size_half,noise));
			glEnd();
		}
		else if (s->str[i] == '/'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
			glEnd();
		}
		else if (s->str[i] == '\\'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
			glEnd();
		}
		else if (s->str[i] == '<'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
			glEnd();
		}
		else if (s->str[i] == '>'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
			glEnd();
		}
		else if (s->str[i] == '='){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise)/3.);
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise)/3);
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),2.*size/3.);
				glVertex3d(random(0        ,noise),random(0        ,noise),2.*size/3.);
			glEnd();
		}else if (s->str[i] == '='){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(size_half,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size_half,noise));
			glEnd();
			
		}else if (s->str[i] == '^'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size_half,noise));
				glVertex3d(random(0        ,noise),random(size_half,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size_half,noise));
			glEnd();
			
		}else if (s->str[i] == '@'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise),random(0        ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise)/3,random(0        ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise)/3,random(size     ,noise)*2./3.);
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise)*2./3.);
			glEnd();
			
		}else if (s->str[i] == '#'){
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(0        ,noise)*1./4,random(0        ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise)*1./4,random(size     ,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(0        ,noise)*3./4,random(0        ,noise));
				glVertex3d(random(0        ,noise),random(0        ,noise)*3./4,random(size     ,noise));
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise)*1./4);
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise)*1./4);
			glEnd();
			glBegin(GL_LINE_STRIP);
				glVertex3d(random(0        ,noise),random(size     ,noise),random(size     ,noise)*3./4);
				glVertex3d(random(0        ,noise),random(0        ,noise),random(size     ,noise)*3./4);
			glEnd();
			
		}
		else {
		
		}
		i++;
	}
	glPopMatrix();
}


