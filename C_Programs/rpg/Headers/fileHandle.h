#ifndef FILES
#define FILES

#include "inventoryHelper.h"
#include "jsonHeaders/jsonChecker.h"
#include "jsonHeaders/getFile.h"
#include "jsonHeaders/parser.h"

#include "rpgStructs.h"

void getPlayerData(Player *playerData);
ClassDatabase *createClassDataBase();
ItemDatabase *createItemDatabase();

#endif