#include "Headers/dungeonMenus.h"
#include "Headers/dungeons.h"
#include "Headers/stringHelpers.h"
#include <stdio.h>
#include <time.h>

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
        printf("\n >");

        fgets(userInput, sizeof(userInput), stdin);
        if(!clearBuffer((int)sizeof(userInput) ,userInput)){
            continue;
        }

        int userInt = *userInput - '0';
        return retOptions[userInt - 1];


    }
}

void displayDirections(DungeonNode *dungeonNode, int length, char *strDir[]){
    charFiller(8, '=');
    printf(" MOVE ");
    charFiller(8, '=');
    charFiller(1, '\n');

    for(int i = 0; i < length; i++){

        if(i == 0 && dungeonNode->north == NULL) continue;
        else if(i == 1 && dungeonNode->east == NULL) continue;
        else if(i == 2 && dungeonNode->south == NULL) continue;
        else if(i == 3 && dungeonNode->west == NULL) continue;

        printf(" [ %d ] %s", (i + 1), strDir[i]);
        printf("\n");
    }
    charFiller(1, '\n');
    printf(" [ 0 ] Back");
    charFiller(1, '\n');
    printf(" >");
}