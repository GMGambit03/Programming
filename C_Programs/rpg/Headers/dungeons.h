#ifndef DUNGEONS
#define DUNGEONS

#include "dungeonMenus.h"
#include "entityStructs.h"

typedef struct Dungeon Dungeon;

typedef enum{
    EXIT,
    RAN,
    DIED,
    BOSSDEFEATED
}DungeonReturns;

typedef struct{
    Dungeon **dungeons;
    int size;
}DungeonDatabase;

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

typedef struct Dungeon{
    int dungeonId;
    char *dungeonName;
    char *description;

    DungeonNode *entrance;
    DungeonNode *bossRoom;

    int *possibleEnimies;
    int possEnemyCount;

    int minEnemyCnt;
    int maxEnemyCnt;
    int dungeonBossId;
}Dungeon;

DungeonReturns dungeonEntrance(GameState **gameState, int dungeonId);
DungeonReturns enterDungeon(Player **player, char *dungeonName, DungeonNode *dungeonNode);
Dungeon *createDungeon(Object *dungeonData);
Dungeon *loadDungeon(int dungeonId);

#endif