#ifndef INVDISPLAY
#define INVDISPLAY

#include "fileHandle.h"

void itemHeader(Inventory *inventory, ItemArray *items);
ITEMOPTIONS *itemDisplay(Item *item, int *optionsSize);

int dropQtcMenu();

#endif