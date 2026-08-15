#ifndef FILES
#define FILES

#include "itemHelper.h"
#include "jsonHeaders/jsonChecker.h"
#include "jsonHeaders/getFile.h"
#include "jsonHeaders/parser.h"

#include "entityStructs.h"

void getPlayerData(Player *playerData);
ClassDatabase *createClassDataBase();
ItemDatabase *createItemDatabase();

#endif