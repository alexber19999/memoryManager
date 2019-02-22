#include "heap.h"

typedef enum BlockType {
	HOLE = 0,
	ALLOC
} BlockType;

typedef struct Node {
	BloctType type;
	size_t size;
	char* startAddress;
	struct Node* prev;
	struct Node* next;
} Node;

#define myHeap 1000
char* heap = NULL;
Node* head = NULL;

void initHeap(){
	heap = (char*) malloc(myHeap);
	head = NULL;	
}

void* replacementAlloc(size_t size){
	if(!heap){
		initHeap();
	}

	if(!insert(head, size)){
		return NULL;
	}


}


void replacementFree(void* address){

}

bool spaceFound(size_t size, Node* head){

	size = head -> size;
	Node* nextNode = head;

	while(nextNode){

		if(size >= nextNode -> size){
			return true;
		}

	nextNode = nextNode -> next;

	}

	return false;
}

bool insert(Node* head, size_t size){
	if(!spaceFound(size, head)){
		return false;
	}



	//insert 
}
