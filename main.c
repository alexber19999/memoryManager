#define USE_REPLACEMENT_MANAGER 1

#include <stdio.h>

#if USE_REPLACEMENT_MANAGER
//load your memManager
	#include "replacementMalloc.h"
	#undef malloc
//	#define malloc myMalloc
	
	#undef free
	#define free myFree
#else
	#include <stdlib.h>
#endif

int main(int argc, char* argv[]){
	char* ptr1 = myMalloc(300);
	char* ptr2 = myMalloc(400);
	char* ptr3 = myMalloc(300);
	char* ptr4 = myMalloc(100);

	free(ptr1);
}
