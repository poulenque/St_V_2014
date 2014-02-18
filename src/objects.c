#include "objects.h"

void mechant_update_dummy(Mechant * mechant){
	mechant->x+=mechant->dx;
	mechant->y+=mechant->dy;
	mechant->z+=mechant->dz;

	mechant->phi	+=mechant->dphi;
	mechant->theta	+=mechant->dtheta;
	mechant->rho	+=mechant->drho;
}
