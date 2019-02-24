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

Node* makeNewNode(size_t size, char* startAddress, BlockType type){
	Node* node = (Node*) malloc(sizeof(Node));
	node -> size = size;
	node -> startAddress = (char*) malloc(strlen(label) + 1);
	strcpy(node -> startAddress, startAddress);
	node -> type = type;
	return node;
}

void initHeap(){
	heap = (char*) malloc(myHeap);
	head = makeNewNode(myHeap, heap, HOLE);
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


void insertInBetweenTwoNodes(Node* newNode, Node* previous, Node* next){
	newNode -> next = next;
	newNode -> prev = previous;
	previous -> next = newNode;
	next -> size -= newNode -> size;
	next -> startAddress += newNode -> size;
	next -> prev = newNode;
}


Node* insert(size_t size){
	Node* space = spaceFound(size, head);
	if(!space){
		return NULL;
	}

	if(space -> size == size){
		space -> type = ALLOC;
		return space;
	}

	if((space -> size == head -> size) && (head -> type == HOLE)){
		//add stuff for the first time to the heap
		Node* newNode = makeNewNode(size, heap, ALLOC);
		insertInBetweenTwoNodes(newNode, head, space);
		
	} else {
		//add stuff in between 2 nodes
		Node* newNode = makeNewNode(size, space -> startAddress, ALLOC);
		insertInBetweenTwoNodes(newNode, space -> prev, space);
	}

	/*
		Check if there is any space in the heap, 
		if there is no space, return null, 
		if there is, insert into the heap, subtract total amt of space from the heap
		insert:
			if the heap is empty, 
				insert into the front of the heap
			else:
				if the spaceFound is equal to the size, then change the spaceFound
				-> type to ALLOC
				insert in between 2 nodes, the free space and allocated space

			

		insert into the front of the heap:
			make a new node
			new node -> size = size
			new node -> next is free space
			new node -> type is ALLOC
			new node -> prev is head
			new node -> startAddress is head -> startAddress
			head -> next is new node
			free space -> prev is new node
			free space start address is free space -> startAddress + new node -> size
			free space -> size is free space -> size - new node -> size

		insert in between 2 nodes:
			make a new node
			new node -> size = size
			new node -> start address = spaceFound -> start address
			new node -> type = ALLOC
			spaceFound -> startAdress = new node -> start address + new node -> size
			new node -> prev = spaceFound -> prev
			new node -> next = spaceFound
			spaceFound -> size = spaceFound -> size - new node -> size
			new node -> prev -> next = new node
	*/
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




























