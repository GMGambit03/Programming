#ifndef DUNGEONMENUS
#define DUNGEONMENUS

#include "stringHelpers.h"
#include "dialogue.h"

typedef struct DungeonNode DungeonNode;

typedef enum{
    RUNAWAY,
    EXIT,
    DIED,
    BOSSDEFEATED,
    FIGHT,
    LEAVE,
    INVENTORY,
    MOVE,
    SEARCHROOM, 
    ENEMEYDEFEATED,
}DungeonReturns;

typedef struct DungeonOptions{
    char *name;
    DungeonReturns option;
}DungeonOptions;

void dungeonHeader(char *dungeonName);
void playerStats(int health, int maxHealth, int mana, int maxMana);
void printEnemies(int s ,char *enimies[s]);
char playerOptions(int optionsLength, DungeonOptions options[optionsLength]);
void displayDirections(DungeonNode *dungeonNode, int length, char *strDir[]);
#endif


