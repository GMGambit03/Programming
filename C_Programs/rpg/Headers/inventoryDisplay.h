#ifndef INVDISPLAY
#define INVDISPLAY

#include "combatDisplay.h"
#include "fileHandle.h"
#include "itemHelper.h"

typedef struct {
    char *name;
    ITEMOPTIONS action;
}InventoryOptions;

void itemHeader(ItemArray *items);
InventoryOptions *itemDisplay(Item *item, int *optionsSize);

int dropQtcMenu();

#endif