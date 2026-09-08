#ifndef INVDISPLAY
#define INVDISPLAY

#include "combatDisplay.h"
#include "fileHandle.h"
#include "itemHelper.h"

typedef struct {
    char *name;
    INVENTORYOPTIONS action;
}ItemOptions;

typedef struct {
    char *item;
    union{
        char *string;
        float number;
    }value;
}ItemValue;

void itemHeader(ItemArray *items, Item *currWeapon, Item *currArmor, Player *player);
ItemOptions *itemDisplay(Item *item, Player *player, int *optionsSize);

int dropQtcMenu();

#endif