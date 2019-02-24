#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "heap.h"



typedef enum BlockType {
	HOLE = 0,
	ALLOC
} BlockType;

typedef struct Node {
	BlockType type;
	size_t size;
	char* startAddress;
	struct Node* prev;
	struct Node* next;
} Node;

#define myHeap 1000
char* heap = NULL;
Node* head = NULL;

Node* makeNewNode(size_t size, char* startAddress, BlockType type){
	Node* node = (Node*) malloc(sizeof(Node));
	node -> size = size;
	node -> startAddress = (char*) malloc(strlen(startAddress) + 1);
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
		if((size <= nextNode -> size) && (nextNode -> type == HOLE)){
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

void reInitHead(Node* node){
	head -> next = node;
	head -> size = 0;
	head -> prev = NULL;
	head -> startAddress = heap;
}
Node* insert(size_t size){
	Node* space = spaceFound(size);
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
		Node* newSpace = makeNewNode(head -> size, newNode -> startAddress + size, HOLE);

		insertInBetweenTwoNodes(newNode, head, newSpace);
		reInitHead(newNode);
		newSpace -> next = NULL;
		
	} else {
		//add stuff in between 2 nodes
		Node* newNode = makeNewNode(size, space -> startAddress, ALLOC);
		insertInBetweenTwoNodes(newNode, space -> prev, space);
		head -> startAddress = heap;
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
void printNodeList(){
	Node* node = head;
	while(node){
		printf("%zu\n", node -> size);
		printf("%d\n", node -> type);
		printf("%p\n", node -> startAddress);
		printf("\n\n");
		node = node -> next;
	}
}
void* replacementAlloc(size_t size){
	if(!heap){
		initHeap();
	}

	Node* newNode = insert(size);

	if(!newNode){
		return NULL;
	}
	printNodeList();

	return newNode -> startAddress;


}
Node* findNode(void* address){
	Node* node = head;
	int notFound = 1;
	while(notFound && node){
		if(node -> startAddress == address){
			notFound = 0;
		} 
		else {
			node = node -> next;
		}
	}
	return node;
}


void mergeNodes(Node* nodeLeft, Node* nodeRight){
	nodeLeft -> size += nodeRight -> size;
	nodeRight -> next -> prev = nodeLeft;
	nodeLeft -> next = nodeRight -> next;
	free(nodeRight);
}


void replacementFree(void* address){
	printf("HERE\n");
	Node* node = findNode(address);
	if(node){
		printf("INSIDE\n");
		if(node -> next){
			if(node -> next -> type == HOLE){
				mergeNodes(node, node -> next);
			}
		}
		if(node -> prev != head){
			if(node -> prev -> type == HOLE){
				mergeNodes(node -> prev, node);
			}
		}
		if(node){
			free(node);
		}
	} else {
		printf("INSIDE ELSE\n");
		exit(EXIT_FAILURE);
	}
}




























