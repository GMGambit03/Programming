#ifndef ENTITYSTRUCTS
#define ENTITYSTRUCTS

#include <stdio.h>

#include "itemHelper.h"
#include "dice.h"
#include "locationMgr.h"

typedef struct{
    int iD;
    char *className;
    char *description;
    double hP;
    double strength;
    double speed;
    double mana;
    Inventory *inventory;
}Class;

typedef struct{
    Class **classes;
    int count;
}ClassDatabase;

typedef struct{
    char *name;
    char *className;

    int level;
    int gold;

    Inventory *inventory;

    double maxHealth;
    double health;

    double maxStrength;
    double strength;

    double maxSpeed;
    double speed;

    double mana;
    double maxMana;


}Player;

typedef struct{
    int iD;
    char *name;

    int *loot;
    int lootCount;

    double health;
    double strength;
    double speed;

    int weapon;

}Enemy;

typedef struct{
    Enemy **enemies;
    int enemiesCount;
}EnemyArray;

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

#endif