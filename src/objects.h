#ifndef OBJECTS_H
#define OBJECTS_H

typedef struct Arrow{
	double x;
	double y;
	double z;

	double dx;
	double dy;
	double dz;

	double phi;
	double theta;
	double rho;

	// int to_update;
	
}Arrow;

typedef struct Mechant{
	double x;
	double y;
	double z;


	double phi;
	double theta;
	double rho;

}Mechant;


#endif