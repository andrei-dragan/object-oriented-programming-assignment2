#include "OfferRepository.h"
#include "UI.h"
#include "UndoService.h"
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

int main() {	
	OfferRepo* r = createRepo();
	OfferService* s = createService(r);
	UndoService* u = createUndoService();
	UI* ui = createUI(s, u);

	// Add data
	addOfferService(u, s, "seaside", "Mauritius", createDate(11, 12, 2022), 50000.99);
	addOfferService(u, s, "seaside", "Maldive", createDate(10, 12, 2022), 7000.99);
	addOfferService(u, s, "mountain", "Swiss", createDate(10, 10, 2024), 42000.02);
	addOfferService(u, s, "city-break", "Bucharest", createDate(5, 7, 2022), 10000.02);
	addOfferService(u, s, "city-break", "Rome", createDate(3, 1, 2024), 20000.88);
	addOfferService(u, s, "mountain", "Sinaia", createDate(25, 12, 2022), 3250.56);
	addOfferService(u, s, "city-break", "New-York", createDate(13, 3, 2023), 90250.00);
	addOfferService(u, s, "seaside", "Miami", createDate(20, 7, 2025), 69999.99);
	addOfferService(u, s, "mountain", "Alaska", createDate(10, 10, 2023), 30250.00);
	addOfferService(u, s, "city-break", "Tokyo", createDate(20, 2, 2024), 67050.20);

	// Tests
	dateTests();
	offerTests();
	repoTests();
	dynamicArrayTests();
	serviceTests();
	undoTests();

	// Run the program
	startUI(ui);
	destroyUI(ui);

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	int return_value = _CrtDumpMemoryLeaks();
	printf("%d", return_value);

	return 0;
}

