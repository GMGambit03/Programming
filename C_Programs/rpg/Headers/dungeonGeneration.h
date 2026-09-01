#ifndef DUNGGEN
#define DUNGGEN

#include "entityStructs.h"

typedef struct QueueEntry{
    DungeonNode *room;
    Direction parent;
    struct QueueEntry *next;
}QueueEntry;

typedef struct{
    QueueEntry *front;
    QueueEntry *rear;
}Queue;

typedef enum{
    NORTH,
    WEST,
    EAST,
    SOUTH,
    NONE
}Direction;

typedef struct DungeonNode{
    EnemyDataBase *enemies;
    int enemiesCount;
    bool enemiesDead;

    char *description;

    struct DungeonNode *north;
    struct DungeonNode *east;
    struct DungeonNode *south;
    struct DungeonNode *west;

    bool isBossRoom;
    bool isEntrance;
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

void enqueue(Queue *queue, DungeonNode *room, Direction parent);
QueueEntry *dequeue(Queue *queue);

Dungeon *createDungeon(Object *dungeonData);
DungeonNode *createDungeonNode(int roomCount, Dungeon **dungeon, int *count, Direction parent, EnemyDataBase **enemyDatabase);
void getDungeonNodes(Dungeon **dungeon, EnemyDataBase **enemyDatabase); 

#endif