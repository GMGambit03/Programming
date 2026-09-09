#include "Headers/dungeons.h"
#include "Headers/dialogue.h"
#include "Headers/dungeonMenus.h"
#include "Headers/entityStructs.h"
#include "Headers/fileHandle.h"
#include "Headers/stringHelpers.h"
#include "Headers/combat.h"
#include <stdio.h>

Dungeon *loadDungeon(Database **DB, int dungeonId){
    // searches through dungeon database to find which specific dungeon we're looking for then returns it
    for(int i = 0; i < (*DB)->dungeonDB->size; i++){
        Dungeon *currDungeon = (*DB)->dungeonDB->dungeons[i];
        if(currDungeon->dungeonId == dungeonId){
            getDungeonNodes(&currDungeon, &(*DB)->enemyDB);
            return currDungeon;
        }
    }
    return NULL;
}

DungeonReturns dungeonEntrance(GameState **gameState, Database **DB, int dungeonId){
    // we first load the dungeon refer to loaddungeon function
    Dungeon *dungeon = loadDungeon(DB, dungeonId);

    while(true){
        char userInput[3];
        clearScreen();

        printf("\n");
        printf("\n");
        printf("  ======== ENTERING %s ========", toUpper(dungeon->dungeonName));
        printf("\n");
        printf("\n");
        
        //Gets Center
        int nameLength = strlen(dungeon->dungeonName);
        charFiller(((32 + (nameLength - 2)) - 34) / 2, ' ');
        printf(" [ 1 ] Continue        [ 2 ] Exit");

        printf("\n");
        printf("\n");
        printf(": ");

        fgets(userInput, sizeof(userInput), stdin);
        if(!clearBuffer((int)sizeof(userInput) ,userInput)){
            continue;
        }

        // based on userinput we can either exit or enter the dungeon
        clearScreen();
        switch(*userInput){
            case '1':
                return enterDungeon(&(*gameState)->player, dungeon->dungeonName, dungeon->entrance, DB);
            break;
            case '2':
                return EXIT;
            break;
            default:
                printf("\n");
                printf("\n");
                validOption();
                getchar();
            break;
        }
    }

}

