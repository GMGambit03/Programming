#include "Headers/combatDisplay.h"
#include "Headers/dialogue.h"
#include "Headers/entityStructs.h"
#include "Headers/itemHelper.h"
#include "Headers/stringHelpers.h"
#include "Headers/fileHandle.h"
#include <stdio.h>

void combatHeaderDisplay(){
    int filler = 30;
    int nameLength = strlen("COMBAT");
    int center = (filler - nameLength) / 2;

    printf(" ");
    charFiller(30, '=');
    printf("\n");
    charFiller(center, ' ');
    printf("COMBAT");
    printf("\n");
    printf(" ");
    charFiller(30, '=');
    charFiller(1, '\n');
    printf(" You are in combat!");
    charFiller(1, '\n');
}

void playerDisplay(Player *player, ItemDatabase **itemDataBase){
    generalHeaderDisplay("PLAYER", '-', 30);
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

    generalHeaderDisplay("ENEMIES", '-', 30);

    for(int i = 0; i < (*enemies)->enemiesCount; i++){
        Enemy *currEnemy = (*enemies)->enemies[i];
        if(currEnemy->isDead){
            printf(" [ %d ] [ %s ](Dead)", (i + 1), currEnemy->name);
        }else{printf(" [ %d ] [ %s ]", (i + 1), currEnemy->name);}
        printf("\n");
        printf("       [ HP ]: %.2lf", currEnemy->health);
        charFiller(1, '\n');
    }
}

void lootEnemyDisplay(Player **player, EnemyDataBase **enemies, ItemDatabase *itemDB){
    while(true){
        clearScreen();
        char userInput[3];
        generalHeaderDisplay("LOOT", '-', 30);
    
        for(int i = 0; i < (*enemies)->enemiesCount; i++){
            Enemy *curr = (*enemies)->enemies[i];
            if(curr->isDead == false){
                continue;
            }

            if(curr->dropCount == 0){
                printf(" [ Empty ] [ %d ]  [ %s ]", (i + 1), curr->name);
            }else{
                printf(" [ Loot ] [ %d ]  [ %s ]", (i + 1), curr->name);
            }
            charFiller(1, '\n');
        }
        printf(" [ A ] Loot All");
        charFiller(1, '\n');
        printf(" [ 0 ] Exit");
        charFiller(1, '\n');
        printf(" < ");

        fgets(userInput, sizeof(userInput), stdin);
        if(!clearBuffer((int)sizeof(userInput) ,userInput)){
            continue;
        }

        // Turn the userinput into and actual integer so we can match it the the actionOptions Array
        int userInt = *userInput - '0';

        // First we'll check they entered A before we validate the numbers
        if(*userInput == 'A'){
            // we loop through each enemy inside of enemies
            // then go into another loop for each enemy we try to add all the item drops
            for(int i = 0; i < (*enemies)->enemiesCount; i++){
                Enemy *curr = (*enemies)->enemies[i];
                // We check if the enemy has already been looted
                if(curr->dropCount == 0){
                    continue;
                }
                for(int i = 0; i <= curr->dropCount; i++){
                    // if the addItem return anything other then zero that means the player can carry it and itll just loop again
                    if(addItem((*player), getItemById(itemDB, (curr->drop[i]))) == 0){
                        removeDrop(&curr, curr->drop[i]);
                    }else{
                        printf("Couldnt additem");
                        getchar();
                        break;
                    }
                }
                continue;
            }
            continue;
        }

        // we'll first check if the user entered 0 to exit 
        // just incase the the dropcount is null or itemarray is null
        if(userInt == 0){
            return;
        }

        // input check to see if its in range of the options
        if(userInt < 0 || userInt > (*enemies)->enemiesCount){
            validOption();
            enterContinue();
            getchar();
            continue;
        }
        displayLoot(player, (*enemies)->enemies[userInt - 1], itemDB);
    }
}

