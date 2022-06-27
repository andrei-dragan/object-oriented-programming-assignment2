#pragma once
#include "OfferRepository.h"
#include "UndoService.h"

typedef int (*FilterFunction)(Offer*, void*, void*);

typedef struct {
	OfferRepo* repo;
} OfferService;

/*
	Constructor for the Offer Service - OfferService structure
	Input: r - pointer to the OfferRepo on the top of which the OfferService is constructed
	Output: A pointer to the created OfferService structure or NULL if the structure couldn't be created
*/
OfferService* createService(OfferRepo *r);

/*
	Destructor for an OfferService structure
	Input: s - pointer to an OfferService structure
	Output: None
*/
void destroyService(OfferService* s);

/*
	Adds an Offer to the OfferService
	Input: u - pointer to the UndoService
		   s - pointer to the OfferService
		   type - string representing the type of the Offer
		   destination - string representing the destination of the Offer
		   departureDate - Date structure representing the departure date of the Offer
		   price - double representing the price of the Offer
	Output: 1 if the operation was successful, 0 otherwise
*/
int addOfferService(UndoService* u, OfferService* s, char* type, char* destination, Date* departureDate, double price);

/*
	Updates an Offer from the OfferService
	Input: u - pointer to the UndoService
		   s - pointer to the OfferService
		   destination - string representing the destination of the Offer to be updated
		   departureDate - Date structure representing the departure date of the Offer to be updated
		   newType - string representing the new type of the Offer
		   newDestination - string representing the new destination of the Offer
		   newDepartureDate - Date structure representing the new departure date of the Offer
		   newPrice - double representing the new price of the Offer
	Output: 1 if the operation was successful, 0 otherwise
*/
int updateOfferService(UndoService* u, OfferService* s, char* destination, Date* departureDate, char* newType, char* newDestination, Date* newDepartureDate, double newPrice);

/*
	Removes an Offer from the OfferService
	Input: u - pointer to the UndoService
		   s - pointer to the OfferService
		   destination - string representing the destination of the Offer
		   departureDate - Date structure representing the departure date of the Offer
	Output: 1 if the operation was successful, 0 otherwise
*/
int removeOfferService(UndoService* u, OfferService* s, char* destination, Date* departureDate);

/*
	Get the repository on top of which the OfferService is built
	Input: s - pointer to the OfferService
	Output: pointer to the OfficeRepo on top of which the OfferService is built
*/
OfferRepo* getRepo(OfferService* s);

/*
	Update the OfficeRepo on top of which the OfferService is built
	Input: s - pointer to the OfferService
		   newR - pointer to the new OfferRepo
	Output: None
*/
void updateRepo(OfferService* s, OfferRepo* newR);

/*
	Filter the Offers based on a filter function and some parameters
	Input: s - pointer to the OfferService
		   filterFunction - pointer to the filterFunction
		   param1 - pointer to the first crietria parameter
		   param2 - pointer to the second criteria parameter
	Output: r - pointer to an OfficeRepo that contains only the filtered Offers
*/
OfferRepo* filterOffers(OfferService* s, FilterFunction filterFunction, void* param1, void* param2);

/*
	Validate if an Offer contains as destination a given substring
	Input: o - pointer to the Offer to be checked
		   param1 - string pointer to the substring 
		   param2 - not useful in this case, should be NULL
	Output: 1 if the substring is inside the Offer's destination, 0 otherwise
*/
int filterByDestination(Offer* o, void* param1, void* param2);

/*
	Validate if an Offer is of a certain type and has a departure date later than a given one
	Input: o - pointer to the Offer to be checked
		   param1 - string pointer to the string containing the type
		   param2 - Date pointer to the Date containing the earliest departure date
	Output: 1 if the Offer matches the criteria, 0 otherwise
*/
int filterByTypeAndDate(Offer* o, void* param1, void* param2);

/*
	Validate if an Offer has a greater price than a given one
	Input: o - pointer to the Offer to be checked
		   param1 - double pointer to the given price
		   param2 - not useful in this case, should be NULL
	Output: 1 if the Offer matches the criteria, 0 otherwise
*/
int filterByPrice(Offer* o, void* param1, void* param2);

// Tests
void serviceTests();