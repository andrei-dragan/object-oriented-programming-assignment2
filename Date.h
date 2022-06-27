#pragma once

typedef struct {
	int day;
	int month;
	int year;
} Date;

/*
	Constructor for a Date structure
	Input: day - integer representing the day of the date
		   month - integer representing the month of the date
		   year - integer representing the year of the date
	Output: A pointer to the created Date structure or NULL if the structure couldn't be created
*/
Date* createDate(int day, int month, int year);

/*
	Destructor for a Date structure
	Input: d - pointer to a Date structure
	Output: None
*/
void destroyDate(Date* d); 

/*
	Creates nullDate - a null Date structure, having 0 as year, month and day
	Input: None
	Output: A pointer to the null Date structure created or NULL if the structure couldn't be created
*/
Date* nullDate();

/*
	Checks if a date is valid
	Input: day - integer representing the day of the date
		   month - integer representing the month of the date
		   year - integer representing the year of the date
	Output: 1 if the date is valid, 0 otherwise
*/
int validDate(int day, int month, int year);

/*
	Checks if 2 Date structures are equal (content wise)
	Input: d1 - pointer to a Date structure
		   d2 - pointer to another Date structure
	Output: 1 if the equality stands, 0 otherwise
*/
int checkEqualDates(Date* d1, Date* d2);

/*
	Transforms the Date structure into a printable string and stores the string
	Input: d - pointer to a Date structure
	Output: str - a string representing the printable string
*/
void dateToString(Date* d, char str[]);

/*
	Updates the content of a Date
	Input: d - pointer to a Date structure
		   day - integer representing the new day of the date
		   month - integer representing the new month of the date
		   year - integer representing the new year of the date
	Output: 1 if the Date was successfully updated, 0 otherwise
*/
int updateDate(Date* d, int newDay, int newMonth, int newYear);

/*
	Copies the content from a source Date structure to a destination Date structure
	Input: d1 - pointer to the destination Date
	       d2 - pointer to the source Date
	Output: None
*/
void copyDate(Date* d1, Date* d2);

/*
	Check if a Date structure is of type nullDate
	Input: d - pointer to a Date structure
	Output: 1 if the Date is of type nullDate, 0 otherwise
*/
int checkNullDate(Date* d);

/*
	Check if d1 is a later date than d2
	Input: d1 - pointer to the Date structure that will be checked
		   d2 - pointer to the earliest Date structure
	Output: 1 if d1 > d2, 0 otherwise
*/
int greaterDate(Date* d1, Date* d2);

// Tests
void dateTests();