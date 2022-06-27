#pragma once
#include "Offer.h"
#include "DynamicArray.h"

typedef struct {
	DynamicArray* offers;
} OfferRepo;

typedef int (*SortingFunction)(Offer*, Offer*);

/*
	Constructor for the Offer Repository - OfferRepo structure
	Input: None
	Output: A pointer to the created OfferRepo structure or NULL if the structure couldn't be created
*/
OfferRepo* createRepo();

/*
	Destructor for an OfferRepo structure
	Input: o - pointer to an OfferRepo structure
	Output: None
*/
void destroyRepo(OfferRepo* r);

/*
	Adds an Offer to the OfferRepo
	Input: r - pointer to the OfferRepo
		   o - pointer to the Offer to be added
	Output: 1 if the operation was successful, 0 otherwise
*/
int addOfferRepo(OfferRepo* r, Offer* o);

/*
	Updates an Offer from the OfferRepo based on the content of another given Offer
	Input: r - pointer to the OfferRepo
		   oldOffer - pointer to the Offer to be updated
		   newOffer - pointer to the Offer from where the content will be copied
	Output: 1 if the operation was successful, 0 otherwise
*/
int updateOfferRepo(OfferRepo* r, Offer* oldOffer, Offer* newOffer);

/*
	Removes an Offer from the OfferRepo 
	Input: r - pointer to the OfferRepo
		   o - pointer to the Offer to be removed
	Output: 1 if the operation was successful, 0 otherwise
*/
int removeOfferRepo(OfferRepo* r, Offer* o);

/*
	Finds an Offer inside the OfferRepo 
	Input: r - pointer to the OfferRepo
		   o - pointer to the Offer to be found
	Output: integer representing the index where the Offer is found inside the dyanmic array of the OfferRepo, -1 otherwise
*/
int findOfferRepo(OfferRepo* r, Offer* o);

/*
	Get the length of the dyanmic array of the OfferRepo
	Input: r - pointer to the OfferRepo
	Output: integer representing the length of the dynamic array of the OfferRepo
*/
int getLengthRepo(OfferRepo* r);

/*
	Get an Offer based on an index, describing the position of the Offer inside the dynamic array of the OfferRepo
	Input: r - pointer to the OfferRepo
		   index - integer representing the position of the Offer inside the dynamic array
	Output: pointer to an Offer, or NULL if the Offer couldn't be retrieved
*/
Offer* getOfferOnPos(OfferRepo* r, int index);

/*
	Sort the Offers inside the OfferRepo based on a given function
	Input: r - pointer to the OfferRepo
		   sortingFunction - pointer to the function that will be considered for sorting
	Output: None
*/
void sortRepoByCriteria(OfferRepo* r, SortingFunction sortingFunction);

/*
	Check if a pair of Offers is in ascending order by the price
	Input: o1 - pointer to the first Offer from the pair
		   o2 - pointer to the second Offer from the pair
	Output: 1 if the order is respected, 0 otherwise
*/
int sortAscendingByPrice(Offer* o1, Offer* o2);

/*
	Check if a pair of Offers is in descending order by the price
	Input: o1 - pointer to the first Offer from the pair
		   o2 - pointer to the second Offer from the pair
	Output: 1 if the order is respected, 0 otherwise
*/
int sortDescendingByPrice(Offer* o1, Offer* o2);

/*
	Deep copy of an OfferRepo
	Input: destinationR - pointer to the destination OfferRepo
		   sourceR - pointer to the source OfferRepo from where the content will be copied
	Output: None
*/
void copyRepo(OfferRepo* destinationR, OfferRepo* sourceR);

// Tests
void repoTests();