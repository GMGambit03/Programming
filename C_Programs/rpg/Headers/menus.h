#ifndef MENUS
#define MENUS

#include <stdlib.h>

#include "fileHandle.h"
#include "rpgStructs.h"
#include "stringHelpers.h"

int startMenu();
char *newSaveMenu();
Player *classMenu(ClassDatabase *classDataBase);
int displayClassInfo(Class *classData);

#endif