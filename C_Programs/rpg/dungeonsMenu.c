#include "Headers/dungeonMenus.h"

void dungeonHeader(char *dungeonName){
    int filler = 16;
    int nameLength = strlen(dungeonName);
    int center = (filler - nameLength) / 2;

    charFiller(16, '=');
    printf("\n");
    printf("\n");
    charFiller(center, ' ');
    printf("%s", dungeonName);
    printf("\n");
    printf("\n");
    charFiller(16, '=');
}

void playerStats(int health, int maxHealth, int mana, int maxMana){
    printf(" Health: %d / %d", health, maxHealth);
    printf("\n");
    printf(" Mana: %d / %d", mana, maxMana);
}

void printEnemies(int s, char *enimies[s]){
    printf(" Enemies in room:");
    printf("\n");
    for(int i = 0; i < s; i++){
        char *currEnemy = enimies[i];
        printf("    %s\n", currEnemy);
    }
}