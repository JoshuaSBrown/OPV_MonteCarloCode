#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//#include "../../../MEM/mem.h"
#include "matrix.h"

int main() {
	
	//mem_init();
	printf("Testing: functions with mtx as null \n");
	matrix mtx = NULL; 
	int rv;
	int row=4;
	int col=3;
	int val = -999; 

	printf("Testing: printMatrix with mtx as null \n");
	rv = printMatrix(mtx);
	assert(rv==-1);
	printf("Testing: deleteMatrix with mtx as null \n");
	rv = deleteMatrix(mtx);
	assert(rv==-1);
	printf("Testing: setAll with mtx as null \n");
	rv = setAll(mtx, val);
	assert(rv==-1);
	printf("Testing: printRandomEnergyFilesijk with mtx as null \n");
	rv= printRandomEnergyFilesijk(mtx); 
	assert(rv==-1);
	printf("Testing: getE with mtx as null \n");
	rv = getE(mtx,row, col);
	assert(rv==-1);
	printf("Testing: getRows with mtx as null \n");	
	rv = getRows(mtx);
	assert(rv==-1);
	printf("Testing: getCols with mtx as null \n");
	rv = getCols(mtx);
	assert(rv==-1);
	printf("Testing: setE with mtx as null \n");	
	rv = setE(mtx,row, col, val);
	assert(rv==-1);
	printf("Testing: deleteMatrix with mtx as null \n");
	rv=deleteMatrix(mtx);
	assert(rv==-1);

	printf("Testing: functions with functional mtx\n");
	matrix mtxrv; 
	mtx = newMatrix(row, col);

	printf("Testing: newMatrix returning null\n");
	mtxrv=newMatrix(-1,1);
	assert(mtxrv==NULL);
	mtxrv=newMatrix(1,-1);
	assert(mtxrv==NULL);

	printf("************\n\n");
	printf("Testing: newMatrix, expecting matrix of 0's\n");
	printf("Testing: printMatrix with functional mtx\n");
	rv = printMatrix(mtx);
	assert(rv==0);

	printf("Testing: setE with functional mtx\n");
	rv= setE(mtx, 2, 3, 343.1);
	assert(rv==0);
	rv= setE(mtx,3,2,902.8);
	assert(rv==0);
	printf("************\n\n");
	printMatrix(mtx);

	printf("Testing: setE returns null properly\n");
	rv = setE(mtx,-1, col, val);
	assert(rv==-2);
	rv = setE(mtx,15, col, val);
	assert(rv==-2);
	rv = setE(mtx,row, -1, val);
	assert(rv==-2);
	rv = setE(mtx,row, 15, val);
	assert(rv==-2);

	printf("Testing: getE with functional mtx\n");
	double drv; 
	drv= getE(mtx, 2, 3);
	assert(drv==343.1);
	drv= getE(mtx,3,2);
	//printf("%g\n",drv);
	assert(drv==902.8);

	printf("Testing: getE returns null properly\n");
	drv = getE(mtx,-1, col);
	assert(drv==-2);
	drv = getE(mtx,15, col);
	assert(drv==-2);
	drv = getE(mtx, row, -1);
	assert(drv==-2);
	drv = getE(mtx,row, 15);
	assert(drv==-2);

	printf("Testing: deleteMatrix\n");
	rv=deleteMatrix(mtx);
	assert(rv==0);

	matrix mtx3 = newMatrixSet(row,15,15.7);
	printf("Testing if printRandomEnergyFilesijk doesn't work with a 15-column matrices\n");
	rv= printRandomEnergyFilesijk(mtx3); 
	assert(rv==-1);
	printf("Testing: getRows\n"); 
	rv= getRows(mtx3); 
	assert(rv==4);
	printf("Testing: getCols\n"); 
	rv=getCols(mtx3); 
	assert(rv==15);
	
	printf("Testing: resizeRow\n");
	matrix mtx4 = NULL;
	rv = resizeRow(&mtx4,3);
	assert(rv==-1);
	mtx4 = newMatrix(5,3);
	printMatrix(mtx4);
	rv = resizeRow(&mtx4,4);
	assert(rv==0);
	rv = getRows(mtx4);
	printf("rows %d\n",rv);
	assert(rv==4);
	rv = resizeRow(&mtx4,0);
	assert(rv==-1);
	setE(mtx4,1,1,34);
	setE(mtx4,2,1,31);
	printMatrix(mtx4);
	rv = resizeRow(&mtx4,6);
	assert(rv==0);
	setE(mtx4,6,2,-12.3);
	printMatrix(mtx4);

	deleteMatrix(mtx3);
	deleteMatrix(mtx4);

	//atexit(mem_term);
	/*
	printf("************\n\n");

	printf("Testing: newMatrixSet, expecting matrix of 5.5's\n");
	matrix mtx2 = newMatrixSet(row,col,5.5);
	printMatrix(mtx2);
	printf("Testing: newMatrixSet returns null properly\n");
	mtxrv=newMatrixSet(-2,0,val);
	assert(mtxrv==NULL);
	mtxrv=newMatrixSet(0,-2,val);
	assert(mtxrv==NULL);

	printf("\n************\n\n");
	printf("Testing the setAll command\n");
	printf("Changing default to 32.1\n");
	rv=setAll(mtx2, 32.1);
	assert(rv==0); 
	printMatrix(mtx2);
	printf("Testing if printRandomEnergyFilesijk works with a 3-column matrix\n");
	rv= printRandomEnergyFilesijk(mtx); 
	assert(rv==0);
	//printf("Changing matrix to 15 columns of 15.7 \n");
*/
	return 0;
}
