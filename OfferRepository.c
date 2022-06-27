#include "OfferRepository.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

OfferRepo* createRepo() {
	OfferRepo* r = malloc(sizeof(OfferRepo));
	if (r == NULL)
		return NULL;
	
	r->offers = createDynamicArray(0, destroyOffer);
	if (r->offers == NULL)
		return NULL;

	return r; 
}

void destroyRepo(OfferRepo* r) {
	if (r == NULL)
		return;

	destroyDynamicArray(r->offers);
	free(r);
}

int addOfferRepo(OfferRepo* r, Offer* o) {
	if (r == NULL || o == NULL)
		return 0;

	for (int i = 0; i < getLength(r->offers); i++) {
		if (checkEqual(o, getElem(r->offers, i))) {
			return 0;
		}
	}

	return addElem(r->offers, o);
}

int findOfferRepo(OfferRepo* r, Offer* o) {
	if (r == NULL || o == NULL)
		return -1; 
		
	for (int i = 0; i < getLength(r->offers); i++) {
		if (checkEqual(o, getElem(r->offers, i)))
			return i;
	}
	return -1;
}

int updateOfferRepo(OfferRepo* r, Offer* oldOffer, Offer* newOffer) {
	if (r == NULL || oldOffer == NULL || newOffer == NULL)
		return 0; 
	
	int i = findOfferRepo(r, oldOffer);
	if (i == -1)
		return 0;

	// Update the identifying fields inside newOffer to check if the updated one is not already an existing offer
	if (strcmp(newOffer->destination, "-") == 0) {
		free(newOffer->destination);
		newOffer->destination = malloc(sizeof(char) * (strlen(oldOffer->destination) + 1));
		if (newOffer->destination != NULL)
			strcpy(newOffer->destination, oldOffer->destination);
	}

	if (checkNullDate(newOffer->departureDate))
		copyDate(newOffer->departureDate, oldOffer->departureDate);

	int j = findOfferRepo(r, newOffer);
	if (j != -1 && j != i)
		return 0;

	return updateOffer(getElem(r->offers, i), newOffer);
}

int removeOfferRepo(OfferRepo* r, Offer* o) {
	if (r == NULL || o == NULL)
		return 0;

	int i = findOfferRepo(r, o);
	if (i == -1) {
		return 0;
	}
	
	Offer* oldOffer = getElem(r->offers, i);
	int res = removeElem(r->offers, oldOffer);
	destroyOffer(oldOffer);
	
	return res;
}

int getLengthRepo(OfferRepo* r) {
	if (r == NULL)
		return 0;
	return getLength(r->offers);
}

Offer* getOfferOnPos(OfferRepo* r, int index) {
	if (r == NULL)
		return NULL;

	return getElem(r->offers, index);
}

void sortRepoByCriteria(OfferRepo* r, SortingFunction sortingFunction) {
	if (r == NULL)
		return;

	for (int i = 0; i < getLength(r->offers); i++) {
		for (int j = i + 1; j < getLength(r->offers); j++) {
			Offer* o1 = getElem(r->offers, i);
			Offer* o2 = getElem(r->offers, j);

			if (!sortingFunction(o1, o2)) {
				swapElems(r->offers, i, j);
			}
		}
	}
}

int sortAscendingByPrice(Offer* o1, Offer* o2) {
	return(o1->price < o2->price);
}

int sortDescendingByPrice(Offer* o1, Offer* o2) {
	return(o1->price > o2->price);
}

void copyRepo(OfferRepo* destinationR, OfferRepo* sourceR) {
	if (destinationR == NULL || sourceR == NULL)
		return;

	for (int i = 0; i < getLength(sourceR->offers); i++) {
		Offer* destinationO = getElem(sourceR->offers, i);
		Offer* sourceO = createCopiedOffer(destinationO);
		addElem(destinationR->offers, sourceO);
	}
}

// ================================================================ //
void repoTests() {
	int res = 0;
	
	// createRepo()
	OfferRepo* r1 = createRepo();
	assert(r1 != NULL);

	// addOfferRepo() 
	res = addOfferRepo(r1, createOffer("seaside", "Romania", createDate(12, 12, 2024), 45600.99));
	assert(res == 1);

	Offer* duplicatedOffer = createOffer("seaside", "Romania", createDate(12, 12, 2024), 45600.99);
	res = addOfferRepo(r1, duplicatedOffer);
	destroyOffer(duplicatedOffer);
	assert(res == 0);

	res = addOfferRepo(r1, createOffer("mountain", "India", createDate(10, 1, 2025), 75600.01));
	assert(res == 1);

	// updateOfferRepo()
	Offer* newOffer = createOffer("seaside", "Bulgaria", createDate(12, 12, 2024), 45600.99);
	Offer* oldOffer = getOfferOnPos(r1, 0);
	res = updateOfferRepo(r1, oldOffer, newOffer);
	destroyOffer(newOffer);
	assert(res == 1);

	Offer* updatedOffer = getOfferOnPos(r1, 0);
	assert(strcmp(updatedOffer->destination, "Bulgaria") == 0);

	newOffer = createOffer("seaside", "India", createDate(10, 1, 2025), 45600.99);
	oldOffer = getOfferOnPos(r1, 0);
	res = updateOfferRepo(r1, oldOffer, newOffer);
	assert(res == 0);
	destroyOffer(newOffer);

	Offer* nonExistingOffer = createOffer("seaside", "Romania", createDate(12, 12, 2024), 45600.99);
	newOffer = createOffer("seaside", "India", createDate(10, 1, 2025), 45600.99);
	res = updateOfferRepo(r1, nonExistingOffer, newOffer);
	assert(res == 0);
	destroyOffer(newOffer);
	destroyOffer(nonExistingOffer);
	
	// removeOfferRepo()
	Offer* offerToDelete = createOffer("seaside", "Bulgaria", createDate(12, 12, 2024), 45600.99);
	res = removeOfferRepo(r1, offerToDelete);
	assert(res == 1 && getLengthRepo(r1) == 1 && findOfferRepo(r1, offerToDelete) == -1);
	res = removeOfferRepo(r1, offerToDelete);
	assert(res == 0);
	destroyOffer(offerToDelete);

	// findOfferRepo() && getOfferOnPos()
	Offer* o = getOfferOnPos(r1, 0);
	int i = findOfferRepo(r1, o);
	assert(i == 0);

	// getLengthRepo()
	assert(getLengthRepo(r1) == 1);
	
	// sortRepoByCriteria() & sortAscendingByPrice()
	addOfferRepo(r1, createOffer("seaside", "Romania", createDate(12, 12, 2024), 35600.99));
	o = getOfferOnPos(r1, 1);
	sortRepoByCriteria(r1, sortAscendingByPrice);
	i = findOfferRepo(r1, o);
	assert(i == 0);

	// sortRepoByPrice() & sortDescendingByPrice()
	sortRepoByCriteria(r1, sortDescendingByPrice);
	i = findOfferRepo(r1, o);
	assert(i == 1);

	// copyRepo()
	OfferRepo* r2 = createRepo();
	copyRepo(r2, r1);
	assert(getLengthRepo(r2) == 2);
	destroyRepo(r1);
	assert(getLengthRepo(r2) == 2);

	// destroyRepo()
	destroyRepo(r2);
}