void displayLoot(Player **player, Enemy *enemy, ItemDatabase *itemDB){

    while(true){
        clearScreen();
        generalHeaderDisplay("LOOT", '=', 30);
        printf(" %s", enemy->name);
        charFiller(1, '\n');
    
        // create space for itemarray
            ItemArray *itemArray = malloc(sizeof(ItemArray));
            itemArray->itemsCount = enemy->dropCount;
        
            // Create space for the items in the item array
            // for each item in the inventory get the id and and get the data of the item using getitembyid function
            itemArray->items = malloc(sizeof(Item *) * itemArray->itemsCount);
            for(int i = 0; i < itemArray->itemsCount; i++){
                Item *currItem = getItemById(itemDB, enemy->drop[i]);
                currItem->quantity = 1;
                itemArray->items[i] = currItem;
            }
    
        lootHeader((*player), itemArray);

        // Next we're going to get the user input for all the items
        char userInput[3];
    
        fgets(userInput, sizeof(userInput), stdin);
        if(!clearBuffer((int)sizeof(userInput) ,userInput)){
            free(itemArray);
            continue;
        }

        // They choose A were going to get all the items and put it in theyre inventory if they can carry it
        if(*userInput == 'A'){
            // check if the enemy has already been looted
            if(enemy->dropCount == 0){
                printf(" [ Enemy already looted ]");
                charFiller(1, '\n');
                enterContinue();
                getchar();
            }

            for(int i = 0; i <= enemy->dropCount; i++){
                // if the addItem return anything other then zero that means the player can carry it and itll just loop again
                if(addItem((*player), getItemById(itemDB, (enemy->drop[i]))) == 0){
                    removeDrop(&enemy, enemy->drop[i]);
                }else{
                    // Basically an erro has occured
                    printf("Error: Couldnt additem at display loot. [Option] A");
                    getchar();
                    break;
                }
            }
            continue;
        }

        // Put userinput into a integer format and we can get what enemy the player chose
        int userInt = *userInput - '0';

        // we'll first check if the user entered 0 to exit 
        // just incase the the dropcount is null or itemarray is null
        if(userInt == 0){
            return;
        }

        if(userInt < 0 || userInt > enemy->dropCount){
            free(itemArray);
            validOption();
            enterContinue();
            getchar();
            continue;
        }

        // we then try to add the item 
        // if the we cant then the additem function will let us know
        if(addItem((*player), getItemById(itemDB, (enemy->drop[userInt - 1]))) == 0){
            clearScreen();
            removeDrop(&enemy, enemy->drop[userInt - 1]);
            printf(" Item taken succesfully");
        }
        continue;

    }

}

void lootHeader(Player *player, ItemArray *items){
    charFiller(60, '-');
    printf("\n");
    printf("%-4s %-25s %-5s %-10s\n","#", "ITEM", "QTY", "WEIGHT");
    charFiller(60, '-');
    charFiller(1, '\n');

    if(items != NULL){
        for(int i = 0; i < items->itemsCount; i++){
            Item *currItem = items->items[i];
            printf("%-4d %-25s %-5d %-20.2lf", (i + 1), currItem->itemName, items->items[i]->quantity, currItem->weight);
            printf("\n");
        }
        charFiller(60, '-');
        charFiller(1, '\n');
    }

    printf(" Inventory Weight: %.2lf / %.2lf", player->inventory->currWeight, player->inventory->weightCap);
    charFiller(1, '\n');
    printf(" [ # ] SELECT ITEM");
    printf("\n");
    printf(" [ A ] TAKE ALL");
    charFiller(1, '\n');
    printf(" [ 0 ] BACK");
    charFiller(1, '\n');
    printf(" >");
}

void actionsDisplay(int optionsCount, ActionOptions options[], bool canRun){
    generalHeaderDisplay("ACTIONS", '-', 30);

    // int optionsLength = canRun == true ? sizeof(*strOptions)/4 : (sizeof(*strOptions) - 1);

    for(int i = 0; i < optionsCount; i++){
            printf(" [%d] %s\n", (i + 1), options[i].name);
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
            printf(" [ %d ]  %s(DEAD)     HP:  %.2lf", (i + 1), curr->name, curr->health);
        }else{printf(" [ %d ]  %s     HP:  %.2lf", (i + 1), curr->name, curr->health);}
        charFiller(1, '\n');
    }
    printf("\n");

    printf(" [ 0 ]  Back");
    charFiller(1, '\n');

    printf(">");
}