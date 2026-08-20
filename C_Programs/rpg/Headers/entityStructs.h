#ifndef ENTITYSTRUCTS
#define ENTITYSTRUCTS

#include <stdio.h>
#include "itemHelper.h"
#include "dice.h"
#include "locationMgr.h"

typedef struct EnemyDataBase EnemyDataBase;
typedef struct ClassDatabase ClassDatabase;

typedef struct Classes{
    int iD;
    char *className;
    char *description;
    double hP;
    double strength;
    double speed;
    double mana;
    Inventory *inventory;

    int weapon;
    int armorSet;
}Class;

typedef struct Player{
    char *name;
    char *className;

    int level;
    int gold;

    Inventory *inventory;

    double maxHealth;
    double health;

    double AC;

    double maxStrength;
    double strength;

    double maxSpeed;
    double speed;

    double mana;
    double maxMana;

    int armorSet;
    int weapon;
}Player;

typedef struct Enemy{
    int iD;
    char *name;

    int *loot;
    int lootCount;

    double health;
    double strength;
    double speed;
    double AC;

    int weapon;
    int armor;

    bool isDead;

}Enemy;

typedef struct{
    Player *player;

    int currLocation;

    int *locationsUnlocked;
    int locoUnlockedSize;
    
    int *dungeonsCompleted;
    int *mainQuestsCompleted;
    // int sideQuestsCompleted;
    int *artifacts;

    bool introCompletion;
    // int archsCompleted;
}GameState;

Player *newPlayerInfo(Class *classData);
Class *createClass(Object *classData);
Class *findClass(ClassDatabase *classDataBase, int classId);
Enemy *createEnemy(Object *currEnemyData);
EnemyDataBase *getRanEnemies(int *possEnemies, int possEnemyCount, int enemyCount, EnemyDataBase **enemyDatabase);
Enemy *getEnemyById(int enemyId, EnemyDataBase **enemyDatabase);

void displayInventory(Player **player);

#endif