#ifndef STRUCTS
#define STRUCTS

#include <stdio.h>

#include "inventoryHelper.h"
#include "dice.h"

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

    double speed;
    double maxSpeed;

    double mana;
    double maxMana;


}Player;

Player *newPlayerInfo(Class *classData);
// Inventory *getBaseInventory(Object *Items);

Class *createClass(Object *classData);
Class *findClass(ClassDatabase *classDataBase, int classId);

#endif