DungeonReturns enterDungeon(Player **player, char *dungeonName, DungeonNode *dungeonNode, Database **DB){
    // refer to dungeonMenus for all displays and prints
    bool dungeonCompleted = false;
    int roomsCompleted = 0;
    while(true){
        clearScreen();
        dungeonHeader(dungeonName);
        charFiller(1, '\n');
        printf(" You enter a %s", dungeonNode->description);
        charFiller(1, '\n');
        playerStats((*player)->health, (*player)->maxHealth, (*player)->mana, (*player)->maxMana);
        charFiller(1, '\n');

        // we just make an of the enemies names so we can then display them on screen
        char *enemiesStrArr[dungeonNode->enemiesCount];
        for(int i = 0; i < dungeonNode->enemiesCount; i++){
            Enemy *currEnemy = dungeonNode->enemies->enemies[i];

            enemiesStrArr[i] = currEnemy->name;
        }
        printEnemies(dungeonNode->enemiesCount, enemiesStrArr);
        charFiller(1, '\n');
        charFiller(30, '-');
        charFiller(1, '\n');

        // we're making the options char and Dungeonreturs so we can match the player input to the actual enum easier
        // same for main options
        DungeonOptions enemyOptions[] = {
            {"Fight", FIGHT},
            {"Inventory", INVENTORY},
            {"Run", RUNAWAY}
        };
        int enemyOptionsSize = sizeof(enemyOptions)/sizeof(enemyOptions[0]);

        DungeonOptions mainOptions[] = {
            {"Move", MOVE},
            {"Search Room", SEARCHROOM},
            {"Inventory", INVENTORY},
            {"Leave Dungeon", LEAVE}
        };
        int mainOptionsSize = sizeof(mainOptions)/sizeof(mainOptions[0]);

        DungeonReturns userInput;
        // we first check if all the enemies are dead if they are we cand display main options
        // if they arent dead we display fighting options
        if(!dungeonNode->enemiesDead && dungeonNode->enemiesCount > 0){
            userInput = playerOptions(enemyOptionsSize, enemyOptions);
        }else{
            userInput = playerOptions(mainOptionsSize, mainOptions);
        }
        
        Direction moveTo;
        DungeonReturns enemiesDefeated;
        // we choose based on the user input
        switch(userInput){
            case FIGHT:
                // this is where the fight actually happens
                enemiesDefeated = fightMenu(player, &dungeonNode->enemies, DB);

                // This checks if the enemies were deafted and they wernt then that means the player either ran or died
                if(enemiesDefeated == DIED || enemiesDefeated == RUNAWAY){
                    return enemiesDefeated;
                }else if(enemiesDefeated == ENEMEYDEFEATED && dungeonNode->isBossRoom){
                    dungeonCompleted = true;
                }
                dungeonNode->enemiesDead = true;
                roomsCompleted++;

            break;
            case INVENTORY:
                // refer to displayinventory
                displayInventoryItems((*player), (*DB)->itemDB);
            break;
            case MOVE:
                // getdirections just displays the valid directions to the player
                // Then returns what the player chose
                moveTo = getDirections(dungeonNode);
                switch (moveTo) {
                    case NORTH:
                        if(dungeonNode->north == NULL){
                            printf(" [ You run into the wall like a mad man ]\n");
                            enterContinue();
                            getchar();
                        }else{
                            return enterDungeon(player, dungeonName, dungeonNode->north, DB);
                        }
                    break;
                    case WEST:
                        if(dungeonNode->west == NULL){
                            printf(" [ You run into the wall like a mad man ]\n");
                            enterContinue();
                            getchar();
                        }else{
                            return enterDungeon(player, dungeonName, dungeonNode->west, DB);
                        }
                    break;
                    case EAST:
                        if(dungeonNode->east == NULL){
                            printf(" [ You run into the wall like a mad man ]\n");
                            enterContinue();
                            getchar();
                            break;
                        }else{
                            return enterDungeon(player, dungeonName, dungeonNode->east, DB);
                        }
                    break;
                    case SOUTH:
                        if(dungeonNode->south == NULL){
                            printf(" [ You run into the wall like a mad man ]\n");
                            enterContinue();
                            getchar();
                            break;
                        }else{
                            return enterDungeon(player, dungeonName, dungeonNode->south, DB);
                        }
                    break;
                    default:
                    break;
                }
            break;
            case SEARCHROOM:
                searchRoom();
            break;
            case LEAVE:
                if(dungeonCompleted){
                    return BOSSDEFEATED;
                }else{
                    return LEAVE;
                }
            default:
            break;
        }
    }
}

Direction getDirections(DungeonNode *dungeonNode){
    while(true){
        clearScreen();
        char userInput[3];
    
        // We make a directions array and char directions array so we can easily match what the player chose to an actual enum
        Direction dirOptions[4] = {NORTH, EAST, SOUTH, WEST};
        char *strDir[] = {"NORTH", "EAST", "SOUTH", "WEST"};
        int strDirLength = sizeof(strDir)/sizeof(strDir[0]);

        // refer to dungeonMenu dispklaydirections funcntoin
        displayDirections(dungeonNode, strDirLength, strDir);

        fgets(userInput, sizeof(userInput), stdin);
        if(!clearBuffer((int)sizeof(userInput) ,userInput)){
            continue;
        }

        // turn player input to int to directly use it to get the enum direction in the enum array
        int userInt = (*userInput - '0');

        // checks if the player input is valid
        if(userInt < 0 || userInt > sizeof(dirOptions)/4){
            validOption();
            enterContinue();
            getchar();
            continue;
        }else if(userInt == 0){
            return NONE;
        }
        return dirOptions[userInt - 1];
    }


}