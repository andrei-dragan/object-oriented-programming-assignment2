#include "DynamicArray.h"
#include "Offer.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

DynamicArray* createDynamicArray(int capacity, destroyFunction destroy) {
	DynamicArray* v = (DynamicArray*)malloc(sizeof(DynamicArray));
	if (v == NULL)
		return NULL;

	v->cap = capacity;
	v->size = 0;
	v->destroy = destroy;

	v->elems = (TElem*)malloc(sizeof(TElem) * v->cap);
	if (v->elems == NULL) {
		free(v);
		return NULL;
	}

	return v;
}

void destroyDynamicArray(DynamicArray* v) {
	if (v == NULL)
		return;
	if (v->elems == NULL) {
		free(v);
		return;
	}

	for (int i = 0; i < v->size; i++) {
		v->destroy(v->elems[i]);
	}
	free(v->elems);
	free(v);
}

void resize(DynamicArray* v) {
	if (v == NULL)
		return; 

	if (v->cap != 0)
		v->cap *= 2;
	else
		v->cap = 1;

	TElem* newElems = (TElem*)malloc(sizeof(TElem) * v->cap);

	if (newElems == NULL) {
		v->cap /= 2;
		return;
	}

	for (int i = 0; i < v->size; i++)
		newElems[i] = v->elems[i];
	
	free(v->elems);
	v->elems = newElems;
}

int addElem(DynamicArray* v, TElem elem) {
	if (v == NULL)
		return 0;

	int old_cap = v->cap;
	if (v->size == v->cap) {
		resize(v);
		if (old_cap == v->cap)
			return 0;
	}
	v->elems[v->size++] = elem;
	return 1;
}

int removeElem(DynamicArray* v, TElem elem) {
	if (v == NULL)
		return 0;

	for (int i = 0; i < v->size; i++) {
		if (v->elems[i] == elem) {
			v->elems[i] = v->elems[v->size - 1];
			v->size--; 
			return 1;
		}
	}

	return 0;
}

TElem getElem(DynamicArray* v, int index) {
	if (v == NULL)
		return NULL;

	if (index < 0 || index >= v->size)
		return NULL;

	return v->elems[index];
}

int getLength(DynamicArray* v) {
	if (v == NULL)
		return 0;
	return v->size;
}

void swapElems(DynamicArray* v, int i, int j) {
	if (i < 0 || i >= getLength(v) || j < 0 || j >= getLength(v))
		return;
	
	TElem aux = v->elems[i];
	v->elems[i] = v->elems[j];
	v->elems[j] = aux;
}

// ================================================================ //
void dynamicArrayTests() {
	// createDynamicArray()
	DynamicArray* v = createDynamicArray(1, destroyOffer);
	assert(v != NULL);
	assert(v->size == 0 && v->cap == 1);
	
	// addElem()
	Offer* o = createOffer("seaside", "Romania", createDate(12, 12, 2024), 45600.99);
	int res = addElem(v, o);
	assert(res == 1 && getLength(v) == 1);

	// removeElem()
	res = removeElem(v, o);
	assert(res == 1 && getLength(v) == 0);

	Offer* anotherO = createOffer("seaside", "Bulgaria", createDate(12, 12, 2024), 45600.99);
	res = removeElem(v, anotherO);
	assert(res == 0);

	// resize()
	addElem(v, o);
	addElem(v, anotherO);
	assert(v->cap == 2);

	// getElem()
	Offer* interO = getElem(v, 1);
	assert(checkEqual(interO, anotherO));

	// getLength()
	assert(getLength(v) == 2);

	// swapElems()
	swapElems(v, 0, 1);
	interO = getElem(v, 0);
	assert(checkEqual(interO, anotherO));
	interO = getElem(v, 1);
	assert(checkEqual(interO, o));

	// destroyDynamicArray()
	destroyDynamicArray(v);
}