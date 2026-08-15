#ifndef MENUS
#define MENUS

#include <stdlib.h>

#include "fileHandle.h"
// "entity Strcutcs is included from filehandle  
#include "stringHelpers.h"

int startMenu();
char *newSaveMenu();
Player *classMenu(ClassDatabase *classDataBase);
int displayClassInfo(Class *classData);

#endif