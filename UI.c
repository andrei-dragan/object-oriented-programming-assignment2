#include "UI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

UI* createUI(OfferService* s, UndoService* u) {
	UI* ui = malloc(sizeof(UI));
	if (ui == NULL)
		return NULL;
	ui->serv = s;
	ui->undo = u;
	return ui;
}

void destroyUI(UI* ui) {
	if (ui == NULL)
		return;

	destroyUndoService(ui->undo);
	destroyService(ui->serv);
	free(ui);
}

// Function that prints the menu
void printMenu()
{
	printf("\n**********************************************************\n");
	printf("1 - add an offer.\n");
	printf("2 - remove an offer.\n");
	printf("3 - update an offer.\n");
	printf("4 - list all offers\n");
	printf("5 - display all tourism offers whose destinations contain a given string sorted ascending by price\n");
	printf("6 - display all tourism offers of a certain type, no earlier than a given departure date\n");
	printf("7 - display all tourism offers cheaper than a given price\n");
	printf("8 - to undo/redo\n");
	printf("0 - to exit.\n");
	printf("**********************************************************\n");
}

// Function the reads an integer number
int readIntegerNumber(const char* message)
{
	char s[16] = { 0 };
	int res = 0;
	int flag = 0;
	int r = 0;

	while (flag == 0)
	{
		printf(message);
		scanf("%15s", s);

		r = sscanf(s, "%d", &res);	// reads data from s and stores them as integer, if possible; returns 1 if successful
		flag = (r == 1);
		if (flag == 0)
			printf("Error reading integer number!\n");
	}
	return res;
}

// Function that checks if a valid command was input
int validCommand(int command) {
	if (command >= 0 && command <= 8)
		return 1;
	return 0;
}

// Function that gets the parameters for adding an offer (it also calls the function that adds the offer)
int addOfferUI(UI* ui)
{
	char type[50], destination[50];
	double price = 0;
	int day = 0, month = 0, year = 0, ok = 0, res;
	Date* departureDate = nullDate();

	// Read the type
	ok = 0;
	while (ok == 0) {
		printf("Choose the type of the offer: \n -seaside \n -mountain \n -city-break \n");
		printf("Input the type: ");

		res = scanf("%49s", type);
		type[49] = 0; // avoid error "string type might not be zero-terminated"
		if (strcmp(type, "seaside") != 0 && strcmp(type, "mountain") != 0 && strcmp(type, "city-break") != 0) 
			printf("Invalid type!\n");
		else 
			ok = 1;	
	}
	
	// Read the destination
	ok = 0;
	printf("Input the destination: ");
	res = scanf("%49s", destination);
	destination[49] = 0;
	
	// Read the departure date
	ok = 0;
	while (ok == 0) {
		printf("Input the departure date, day - month - year in this specific order\n");
		year = readIntegerNumber("Input the year: ");
		month = readIntegerNumber("Input the month: ");
		day = readIntegerNumber("Input the day: ");

		if (updateDate(departureDate, day, month, year)) 
			ok = 1;
		else 
			printf("Invalid date!\n");
	}

	// Read the price
	ok = 0;
	printf("Input the price: ");
	while (ok == 0) {
		res = scanf("%lf", &price);
		if (price <= 0) 
			printf("The price should be greater than 0! Try again: ");
		else 
			ok = 1;
	}
	
	// Add the offer
	return addOfferService(ui->undo, ui->serv, type, destination, departureDate, price);
}

