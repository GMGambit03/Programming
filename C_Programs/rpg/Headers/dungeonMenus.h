#ifndef DUNGEONMENUS
#define DUNGEONMENUS

#include "stringHelpers.h"
#include "dialogue.h"

void dungeonHeader(char *dungeonName);
void playerStats(int health, int maxHealth, int mana, int maxMana);
void printEnemies(int s ,char *enimies[s]);
char playerOptions(int s, char *options[s]);
#endif
