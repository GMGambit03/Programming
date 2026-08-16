#ifndef DUNGEONS
#define DUNGEONS

#include "dungeonMenus.h"
#include "entityStructs.h"

typedef struct DungeonDatabase DungeonDatabase;
typedef struct Database Database;

typedef struct Dungeon Dungeon;

typedef enum{
    NORTH,
    WEST,
    EAST,
    SOUTH,
    NONE
}Direction;

typedef struct DungeonNode{
    EnemeyDataBase *enemies;
    int enemiesCount;
    bool enemiesDead;

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

    int *possibleEnemies;
    int possEnemyCount;

    int minEnemyCnt;
    int maxEnemyCnt;

    int minRooms;
    int maxRooms;

    int dungeonBossId;
}Dungeon;

DungeonReturns dungeonEntrance(GameState **gameState, Database **DB, int dungeonId);
DungeonReturns enterDungeon(Player **player, char *dungeonName, DungeonNode *dungeonNode, Database **DB);
Dungeon *createDungeon(Object *dungeonData);
DungeonNode *createDungeonNode(int roomCount, Dungeon **dungeon, int *count, Direction parent, EnemeyDataBase **enemeyDatabase);
void getDungeonNodes(Dungeon **dungeon, EnemeyDataBase **enemeyDatabase); 
Dungeon *loadDungeon(Database **DB, int dungeonId);

Direction getDirections(DungeonNode *dungeonNode);

#endif