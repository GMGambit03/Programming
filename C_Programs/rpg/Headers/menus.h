#ifndef MENUS
#define MENUS

#include <stdlib.h>

#include "fileHandle.h"
#include "stringHelpers.h"

int startMenu();
char *newSaveMenu();
void classMenu(Player *player);
void displayClassInfo(Object *classObj);

#endif