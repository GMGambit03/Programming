#ifndef DUNGEONS
#define DUNGEONS

#include "dungeonMenus.h"
#include "dungeonGeneration.h"

typedef struct DungeonDatabase DungeonDatabase;
typedef struct Database Database;

typedef struct Dungeon Dungeon;

DungeonReturns dungeonEntrance(GameState **gameState, Database **DB, int dungeonId);
DungeonReturns enterDungeon(Player **player, char *dungeonName, DungeonNode *dungeonNode, Database **DB);
Dungeon *loadDungeon(Database **DB, int dungeonId);

Direction getDirections(DungeonNode *dungeonNode);

#endif