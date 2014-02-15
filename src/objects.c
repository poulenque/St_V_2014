#include "objects.h"

void mechant_update_dummy(Mechant * mechant){
	mechant->x+=mechant->dx;
	mechant->y+=mechant->dy;
	mechant->z+=mechant->dz;
}
