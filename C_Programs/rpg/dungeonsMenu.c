#include "Headers/dungeonMenus.h"
#include <stdio.h>

void dungeonHeader(char *dungeonName){
    int filler = 16;
    int nameLength = strlen(dungeonName);
    int center = (filler - nameLength) / 2;

    printf(" ");
    charFiller(16, '=');
    printf("\n");
    printf("\n");
    charFiller(center, ' ');
    printf("%s", dungeonName);
    printf("\n");
    printf("\n");
    printf(" ");
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
        printf(" : [ %s ]\n", currEnemy);
    }
}

char playerOptions(int optionsLength, char *options[optionsLength], DungeonReturns *retOptions){
    while(true){
        char userInput[3];

        for(int i = 0; i < optionsLength; i++){
            printf(" [%d] %s\n", (i + 1), options[i]);
        }
        printf("\n: ");

        fgets(userInput, sizeof(userInput), stdin);
        if(!clearBuffer((int)sizeof(userInput) ,userInput)){
            continue;
        }

        int userInt = *userInput - '0';
        return retOptions[userInt - 1];


    }


}