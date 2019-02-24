#define USE_REPLACEMENT_MANAGER 1

#include <stdio.h>

#if USE_REPLACEMENT_MANAGER
//load your memManager
	#undef malloc
	#define malloc myMalloc
	
	#undef free
	#define free myFree
	#include "replacementMalloc.h"
#else
	#include <stdlib.h>
#endif

int main(int argc, char* argv[]){


}
