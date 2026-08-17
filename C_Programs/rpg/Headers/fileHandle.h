#ifndef FILES
#define FILES

#include "itemHelper.h"
#include "jsonHeaders/jsonChecker.h"
#include "jsonHeaders/getFile.h"
#include "jsonHeaders/parser.h"

#include "dungeons.h"
#include "entityStructs.h"

typedef struct Enemy Enemy;
typedef struct Dungeon Dungeon;
typedef struct Player Player;

typedef struct EnemyDataBase{
    Enemy **enemies;
    int enemiesCount;
}EnemyDataBase;

typedef struct ClassDatabase{
    Class **classes;
    int count;
}ClassDatabase;

typedef struct DungeonDatabase{
    Dungeon **dungeons;
    int size;
}DungeonDatabase;

typedef struct ItemDatabase{
    Item ***itemsArray;
    int *itemCounts;
}ItemDatabase;

typedef struct Database{
    ClassDatabase *classDB;
    ItemDatabase *itemDB;
    DungeonDatabase *dungeonDB;
    EnemyDataBase *enemyDB;
}Database;

void getPlayerData(Player *playerData);
ClassDatabase *createClassDB();
ItemDatabase *createItemDB();
DungeonDatabase *createDungeonDB();
EnemyDataBase *createEnemyDB();
Database *createDB();

Class *createClass(Object *classData);

#endif