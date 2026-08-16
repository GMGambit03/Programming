#ifndef FILES
#define FILES

#include "itemHelper.h"
#include "jsonHeaders/jsonChecker.h"
#include "jsonHeaders/getFile.h"
#include "jsonHeaders/parser.h"

#include "dungeons.h"
#include "entityStructs.h"

typedef struct Enemey Enemey;
typedef struct Dungeon Dungeon;
typedef struct Player Player;

typedef struct EnemeyDataBase{
    Enemey **enemies;
    int enemiesCount;
}EnemeyDataBase;

typedef struct ClassDatabase{
    Class **classes;
    int count;
}ClassDatabase;

typedef struct DungeonDatabase{
    Dungeon **dungeons;
    int size;
}DungeonDatabase;

typedef struct ItemDatabase{
    Item **items;
    int count;
}ItemDatabase;

typedef struct Database{
    ClassDatabase *classDB;
    ItemDatabase *itemDB;
    DungeonDatabase *dungeonDB;
    EnemeyDataBase *enemeyDB;
}Database;

void getPlayerData(Player *playerData);
ClassDatabase *createClassDB();
ItemDatabase *createItemDB();
DungeonDatabase *createDungeonDB();
EnemeyDataBase *createEnemeyDB();
Database *createDB();

Class *createClass(Object *classData);

#endif