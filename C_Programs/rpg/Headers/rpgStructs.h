#ifndef STRUCTS
#define STRUCTS

#include <stdio.h>

#include "jsonHeaders/structs.h"
#include "dice.h"

typedef enum{
    WEAPON,
    ARMOR,
    POTION,
    UTILITY
}ITEMTYPE;

typedef enum{
    NOEFFECT,
    HEAL,
    RESTOREMANA,
    STRINCREASE,
    DAMAGE,
    DEFENSE,
    RUN
}EFFECTTYPE;

typedef struct{
    int itemId;
    char *itemName;

    EFFECTTYPE effectType;
    ITEMTYPE itemIype;

    bool stackable;
    double weight;
    double value;
    double effect;
}Item;

typedef struct{
    char *name;
    char *className;

    int level;
    int gold;

    Item *inventory;

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