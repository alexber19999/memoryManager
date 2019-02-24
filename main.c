#define USE_REPLACEMENT_MANAGER 0

#include <stdio.h>

#if USE_REPLACEMENT_MANAGER
//load your memManager
	#include "replacementMalloc.h"
	#undef malloc
	#define malloc myMalloc
	
	#undef free
	#define free myFree
#else
	#include <stdlib.h>
#endif

int main(int argc, char* argv[]){
	char* ptr1 = malloc(300);
}
