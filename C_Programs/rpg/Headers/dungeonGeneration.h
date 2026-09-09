#ifndef DUNGGEN
#define DUNGGEN

#include "entityStructs.h"

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

    bool visited;
}DungeonNode;

typedef struct Dungeon{
    int dungeonId;
    char *dungeonName;

    char *description;
    char **roomDescs;
    int roomDescLength;

    DungeonNode *entrance;
    DungeonNode *bossRoom;

    int roomsCompleted;

    int *possibleEnemies;
    int possEnemyCount;

    int minEnemyCnt;
    int maxEnemyCnt;

    int minRooms;
    int maxRooms;

    int dungeonBossId;
}Dungeon;

typedef struct QueueEntry{
    DungeonNode *room;
    Direction parent;
    struct QueueEntry *next;
}QueueEntry;

typedef struct{
    QueueEntry *front;
    QueueEntry *rear;
}Queue;

void enqueue(Queue *queue, DungeonNode *room, Direction parent);
QueueEntry *dequeue(Queue *queue);

Dungeon *createDungeon(Object *dungeonData);
void getDungeonNodes(Dungeon **dungeon, EnemyDataBase **enemyDatabase); 
DungeonNode *createDungeonNode(int roomCount, Dungeon **dungeon, EnemyDataBase **enemyDatabase);
DungeonNode *createRoom(Dungeon **dungeon, EnemyDataBase **enemyDatabase);
DungeonNode  *createBossRoom(Dungeon **dungeon, EnemyDataBase **enemyDatabase);
void test(DungeonNode *root, int *count, int *depth, char* direction);

#endif