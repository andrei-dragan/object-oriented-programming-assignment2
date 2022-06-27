#pragma once

typedef void* TElem;
typedef void (*destroyFunction)(void*);

typedef struct {
	TElem* elems;
	int cap, size;
	destroyFunction destroy;
} DynamicArray;

/*
	Constructor for the DynamicArray structure
	Input: capacity - integer representing the initial capacity of the DynamicArray
		   destroy - destroyFunction representing the function te be called to destroy the elements inside the dynamic array
	Output: A pointer to the created DynamicArray structure or NULL if the structure couldn't be created
*/
DynamicArray* createDynamicArray(int capacity, destroyFunction destroy);

/*
	Destructor for an DynamicArray structure
	Input: v - pointer to a DynamicArray structure
	Output: None
*/
void destroyDynamicArray(DynamicArray* v);

/*
	Adds an element to the dynamic array
	Input: v - pointer to a DynamicArray structure
		   elem - TEleme to be added to the dynamic array
	Output: 1 if the operation was successful, 0 otherwise
*/
int addElem(DynamicArray* v, TElem elem);

/*
	Removes an element from the dynamic array
	Input: v - pointer to a DynamicArray structure
		   elem - TElem to be added to the dynamic array
	Output: 1 if the operation was successful, 0 otherwise
*/
int removeElem(DynamicArray* v, TElem elem);

/*
	Get an element from the dynamic array based on the index
	Input: v - pointer to a DynamicArray structure
		   index - integer representing the index of the element inside the dynamic array
	Output: TElem or NULL if the TElem can't be retrieved
*/
TElem getElem(DynamicArray* v, int index);

/*
	Get the length of the dynamic array
	Input: v - pointer to a DynamicArray structure
	Output: integer representing the length of the DynamicArray
*/
int getLength(DynamicArray* v);

/*
	Swap the elements from positions i and j
	Input: v - pointer to a DynamicArray structure
		   i - integer representing an index inside the array
		   j - integer representing an index inside the array
	Output: None
*/
void swapElems(DynamicArray* v, int i, int j);

// Tests 
void dynamicArrayTests();