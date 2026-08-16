#ifndef DUNGEONMENUS
#define DUNGEONMENUS

#include "stringHelpers.h"
#include "dialogue.h"

typedef enum{
    EXIT,
    RUNAWAY,
    DIED,
    BOSSDEFEATED,
    FIGHT,
    LEAVE,
    INVENTORY,
    MOVE,
    SEARCHROOM, 
    ENEMEYDEFEATED
}DungeonReturns;

void dungeonHeader(char *dungeonName);
void playerStats(int health, int maxHealth, int mana, int maxMana);
void printEnemies(int s ,char *enimies[s]);
char playerOptions(int s, char *options[s], DungeonReturns *retOptions);
#endif
