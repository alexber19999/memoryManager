#ifndef replacementMalloc_h
#define replacementMalloc_h

#include <stddef.h>
#include "heap.h"

void* myMalloc(size_t size);
void myFree(void* address);

#endif


