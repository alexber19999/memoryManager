#ifndef heap_h
#define heap_h
#include <stddef.h>
void* replacementAlloc(size_t size);
void replacementFree(void* address);
#endif
