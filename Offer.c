#include "Offer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

Offer* createOffer(char* type, char* destination, Date* departureDate, double price) {
	Offer* o = malloc(sizeof(Offer));
	if (o == NULL)
		return NULL; 

	o->type = malloc(sizeof(char) * (strlen(type) + 1));
	if (o->type != NULL)
		strcpy(o->type, type);

	o->destination = malloc(sizeof(char) * (strlen(destination) + 1));
	if (o->destination != NULL)
		strcpy(o->destination, destination);

	o->departureDate = departureDate;	
	o->price = price;
	
	return o;
}

void destroyOffer(Offer* o) {
	if (o == NULL)
		return; 

	free(o->type);
	free(o->destination);
	destroyDate(o->departureDate);
	free(o);
}

int updateOffer(Offer* o, Offer* newOffer) {
	if (o == NULL || newOffer == NULL)
		return 0;

	if (strcmp(newOffer->type, "-") != 0) {
		free(o->type);
		o->type = malloc(sizeof(char) * (strlen(newOffer->type) + 1));
		if (o->type != NULL)
			strcpy(o->type, newOffer->type);
	}

	if (strcmp(newOffer->destination, "-") != 0) {
		free(o->destination);
		o->destination = malloc(sizeof(char) * (strlen(newOffer->destination) + 1));
		if (o->destination != NULL)
			strcpy(o->destination, newOffer->destination);
	}

	if(!(checkNullDate(newOffer->departureDate)))
		copyDate(o->departureDate, newOffer->departureDate);

	if (newOffer->price != 0) 
		o->price = newOffer->price;

	return 1;
}

int checkEqual(Offer* o1, Offer* o2) {
	if (o1 == NULL || o2 == NULL)
		return 0;

	if(strcmp(o1->destination, o2->destination) == 0 && checkEqualDates(o1->departureDate, o2->departureDate))
		return 1;
	return 0;
}

void offerToString(Offer* o, char str[]) {
	if (o == NULL)
		return;
	sprintf(str, "type - %s | destination - %s | price - %0.2lf | departure date - ", o->type, o->destination, o->price);
	
	char dateString[20];
	dateToString(o->departureDate, dateString);

	strcat(str, dateString);
}

Offer* createCopiedOffer(Offer* o) {
	Date* departureDate = nullDate();
	copyDate(departureDate, o->departureDate);

	return createOffer(o->type, o->destination, departureDate, o->price);
}


// ================================================================ //
void offerTests() {
	// createOffer()
	Offer* o1 = createOffer("seaside", "Romania", createDate(12, 12, 2024), 45600.99);
	Date* equalityDate = createDate(12, 12, 2024);
	assert(strcmp(o1->type, "seaside") == 0 && strcmp(o1->destination, "Romania") == 0 && checkEqualDates(o1->departureDate, equalityDate) && o1->price == 45600.99);
	destroyDate(equalityDate);

	// createCopiedOffer() && checkEqual()
	Offer* o3 = createCopiedOffer(o1);
	assert(checkEqual(o1, o3));

	// updateOffer()
	Offer* o2 = createOffer("mountain", "India", createDate(10, 1, 2025), 75600.01);
	updateOffer(o1, o2);
	equalityDate = createDate(10, 1, 2025);
	assert(strcmp(o1->type, "mountain") == 0 && strcmp(o1->destination, "India") == 0 && checkEqualDates(o1->departureDate, equalityDate) && o1->price == 75600.01);
	destroyDate(equalityDate);

	Offer* emptyOffer = createOffer("-", "-", nullDate(), 0);
	updateOffer(emptyOffer, o2);
	equalityDate = createDate(10, 1, 2025);
	assert(strcmp(emptyOffer->type, "mountain") == 0 && strcmp(emptyOffer->destination, "India") == 0 && checkEqualDates(emptyOffer->departureDate, equalityDate) && emptyOffer->price == 75600.01);
	destroyDate(equalityDate);

	// checkEqual()
	assert(checkEqual(o1, o2) && !checkEqual(o1, o3));

	// offerToString()
	char str[200];
	offerToString(o3, str);
	assert(strcmp(str, "type - seaside | destination - Romania | price - 45600.99 | departure date - 12-12-2024") == 0);

	// destroyOffer()
	destroyOffer(o1);
	destroyOffer(o2);
	destroyOffer(o3);
	destroyOffer(emptyOffer);
}