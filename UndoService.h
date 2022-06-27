#pragma once
#include "DynamicArray.h"
#include "OfferRepository.h"

typedef struct {
	DynamicArray* repos;
	int index;
	int nrOperations;
} UndoService;

/*
	Constructor for the Undo Service - UndoService structure
	Input: None
	Output: A pointer to the created UndoService structure or NULL if the structure couldn't be created
*/
UndoService* createUndoService();

/*
	Destructor for an UndoService structure
	Input: u - pointer to an UndoService structure
	Output: None
*/
void destroyUndoService(UndoService* u);

/*
	Undo operation
	Input: u - pointer to an UndoService structure
	Output: A pointer to an OfferRepo structure, representing the previous repo state
*/
OfferRepo* undo(UndoService* u);

/*
	Redo operation
	Input: u - pointer to an UndoService structure
	Output: A pointer to an OfferRepo structure, representing the next repo state
*/
OfferRepo* redo(UndoService* u);

/*
	Log an operation - inserting a new repo state
	Input: u - pointer to an UndoService structure
		   newR - pointer to the repo that will be recorded
	Output: None
*/
void logOp(UndoService* u, OfferRepo* newR);

// Tests
void undoTests();