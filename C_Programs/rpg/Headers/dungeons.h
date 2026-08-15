#ifndef DUNGEONS
#define DUNGEONS

#include "dungeonMenus.h"
#include "entityStructs.h"

typedef enum{
    EXIT,
    RAN,
    DIED,
    BOSSDEFEATED
}DungeonReturns;

typedef struct DungeonNode{
    EnemyArray *enemies;
    int enemiesCount;

    char *description;

    struct DungeonNode *north;
    struct DungeonNode *east;
    struct DungeonNode *south;
    struct DungeonNode *west;

    bool isBossRoom;
    int utilityRequ;
}DungeonNode;

typedef struct{
    int dungeonId;
    char *dungeonName;

    DungeonNode *entrance;
    DungeonNode *bossRoom;

    int *possibleEnimies;
    int possEnemyCount;
    int dungeonBossId;
}Dungeon;

DungeonReturns dungeonEntrance(GameState **gameState, int dungeonId);
DungeonReturns enterDungeon(Player **player, char *dungeonName, DungeonNode *dungeonNode);
Dungeon *loadDungeon(int dungeonId);

#endif