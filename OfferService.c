#include "OfferService.h"
#include "UndoService.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

OfferService* createService(OfferRepo *r) {
	OfferService* s = malloc(sizeof(OfferService));
	if (s == NULL)
		return NULL;
	s->repo = r;
	return s;
}

void destroyService(OfferService* s) {
	if (s == NULL)
		return;

	destroyRepo(s->repo);
	free(s);
}

int addOfferService(UndoService* u, OfferService* s, char* type, char* destination, Date* departureDate, double price) {
	Offer* o = createOffer(type, destination, departureDate, price);

	int res = addOfferRepo(s->repo, o);
	if (res == 0) {
		destroyOffer(o);
		return 0;
	}

	// Add the repo history for the undo
	OfferRepo* newR = createRepo();
	copyRepo(newR, s->repo);
	logOp(u, newR);

	return 1;
}

int updateOfferService(UndoService* u, OfferService* s, char* destination, Date* departureDate, char* newType, char* newDestination, Date* newDepartureDate, double newPrice) {
	Offer* oldOffer = createOffer("-", destination, departureDate, 0);
	Offer* newOffer = createOffer(newType, newDestination, newDepartureDate, newPrice);

	int res = updateOfferRepo(s->repo, oldOffer, newOffer);

	destroyOffer(oldOffer);
	destroyOffer(newOffer);
	
	if (res == 0)
		return 0;

	// Add the repo history for the undo
	OfferRepo* newR = createRepo();
	copyRepo(newR, s->repo);
	logOp(u, newR);

	return res;
}

int removeOfferService(UndoService* u, OfferService* s, char* destination, Date* departureDate) {
	Offer* o = createOffer("", destination, departureDate, 0);
	
	int res = removeOfferRepo(s->repo, o);
	destroyOffer(o);

	if (res == 0)
		return res;

	// Add the repo history for the undo
	OfferRepo* newR = createRepo();
	copyRepo(newR, s->repo);
	logOp(u, newR);

	return res;
}

OfferRepo* getRepo(OfferService* s) {
	if (s == NULL)
		return NULL;
	return s->repo;
}

void updateRepo(OfferService* s, OfferRepo* newR) {
	if (s == NULL || newR == NULL)
		return;
	
	destroyRepo(s->repo);
	s->repo = createRepo();

	copyRepo(s->repo, newR);
}

OfferRepo* filterOffers(OfferService* s, FilterFunction filterFunction, void* param1, void* param2) {
	if (s == NULL)
		return NULL;

	OfferRepo* filteredR = createRepo();
	OfferRepo* oldR = getRepo(s);

	int oldRepoLength = getLengthRepo(oldR);
	for (int i = 0; i < oldRepoLength; i++) {
		Offer* o = getOfferOnPos(oldR, i);
		Offer* copyO = createCopiedOffer(o);

		if (filterFunction(o, param1, param2))
			addOfferRepo(filteredR, copyO);
		else
			destroyOffer(copyO);
	}
	return filteredR;
}

int filterByDestination(Offer* o, void* param1, void* param2) {
	if (strstr(o->destination, param1) || strcmp(param1, "-") == 0)
		return 1;
	return 0;
}

int filterByTypeAndDate(Offer* o, void* param1, void* param2) {
	return (strcmp(param1, o->type) == 0 && greaterDate(o->departureDate, param2));
}

int filterByPrice(Offer* o, void* param1, void* param2) {
	double* price = (double*)param1;
	return(o->price < *price);
}

// ================================================================ //
void serviceTests() {
	// createService()
	UndoService* u = createUndoService();
	OfferRepo* r = createRepo();
	OfferService* s = createService(r);
	
	assert(s != NULL && s->repo != NULL);

	// addOfferService()
	int res = addOfferService(u, s, "seaside", "Romania", createDate(12, 12, 2025), 5600);
	assert(res == 1);

	// updateOfferService()
	res = updateOfferService(u, s, "Romania", createDate(12, 12, 2025), "-", "Bulgaria", nullDate(), 0);
	assert(res == 1);

	// removeOfferService()
	res = removeOfferService(u, s, "Romania", createDate(12, 12, 2025));
	assert(res == 0);
	res = removeOfferService(u, s, "Bulgaria", createDate(12, 12, 2025));
	assert(res == 1);

	// getRepo()
	assert(r == getRepo(s));

	// filterOffers() & filterByDestination() 
	addOfferService(u, s, "seaside", "India", createDate(12, 12, 2024), 10600);
	addOfferService(u, s, "seaside", "Romania", createDate(12, 12, 2025), 5600);
	addOfferService(u, s, "seaside", "America", createDate(12, 12, 2025), 100600);
	OfferRepo* filteredR = filterOffers(s, filterByDestination, "ia", NULL);
	assert(strcmp(getOfferOnPos(filteredR, 0)->destination, "India") == 0);
	assert(strcmp(getOfferOnPos(filteredR, 1)->destination, "Romania") == 0);
	assert(getLengthRepo(filteredR) == 2);
	destroyRepo(filteredR);

	// filterOffers() & filterByTypeAndDate()
	addOfferService(u, s, "mountain", "Swiss", createDate(12, 12, 2025), 10600);
	addOfferService(u, s, "city-break", "Paris", createDate(12, 12, 2025), 9999);
	Date* earlyDate = createDate(1, 1, 2025);
	filteredR = filterOffers(s, filterByTypeAndDate, "seaside", earlyDate);
	destroyDate(earlyDate);
	assert(strcmp(getOfferOnPos(filteredR, 0)->destination, "Romania") == 0);
	assert(strcmp(getOfferOnPos(filteredR, 1)->destination, "America") == 0);
	assert(getLengthRepo(filteredR) == 2);
	destroyRepo(filteredR);

	// filterOffers() & filterByPrice()
	double price = 10000;
	filteredR = filterOffers(s, filterByPrice, &price, NULL);
	assert(strcmp(getOfferOnPos(filteredR, 0)->destination, "Romania") == 0);
	assert(strcmp(getOfferOnPos(filteredR, 1)->destination, "Paris") == 0);
	assert(getLengthRepo(filteredR) == 2);


	// updateRepo();
	updateRepo(s, filteredR);
	assert(s->repo != filteredR);
	assert(strcmp(getOfferOnPos(s->repo, 0)->destination, "Romania") == 0);
	assert(strcmp(getOfferOnPos(s->repo, 1)->destination, "Paris") == 0);
	assert(getLengthRepo(s->repo) == 2);

	// destroyService()
	destroyService(s);
	destroyRepo(filteredR);
	destroyUndoService(u);
}
