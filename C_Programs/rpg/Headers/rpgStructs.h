#ifndef STRUCTS
#define STRUCTS

#include <stdio.h>

#include "jsonHeaders/structs.h"
#include "dice.h"

typedef struct{
    int itemId;
    char *itemName;
}item;

typedef struct{
    char *name;
    char *className;

    int level;
    int gold;

    item *inventory;

    double maxHealth;
    double health;

    double maxStrength;
    double strength;

    double speed;
    double maxSpeed;

    double mana;
    double maxMana;


}Player;

Player *assignBaseInfo(Object *classData);

#endif