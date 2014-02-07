#include "random.h"

#include <stdlib.h>
#include <limits.h>
#include <time.h>

// const double invert_RAND_MAX=1./RAND_MAX;
const double invert_RAND_MAX=.5/INT_MAX;


static unsigned int x;
void random_init(){
	srand((unsigned)time(NULL));
	x=(unsigned)time(NULL);
}

double random_simple(){
	x = 1103515245 * x + 12345;
	return x*invert_RAND_MAX;
	// return rand()*invert_RAND_MAX;
}

double random(double around,double noise){
	// return around*(1+noise*rand()/RAND_MAX-noise/2);
	return around+noise*((double)random_simple()-.5);
}







