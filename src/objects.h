#ifndef OBJECTS_H
#define OBJECTS_H

typedef struct Arrow{
	double x;
	double y;
	double z;

	double dx;
	double dy;
	double dz;

	//chained list
	struct Arrow * next;
	struct Arrow * prev;
	struct Arrow * next_update;

	double v;
	double dist;
	double alpha;
	double beta;
}Arrow;

typedef struct Mechant{
	double x;
	double y;
	double z;


	double phi;
	double theta;
	double rho;

	struct Mechant * next;

	double dist;

}Mechant;


#endif