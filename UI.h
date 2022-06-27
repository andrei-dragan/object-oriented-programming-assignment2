#pragma once
#include "OfferService.h"
#include "UndoService.h"

typedef struct {
	OfferService* serv;
	UndoService* undo;
} UI;

UI* createUI(OfferService* s, UndoService* u);
void destroyUI(UI* ui);

void startUI(UI* ui);