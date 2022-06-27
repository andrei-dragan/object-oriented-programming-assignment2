#include "UndoService.h"
#include "DynamicArray.h"
#include "OfferRepository.h"
#include "OfferService.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

UndoService* createUndoService() {
	UndoService* u = (UndoService*)malloc(sizeof(UndoService));
	if (u == NULL)
		return NULL;

	u->index = 0;
	u->nrOperations = 0;
	
	u->repos = createDynamicArray(0, destroyRepo);
	if (u->repos == NULL)
		return NULL;

	OfferRepo* emptyRepo = createRepo();
	addElem(u->repos, emptyRepo);

	return u;
}

void destroyUndoService(UndoService* u) {
	if (u == NULL)
		return;
	destroyDynamicArray(u->repos);
	free(u);
}

OfferRepo* undo(UndoService* u) {
	if (u->index - 1 == -1 || u == NULL)
		return NULL;

	u->index--;
	return getElem(u->repos, u->index);
}

OfferRepo* redo(UndoService* u) {
	if (u->index >= u->nrOperations - 1 || u == NULL)
		return NULL;

	u->index++;
	return getElem(u->repos, u->index);
}

void logOp(UndoService* u, OfferRepo* newR) {
	for (int i = u->nrOperations - 1; i >= u->index + 1; i--) {
		OfferRepo* r = getElem(u->repos, i);
		removeElem(u->repos, r);
		destroyRepo(r);
	}
	u->index++;
	u->nrOperations = u->index + 1;
	addElem(u->repos, newR);
}

// ================================================================ //
void undoTests() {
	// createUndoService()
	UndoService* u = createUndoService();
	assert(u != NULL);

	// undo() + redo() + logOp() 
	OfferRepo* r = createRepo();
	OfferService* s = createService(r);
	
	addOfferService(u, s, "mountain", "Sinaia", createDate(12, 12, 2025), 8000);
	addOfferService(u, s, "seaside", "Mamaia", createDate(07, 07, 2022), 10000);
	updateOfferService(u, s, "Sinaia", createDate(12, 12, 2025), "-", "Busteni", nullDate(), 6500);
	removeOfferService(u, s, "Mamaia", createDate(07, 07, 2022));

	OfferRepo* res = redo(u);
	assert(res == NULL);

	assert(getLengthRepo(getRepo(s)) == 1);
	res = undo(u);
	updateRepo(s, res);
	assert(res != NULL && getLengthRepo(getRepo(s)) == 2);
	
	res = undo(u);
	updateRepo(s, res);
	assert(res != NULL && strcmp(getOfferOnPos(getRepo(s), 0)->destination, "Sinaia") == 0);

	res = redo(u);
	updateRepo(s, res);
	assert(res != NULL && strcmp(getOfferOnPos(getRepo(s), 0)->destination, "Busteni") == 0);

	res = undo(u);
	updateRepo(s, res);
	res = undo(u);
	updateRepo(s, res);
	assert(res != NULL && getLengthRepo(getRepo(s)) == 1);

	res = redo(u);
	updateRepo(s, res);
	assert(res != NULL && getLengthRepo(getRepo(s)) == 2);

	addOfferService(u, s, "city-break", "Cluj", createDate(10, 1, 2022), 12000);
	res = redo(u);
	assert(res == NULL && strcmp(getOfferOnPos(getRepo(s), 0)->destination, "Sinaia") == 0);

	// destroyUndoService()
	destroyService(s);
	destroyUndoService(u);
}