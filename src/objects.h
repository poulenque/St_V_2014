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

	double dx;
	double dy;
	double dz;

	double phi;
	double theta;
	double rho;

	struct Mechant * next;
	struct Mechant * prev;

	void (*update)(struct Mechant * mechant);

	double dist;

}Mechant;

typedef struct Particle{
	double x;
	double y;
	double z;

	double dx;
	double dy;
	double dz;

	struct Particle* next;
	struct Particle* next_update;
}Particle;



#endif