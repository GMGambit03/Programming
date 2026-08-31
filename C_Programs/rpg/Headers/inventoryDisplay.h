#ifndef INVDISPLAY
#define INVDISPLAY

#include "fileHandle.h"

void itemHeader(ItemArray *items);
ITEMOPTIONS *itemDisplay(Item *item, int *optionsSize);

int dropQtcMenu();

#endif