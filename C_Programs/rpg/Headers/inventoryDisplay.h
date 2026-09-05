#ifndef INVDISPLAY
#define INVDISPLAY

#include "combatDisplay.h"
#include "fileHandle.h"
#include "itemHelper.h"

typedef struct {
    char *name;
    ITEMOPTIONS action;
}Options;

typedef struct {
    char *item;
    union{
        char *string;
        float number;
    }value;
}ItemValue;

void itemHeader(ItemArray *items);
Options *itemDisplay(Item *item, int *optionsSize);

int dropQtcMenu();

#endif