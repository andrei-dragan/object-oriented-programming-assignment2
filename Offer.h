#pragma once
#include "Date.h"

typedef struct {
	char* type;
	char* destination;
	Date* departureDate;
	double price; 
} Offer;

/*
	Constructor for an Offer structure
	Input: type - string representing the type of the Offer
		   destination - string representing the destination of the Offer
		   departureDate - Date structure representing the departure date of the Offer
		   price - double representing the price of the Offer
	Output: A pointer to the created Offer structure or NULL if the structure couldn't be created
*/
Offer* createOffer(char* type, char* destination, Date* departureDate, double price);

/*
	Destructor for an Offer structure
	Input: o - pointer to an Offer structure
	Output: None
*/
void destroyOffer(Offer* o);

/*
	Update the content from the destination Offer structure to the content from the source Offer
	Input: o - pointer to the destination Offer
		   newOffer - pointer to the source Offer
	Output: 1 if the operation was successful, 0 otherwise
*/
int updateOffer(Offer* o, Offer* newOffer);

/*
	Check if 2 Offers are equal (content wise)
	Input: o1 - pointer to an Offer structure
		   o2 - pointer to an Offer structure
	Output: 1 if the equality stands, 0 otherwise
*/
int checkEqual(Offer* o1, Offer* o2);

/*
	Create another Offer structure that will copy inside the content from a given Offer
	Input: o - pointer to an Offer structure
	Output: pointer to the newly created Offer structure
*/
Offer* createCopiedOffer(Offer* o);

/*
	Transforms the Offer structure into a printable string and stores the string
	Input: o - pointer to an Offer structure
	Output: str - a string representing the printable string
*/
void offerToString(Offer* o, char str[]);

// Tests
void offerTests();