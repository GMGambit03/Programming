#include "Headers/combatDisplay.h"
#include "Headers/itemHelper.h"
#include "Headers/stringHelpers.h"
#include "Headers/fileHandle.h"
#include <stdio.h>

void combatHeaderDisplay(){
    int filler = 16;
    int nameLength = strlen("COMBAT");
    int center = (filler - nameLength) / 2;

    printf(" ");
    charFiller(16, '=');
    printf("\n");
    charFiller(center, ' ');
    printf("COMBAT");
    printf("\n");
    printf(" ");
    charFiller(16, '=');
    charFiller(1, '\n');
    printf(" You are in combat!");
    charFiller(1, '\n');
}

void playerDisplay(Player *player, ItemDatabase **itemDataBase){
    generalHeaderDisplay("PLAYER", '-', 16);
    printf(" [ %s ] - [ %s ]", player->name, player->className);
    printf("\n");
    printf(" [ HP ]:    [ %.2lf / %.2lf ]", player->health, player->maxHealth);
    printf("\n");
    printf(" [ Mana ]:  [ %.2lf / %.2lf ]", player->mana, player->maxMana);
    charFiller(1, '\n');
    // printf(" [ Weapon ]:    %s", getItemById((*itemDataBase), player->weapon)->itemName);
    charFiller(1, '\n');
}

void enemyDisplay(EnemyDataBase **enemies){

    generalHeaderDisplay("ENEMIES", '-', 16);

    for(int i = 0; i < (*enemies)->enemiesCount; i++){
        Enemy *currEnemy = (*enemies)->enemies[i];
        if(currEnemy->isDead){
            continue;
        }
        printf(" [ %d ] [ %s ]", (i + 1), currEnemy->name);
        printf("\n");
        printf("       [ HP ]: %.2lf", currEnemy->health);
        charFiller(1, '\n');
    }
}

void actionsDisplay(char *strOptions[], bool canRun){
    generalHeaderDisplay("ACTIONS", '-', 16);

    int optionsLength = canRun == true ? sizeof(*strOptions)/4 : (sizeof(*strOptions) - 1);

    for(int i = 0; i < optionsLength; i++){
            printf(" [%d] %s\n", (i + 1), strOptions[i]);
        }
        printf("\n: ");
}

void selTargetDisplay(EnemyDataBase *enemies){
    clearScreen();
    charFiller(1, ' ');
    charFiller(8, '=');
    printf(" SELECT TARGET ");
    charFiller(8, '=');
    charFiller(1, '\n');

    for(int i = 0; i < enemies->enemiesCount; i++){
        Enemy *curr = enemies->enemies[i];
        if(curr->isDead == true){
            continue;
        }
        printf(" [ %d ]  %s     HP:  %.2lf", (i + 1), curr->name, curr->health);
        charFiller(1, '\n');
    }
    printf("\n");

    printf(" [ 0 ]  Back");
    charFiller(1, '\n');

    printf(">");
}