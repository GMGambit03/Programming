#ifndef COMBATDISPLAY
#define COMBATDISPLAY

#include "entityStructs.h"
#include "itemHelper.h"

typedef struct Player Player;
typedef struct EnemyDataBase EnemyDataBase;
typedef struct ItemDatabase ItemDatabase;
typedef struct ItemArray ItemArray;

typedef enum{
    ATTACK,
    USEITEM,
    RUNATT,
    LOOT
}ACTIONS;

typedef struct ActionOptions{
    char *name;
    ACTIONS option; 
}ActionOptions;

void combatHeaderDisplay();
void generalHeaderDisplay(char *print, char character, int filler);
void lootHeader(Player *player, ItemArray *items);

void playerDisplay(Player *player, ItemDatabase **itemDataBase);
void enemyDisplay(EnemyDataBase **enemies);

void lootEnemyDisplay(Player **player, EnemyDataBase **enemies, ItemDatabase *itemDB);
void displayLoot(Player **player, Enemy *enemy, ItemDatabase *itemDB);

void actionsDisplay(int optionsCount, ActionOptions options[], bool canRun);
void selTargetDisplay(EnemyDataBase *enemies);


#endif