// Function that gets the parameters for updating an offer (it also calls the function that updates the offer)
int updateOfferUI(UI* ui) {
	char currentDestination[50], newType[50], newDestination[50];
	double newPrice = 0;
	Date* currentDepartureDate = nullDate(), * newDepartureDate = nullDate();
	int i, day = 0, month = 0, year = 0, ok = 0, res;

	// Read the fields to identify the Offer to be updated
	printf("What offer you want to update?\n");

	// Read the current destination
	printf("Input the current destination of the offer you want to update: ");
	res = scanf("%49s", currentDestination);
	currentDestination[49] = 0;
		
	// Read the current departure date
	ok = 0;
	while (ok == 0) {
		printf("Input the current departure date, day - month - year in this specific order of the offer you want to update\n");
		year = readIntegerNumber("Input the year: ");
		month = readIntegerNumber("Input the month: ");
		day = readIntegerNumber("Input the day: ");

		if (updateDate(currentDepartureDate, day, month, year))
			ok = 1;
		else 
			printf("Invalid date!\n");
	}
		
	// Create copies of those parameters to create a new Offer, in order to check if there exists inside the repo the user-requested Offer
	Date* copyCurrentDepartureDate = nullDate();
	copyDate(copyCurrentDepartureDate, currentDepartureDate);

	char copyCurrentDestination[50];
	copyCurrentDestination[49] = 0;
	strcpy(copyCurrentDestination, currentDestination);

	Offer* o = createOffer("-", copyCurrentDestination, copyCurrentDepartureDate, 0);
	i = findOfferRepo(getRepo(ui->serv), o);
	destroyOffer(o);

	if (i == -1) {
		printf("We couldn't find an offer matching your input!");
		destroyDate(currentDepartureDate);
		destroyDate(newDepartureDate);
		return -1;
	}

	// Print the user-requested Offer
	char offerString[200];
	Offer* oldOffer = getOfferOnPos(getRepo(ui->serv), i);
	offerToString(oldOffer, offerString);

	printf("**********************************************************\n");
	printf("Your offer is: ");
	printf("%s\n", offerString);
	printf("**********************************************************\n");

	// Read the updated type
	ok = 0;
	while (ok == 0) {
		printf("If you don't want to update the type, input '-', otherwise input the new type of the offer: \n - seaside \n - mountain \n - city-break \n");
		printf("Input the type: ");

		res = scanf("%49s", newType);
		newType[49] = 0;

		if (strcmp(newType, "seaside") != 0 && strcmp(newType, "mountain") != 0 && strcmp(newType, "city-break") != 0 && strcmp(newType, "-") != 0)
			printf("Invalid type!\n");
		else 
			ok = 1;
	}

	// Read the updated destination
	ok = 0;
	printf("If you don't want to update the destination, input '-', otherwise input the new destination: ");
	res = scanf("%49s", newDestination);
	newDestination[49] = 0;

	// Read the updated departure date
	ok = 0;
	while (ok == 0) {
		printf("Input the departure date, day - month - year in this specific order. If you don't want to change the date, input 0 for every field\n");
		year = readIntegerNumber("Input the year: ");
		month = readIntegerNumber("Input the month: ");
		day = readIntegerNumber("Input the day: ");

		if (year == 0 && month == 0 && day == 0) 
			ok = 1;
		else if (updateDate(newDepartureDate, day, month, year))
			ok = 1;
		else
			printf("Invalid date!\n");
	}
	
	// Read the updated price
	ok = 0;
	printf("Input 0 if you don't want to update the price, otherwise input the new price: ");
	while (ok == 0) {
		res = scanf("%lf", &newPrice);
		if (newPrice < 0) {
			printf("The price should be greater than 0 or 0 if you don't want to update it!");
		}
		else 
			ok = 1;
	}
	
	// Update the offer
	return updateOfferService(ui->undo, ui->serv, currentDestination, currentDepartureDate, newType, newDestination, newDepartureDate, newPrice);
}

// Function that gets the parameters for rempving an offer (it also calls the function that removes the offer)
int removeOfferUI(UI* ui) {
	char destination[50];
	int day = 0, month = 0, year = 0, ok = 0, res;
	Date* departureDate = nullDate();

	// Read the destination
	ok = 0;
	printf("Input the destination of the offer you want to remove: ");
	res = scanf("%49s", destination);
	destination[49] = 0;

	// Read the date
	ok = 0;
	while (ok == 0) {
		printf("Input the departure date, day - month - year in this specific order of the offer you want to remove\n");
		year = readIntegerNumber("Input the year: ");
		month = readIntegerNumber("Input the month: ");
		day = readIntegerNumber("Input the day: ");

		if (updateDate(departureDate, day, month, year)) 
			ok = 1;
		else 
			printf("Invalid date!\n");
	}

	// Remove the Offer
	return removeOfferService(ui->undo, ui->serv, destination, departureDate);
}

// Function that prints all the current Offers
void printOffers(UI* ui) {
	OfferRepo* r = getRepo(ui->serv);
	if (r == NULL)
		return; 

	printf("**********************************************************\n");

	for (int i = 0; i < getLengthRepo(r); i++) {
		char offerString[200];
		Offer* o = getOfferOnPos(r, i);
		offerToString(o, offerString);
		printf("Offer %d: ", i + 1);
		printf("%s\n", offerString);
	}
}

// Function that prints all tourism offers whose destinations contain a given string sorted ascending by price
void printOffersByDestination(UI* ui) {
	char destinationTemplate[50], stringOffer[200];
	int res; 

	printf("Input a destination or '-' if you want all of them: ");

	res = scanf("%49s", destinationTemplate);
	destinationTemplate[49] = 0;

	printf("**********************************************************\n");
	OfferRepo* filteredR = filterOffers(ui->serv, filterByDestination, destinationTemplate, NULL);
	sortRepoByCriteria(filteredR, sortAscendingByPrice);
	int length = getLengthRepo(filteredR);
	for (int i = 0; i < length; i++) {
		Offer* o = getOfferOnPos(filteredR, i);
		offerToString(o, stringOffer);
		printf("%s\n", stringOffer);
	}
	printf("**********************************************************\n");
	destroyRepo(filteredR);
}

