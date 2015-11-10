#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

#include "matrix.h"

int main(){


	matrix mtx = newMatrix(20000000,12);

	assert(mtx!=NULL);
	sleep(3);
	deleteMatrix(&mtx);
	return 0;

}
