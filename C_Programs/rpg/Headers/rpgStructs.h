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

    float maxHealth;
    float health;

    float maxStrength;
    float strength;

    int speed;
    int maxSpeed;

    float mana;
    float maxMana;


}Player;

Player *assignBaseInfo(Object *classData);

#endif