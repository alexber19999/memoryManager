#include "replacementMalloc.h"

void* myMalloc(size_t size){
	return replacementAlloc(size); // returns start address
}

void myFree(void* address){
	replacementFree(address);
}
