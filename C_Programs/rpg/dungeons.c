#include "Headers/dungeons.h"
#include "Headers/dungeonMenus.h"
#include "Headers/stringHelpers.h"
#include <stdlib.h>

DungeonReturns dungeonEntrance(GameState **gameState, int dungeonId){
    Dungeon *dungeon = loadDungeon(dungeonId);

    while(true){
        char userInput[3];
        clearScreen();

        printf("\n");
        printf("\n");
        printf(" ======== ENTERING %s ========\n", toUpper(dungeon->dungeonName));
        printf("\n");
        printf("\n");
        printf(" [ 1 ] Exit        [ 2 ] Continue\n");
        printf(": ");

        fgets(userInput, sizeof(userInput), stdin);
        if(!clearBuffer((int)sizeof(userInput) ,userInput)){
            continue;
        }

        clearScreen();
        switch(*userInput){
            case '1':
                return EXIT;
            break;
            case '2':
                return enterDungeon(&(*gameState)->player, dungeon->dungeonName, dungeon->entrance);
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

DungeonReturns enterDungeon(Player **player, char *dungeonName, DungeonNode *dungeonNode){
    dungeonHeader(dungeonName);
    charFiller(3, '\n');
    printf("You enter a %s", dungeonNode->description);
    charFiller(3, '\n');
    playerStats((*player)->health, (*player)->maxHealth, (*player)->mana, (*player)->maxMana);
    charFiller(3, '\n');

    char *enemiesStrArr[dungeonNode->enemiesCount];
    for(int i = 0; i < dungeonNode->enemiesCount; i++){
        Enemy *currEnemy = dungeonNode->enemies->enemies[i];

        enemiesStrArr[i] = currEnemy->name;
    }
    printEnemies(dungeonNode->enemiesCount, enemiesStrArr);

    charFiller(16, '-');

    char *options[] = {"Fight", "Inventory", "Inspect Room", "Move", "Run"};
    int optionsLength = sizeof(options) / 8;
    char userInput = playerOptions(optionsLength, options);

    switch(userInput){
        case '5':
            return RAN;
        break;
    }
}