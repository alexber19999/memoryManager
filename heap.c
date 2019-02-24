#include "heap.h"

typedef enum BlockType {
	HOLE = 0,
	ALLOC
} BlockType;

typedef struct Node {
	BloctType type;
	size_t size;
	char* startAddress;
	struct Node* prev = NULL;
	struct Node* next = NULL;
} Node;

#define myHeap 1000
char* heap = NULL;
Node* head = NULL;

void initHeap(){
	heap = (char*) malloc(myHeap);
	head = (Node*) malloc(heap);
	head -> type = HOLE;
	head -> startAddress = heap;
}

Node* spaceFound(size_t size){

	Node* nextNode = head;

	while(nextNode){

		if(size >= nextNode -> size){
			return nextNode;
		}

		nextNode = nextNode -> next;

	}

	return NULL;
}

Node* insert(size_t size){
	Node* space = spaceFound(size, head);
	if(!space){
		return NULL;
	}

	if((head -> size = size) && (head -> type == HOLE)){
		//add stuff for the first time to the heap
		Node* newNode = (Node*) malloc(size);
		
	} else {
		//add stuff in between 2 nodes
	}
}


void* replacementAlloc(size_t size){
	if(!heap){
		initHeap();
	}

	Node* newNode = insert(head, size);

	if(!newNode){
		return NULL;
	}

	return newNode -> startAddress;


}

void replacementFree(void* address){

}




























