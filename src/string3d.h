#ifndef STRING3D_H
#define STRING3D_H


typedef struct String3d{
	char* str;
	// unsigned int vbo_buff_a;

	double noise;
	double size;
	double dist;
	double rho;
	double phi;
	double theta;

	double x;
	double y;
	double z;


} String3d;

String3d* new_string3d();
void string3d_setTxt(String3d* s,const char* str);
void string3d_draw(String3d* s);


#endif