// Function that prints all tourism offers of a given type, having the departure date after a given date
void printOffersByTypeAndDate(UI* ui) {
	char type[50];
	int day = 0, month = 0, year = 0, ok = 0, choice = 0, res;
	Date* departureDate = nullDate();
	
	// Read the type
	ok = 0;
	while (ok == 0) {
		printf("Choose the type of the offer: \n -seaside \n -mountain \n -city-break \n");
		printf("Input the type: ");

		res = scanf("%49s", type);
		type[49] = 0; // avoid error "string type might not be zero-terminated"
		if (strcmp(type, "seaside") != 0 && strcmp(type, "mountain") != 0 && strcmp(type, "city-break") != 0)
			printf("Invalid type!\n");
		else
			ok = 1;
	}

	// Read the date
	ok = 0;
	while (ok == 0) {
		printf("Input the departure date, day - month - year in this specific order of the offer you want to remove\n");
		year = readIntegerNumber("Input the year: ");
		month = readIntegerNumber("Input the month: ");
		day = readIntegerNumber("Input the day: ");

		if (updateDate(departureDate, day, month, year))
			ok = 1;
		else
			printf("Invalid date!\n");
	}

	// Choose the sorting criteria
	choice = readIntegerNumber("Choose the order: 0 - no order | 1 - ascending by price | 2 - descending by price: ");
	while (validCommand(choice) == 0) {
		printf("Please input a valid choice!\n");
		readIntegerNumber("Choose the order: 0 - no order | 1 - ascending by price | 2 - descending by price: ");
	}
	
	// Print it
	printf("**********************************************************\n");
	char stringOffer[200];
	OfferRepo* filteredR = filterOffers(ui->serv, filterByTypeAndDate, type, departureDate);

	// Sort the Offers
	if (choice == 1) 
		sortRepoByCriteria(filteredR, sortAscendingByPrice);
	else 
		sortRepoByCriteria(filteredR, sortDescendingByPrice);

	int length = getLengthRepo(filteredR);
	for (int i = 0; i < length; i++) {
		Offer* o = getOfferOnPos(filteredR, i);
		offerToString(o, stringOffer);
		printf("%s\n", stringOffer);
	}
	printf("**********************************************************\n");
	destroyDate(departureDate);
	destroyRepo(filteredR);
}

// Function that prints all tourism offers cheaper than a given price
void printOffersByPrice(UI* ui) {
	char stringOffer[200];
	int res, ok = 0;
	double price = 0;

	while (ok == 0) {
		printf("Input the price: ");
		res = scanf("%lf", &price);
		if (price <= 0)
			printf("The price should be greater than 0! Try again: ");
		else
			ok = 1;
	}

	printf("**********************************************************\n");
	OfferRepo* filteredR = filterOffers(ui->serv, filterByPrice, &price, NULL);
	int length = getLengthRepo(filteredR);
	for (int i = 0; i < length; i++) {
		Offer* o = getOfferOnPos(filteredR, i);
		offerToString(o, stringOffer);
		printf("%s\n", stringOffer);
	}
	printf("**********************************************************\n");
	destroyRepo(filteredR);
}

// Function that gets the undo or redo command from the user and does the operation 
int undoRedoUI(UI* ui) {
	int res = 0;
	while (res != -1 && res != 1) {
		res = readIntegerNumber("Input -1 to undo or +1 to redo: ");

		if (res == -1) {
			OfferRepo* newR = undo(ui->undo);
			if (newR == NULL)
				return -1;
			// Change the current active repo
			updateRepo(ui->serv, newR);
		}
		else if (res == 1) {
			OfferRepo* newR = redo(ui->undo);
			if (newR == NULL)
				return -2;
			// Change the current active repo
			updateRepo(ui->serv, newR);
		}
	}
	return 1;
}

void startUI(UI* ui) {
	while (1) {
		printMenu();
		
		int command = readIntegerNumber("Input command: ");
		while (validCommand(command) == 0) {
			printf("Please input a valid command!\n");
			command = readIntegerNumber("Input command: ");
		}

		if (command == 0)
			break;
		else if (command == 1) {
			int res = addOfferUI(ui);
			if (res == 1) {
				printf("Offer added successfully!\n");
			}
			else {
				printf("There was an error! Make sure there isn't already a similar offer!\n");
			}
		}
		else if (command == 2) {
			int res = removeOfferUI(ui);
			if (res == 1) {
				printf("Offer removed successfully!\n");
			}
			else if (res == 0) {
				printf("There was an error! Make sure the offer isn't already removed!\n");
			}
		}
		else if (command == 3) {
			int res = updateOfferUI(ui);
			if (res == 1) {
				printf("Offer updated successfully!\n");
			}
			else if (res == 0) {
				printf("There was an error! Make sure there isn't already a similar offer!\n");
			}
		}
		else if (command == 4) {
			printOffers(ui);
		}
		else if (command == 5) {
			printOffersByDestination(ui);
		}
		else if (command == 6) {
			printOffersByTypeAndDate(ui);
		}
		else if (command == 7) {
			printOffersByPrice(ui);
		}
		else if (command == 8) {
			int res = undoRedoUI(ui);
			if (res == -1)
				printf("You cannot undo anymore!\n");
			else if (res == -2)
				printf("You cannot redo anymore!\n");
			else
				printf("Operation successful!\n");
		}
	}
}
