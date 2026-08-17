#ifndef COMBATDISPLAY
#define COMBATDISPLAY

#include "entityStructs.h"
#include "itemHelper.h"

typedef struct Player Player;
typedef struct EnemyDataBase EnemyDataBase;
typedef struct ItemDatabase ItemDatabase;

typedef enum{
    ATTACK,
    USEITEM,
    RUNATT
}ACTIONS;

void combatHeaderDisplay();
void generalHeaderDisplay(char *print, char character, int filler);
void playerDisplay(Player *player, ItemDatabase **itemDataBase);
void enemyDisplay(EnemyDataBase **enemies);
void actionsDisplay(char *strOptions[], bool canRun);

void selTargetDisplay(EnemyDataBase *enemies);


#endif