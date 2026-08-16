#ifndef FILES
#define FILES

#include "itemHelper.h"
#include "jsonHeaders/jsonChecker.h"
#include "jsonHeaders/getFile.h"
#include "jsonHeaders/parser.h"

#include "dungeons.h"
#include "entityStructs.h"

void getPlayerData(Player *playerData);
ClassDatabase *createClassDB();
ItemDatabase *createItemDB();
DungeonDatabase *createDungeonDB();

#endif