#ifndef ENTITYSTRUCTS
#define ENTITYSTRUCTS

#include <stdio.h>
#include "itemHelper.h"
#include "dice.h"
#include "locationMgr.h"

typedef struct EnemeyDataBase EnemeyDataBase;
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

    double maxStrength;
    double strength;

    double maxSpeed;
    double speed;

    double mana;
    double maxMana;

    int armorSet;
    int weapon;
}Player;

typedef struct Enemey{
    int iD;
    char *name;

    int *loot;
    int lootCount;

    double health;
    double strength;
    double speed;

    int weapon;
    int armor;

    bool isDead;

}Enemey;

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
Enemey *createEnemey(Object *currEnemeyData);
EnemeyDataBase *getRanEnemies(int *possEnemies, int possEnemeyCount, int enemeyCount, EnemeyDataBase **enemeyDatabase);
Enemey *getEnemeyById(int enemeyId, EnemeyDataBase **enemeyDatabase);

void displayInventory(Player **player);

#endif