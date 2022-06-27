#include "Date.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

Date* createDate(int day, int month, int year) {
	Date* d = malloc(sizeof(Date));
	if (d == NULL)
		return NULL;
	
	d->day = day;
	d->month = month;
	d->year = year;

	return d;
}

void destroyDate(Date* d) {
	if (d == NULL)
		return;
	free(d);
}

int checkEqualDates(Date* d1, Date* d2) {
	if (d1->day == d2->day && d1->month == d2->month && d1->year == d2->year)
		return 1;
	return 0;
}

Date* nullDate() {
	return createDate(0, 0, 0);
}

int validDate(int day, int month, int year) {
	if (0 >= day || day >= 32)
		return 0;

	if (0 >= month || month >= 13)
		return 0;

	if (!(year >= 2021))
		return 0;

	if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 31)
		return 0;
	if (month == 2) {
		if (!(year % 4 == 0 && year % 100 != 0) && day >= 29)
			return 0;
		else if (year % 4 == 0 && year % 100 != 0 && day >= 30)
			return 0;
	}

	return 1;
}	

void dateToString(Date* d, char str[]) {
	if (d == NULL)
		return; 
	sprintf(str, "%d-%d-%d", d->day, d->month, d->year);
}

int updateDate(Date* d, int newDay, int newMonth, int newYear) {
	if (d == NULL)
		return 0;	

	if (validDate(newDay, newMonth, newYear)) {
		d->day = newDay;
		d->month = newMonth;
		d->year = newYear;
		return 1;
	}
	return 0;
}

int checkNullDate(Date* d) {
	if (d->day == 0 && d->month == 0 && d->year == 0)
		return 1;
	return 0;
}

void copyDate(Date* d1, Date* d2) {
	if (d1 == NULL || d2 == NULL)
		return;

	d1->day = d2->day;
	d1->month = d2->month;
	d1->year = d2->year;
}

int greaterDate(Date* d1, Date* d2) {
	if (d1->year == d2->year) {
		if (d1->month == d2->month) {
			if (d1->day > d2->day)
				return 1;
			else
				return 0;
		}
		else
			return (d1->month > d2->month);
	}
	else
		return (d1->year > d2->year);
}


// ================================================================ //
void dateTests() {
	// createDate()
	Date* d1 = createDate(12, 10, 2024);
	assert(d1->day == 12 && d1->month == 10 && d1->year == 2024);

	// updateDate() & validDate()
	int res = updateDate(d1, 31, 2, 2024);
	assert(res == 0);
	res = updateDate(d1, 12, 12, 2025);
	assert(res == 1 && d1->day == 12 && d1->month == 12 && d1->year == 2025);

	// nullDate()
	Date* d2 = nullDate();
	assert(d2->day == 0 && d2->month == 0 && d2->year == 0);

	// checkNullDate()
	assert(checkNullDate(d1) != 1 && checkNullDate(d2) == 1);

	// copyDate() & checkEqualDates()
	copyDate(d2, d1);
	assert(d2->day == 12 && d2->month == 12 && d2->year == 2025);
	assert(checkEqualDates(d1, d2) == 1);

	updateDate(d1, 10, 10, 2024);
	assert(d2->day == 12 && d2->month == 12 && d2->year == 2025);
	assert(checkEqualDates(d1, d2) == 0);

	// dateToString()
	char str[200];
	dateToString(d1, str);
	assert(strcmp(str, "10-10-2024") == 0);

	// greaterDate()
	assert(greaterDate(d2, d1));

	// destroyDate()
	destroyDate(d1);
	destroyDate(d2);
}