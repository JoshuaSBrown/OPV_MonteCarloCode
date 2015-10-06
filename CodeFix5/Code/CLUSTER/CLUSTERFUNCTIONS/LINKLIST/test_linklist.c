#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "linklist.h"

int main(){

	printf("Starting\n");
	printf("Testing:newLinkList\n");
	linklist LL = newLinkList(-1);
	assert(LL==NULL);
	printf("1 - complete\n");
	LL = newLinkList(0);
	assert(LL!=NULL);
	printf("2 - complete\n");
	printLL(LL);

	int rv;
	printf("Testing:addLLNode\n");
	rv = addLLNode(NULL,1);
	assert(rv==-1);
	rv = addLLNode(LL, 0);
	assert(rv==-1);
	rv = addLLNode(LL, -1);
	assert(rv==-1);
	rv = addLLNode(LL, 34);
	assert(rv==0);
	printLL(LL);
	rv = addLLNode(LL, 34);
	assert(rv==-1);
	rv = addLLNode(LL,54);
	assert(rv==0);
	printLL(LL);

	printf("Testing:removeLLNode\n");
	rv = removeLLNode(NULL, 1);
	assert(rv==-1);
	rv = removeLLNode(LL, 34);
	assert(rv==0);
	printLL(LL);
	rv = removeLLNode(LL,0);
	assert(rv==0);
	printLL(LL);

	printf("Testing:deleteLL\n");
	rv = deleteLL(LL);
	assert(rv==0);
	printf("Finished");

	return 0;
}
