#include "Headers/dungeons.h"
#include "Headers/dialogue.h"
#include "Headers/dungeonMenus.h"
#include "Headers/entityStructs.h"
#include "Headers/fileHandle.h"
#include "Headers/stringHelpers.h"
#include "Headers/combat.h"
#include <stdio.h>

Dungeon *createDungeon(Object *dungeonData){
    Dungeon *dungeonStruct = malloc(sizeof(Dungeon));

    dungeonStruct->dungeonId = getMember(dungeonData, "iD")->value.data.number;
    dungeonStruct->dungeonName = getMember(dungeonData, "Name")->value.data.string;
    dungeonStruct->description = getMember(dungeonData, "Description")->value.data.string;

    // Getting array for possibleEnemies
    JsonArray *dungeonEnemiesArr = getMember(dungeonData, "PossibleEnemies")->value.data.array;
    dungeonStruct->possibleEnemies = getIntArr(dungeonEnemiesArr, &dungeonStruct->possEnemyCount); 

    dungeonStruct->minEnemyCnt = getMember(dungeonData, "MinEnemyCount")->value.data.number;
    dungeonStruct->maxEnemyCnt = getMember(dungeonData, "MaxEnemyCount")->value.data.number;

    dungeonStruct->minRooms = getMember(dungeonData, "MinRooms")->value.data.number;
    dungeonStruct->maxRooms = getMember(dungeonData, "MaxRooms")->value.data.number;

    dungeonStruct->dungeonBossId = getMember(dungeonData, "BossId")->value.data.number;

    return dungeonStruct;

}

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

DungeonNode *createDungeonNode(int roomCount, Dungeon **dungeon, int *count, Direction Parent, EnemyDataBase **enemyDatabase){
    
    // This is our recursive funtion return comparison
    // We basically stop once we reach the m=amount of room we set in getDungeonNodes
    if(*count == roomCount){
        return NULL;
    }

    // we create a tmp pointer so its easier to type everything
    Dungeon *tmp = (*dungeon);

    // ccreate space for everything we're going to add to the room
    DungeonNode *room = malloc(sizeof(DungeonNode));

    // initially set all the directions to null because not every room will have all the directions
    room->north = NULL;
    room->east = NULL;
    room->west = NULL;
    room->south = NULL;

    // we get a random enemy count between the specifc dungeons min and max enemies
    room->enemiesCount = rand() % (tmp->maxEnemyCnt - tmp->minEnemyCnt + 1) + tmp->minEnemyCnt;

    // Just to make it easier for other funtions we check if theyre any enimies even in the dungeon
    if(room->enemiesCount == 0){
        room->enemiesDead = true;
    }else{
        room->enemiesDead = false;
    }

    // we then based on the different enimies the dungeon can have we randomly add them to the room
    room->enemies = getRanEnemies(tmp->possibleEnemies, tmp->possEnemyCount, room->enemiesCount, enemyDatabase);

    // eventually we'll have different descriptions for each room
    room->description = "We dont got anything";
    
    // if the number of rooms count is 1 then its the first room which we will add to be the entrance\
    // if the room count is the max then the room is set to be the boss room
    *count += 1;
    if(*count == 1){
        (*dungeon)->entrance = room;
    }else if(*count == roomCount){
        (*dungeon)->bossRoom = room;
    }

    // makeing an array of the different directions we can have
    Direction direction[4] = {NORTH, EAST, SOUTH, WEST};
    int dirSize = sizeof(direction)/sizeof(*direction);

    // we first check if this is child of another room if so we create space for one less direction array
    Direction *direct;
    if(Parent != NONE){
        Direction *tmp = malloc(sizeof(Direction) * 3);
        direct = tmp;
    }else{
        Direction *tmp = malloc(sizeof(Direction) * 4);
        direct = tmp;
    }
    // we then fill up the new direction array with all the valid directions
    int y = 0;
    int newDirSize = 0;
    for(int i = 0; i < dirSize; i++){
        if(Parent != direction[i]){
            direct[y] = direction[i];
            newDirSize++;
            y++;
        }
    }

     int dirCnt = 0;
     // The formula is (rand() % (max - min + 1)) + min
    // we then use rand to get rand number of different rooms you can go inside of the actual room
    // If we have 2 or less rooms those rooms will have the option between 1 and 3 options
    if(*count <= 3){
        int min = 2;
        dirCnt = newDirSize == dirSize ? (rand() % (dirSize - min + 1)) + min : (rand() % (newDirSize - min + 1)) + min;
    }else{
        // if we have moree then its between 0 and 2
        int min = 1;
        dirCnt = newDirSize == dirSize ? (rand() % (dirSize - min + 1)) + min : (rand() % (newDirSize - min + 1)) + min;
    }

    // Shuffle the directions so we can just go in a for loop and get the hoever many we randomed for
    for(int i = newDirSize - 1; i > 0; i--){
        int ranNum = rand() % (i + 1);

        Direction curr = direct[i];
        Direction swap = direct[ranNum];

        direct[i] = swap;
        direct[ranNum] = curr;
    }

    for(int i = 0; i < dirCnt; i++){
        // we create next room equal to our shuffled array starting at 0 and going until it maxes out
        Direction nxtRoom = direct[i];
        Direction childParent;
        // based on nxtRoom which is the direction we then set the parent for the next room so it knows where this room is
        // if the parent room is just the opistite direction of nxtRoom
        switch (nxtRoom) {
            case NORTH:
                childParent = SOUTH;
                room->north = createDungeonNode(roomCount, dungeon, count, childParent, enemyDatabase);
                if(room->north != NULL){
                    room->north->south = room;
                }
            break;
            case WEST:
                childParent = EAST;
                room->west = createDungeonNode(roomCount, dungeon, count, childParent, enemyDatabase);
                if(room->west != NULL){
                    room->west->east = room;
                }
            break;
            case SOUTH:
                childParent = NORTH;
                room->south = createDungeonNode(roomCount, dungeon, count, childParent, enemyDatabase);
                if(room->south != NULL){
                    room->south->north = room;
                }
            break;
            case EAST:
                childParent = WEST;
                room->east = createDungeonNode(roomCount, dungeon, count, childParent, enemyDatabase);
                if(room->east != NULL){
                    room->east->west = room;
                }                
            break;
            default:
            break;
        }

    }
    free(direct);
    return room;
}

void getDungeonNodes(Dungeon **dungeon, EnemyDataBase **enemyDatabase){

    // this function we just get the max room count and set the dungeon entrance
    // And we declare the count here because in get nodes each child can change the value and it wouldnt be random
    int roomCount = (rand() + (*dungeon)->minRooms) % (*dungeon)->maxRooms + 1;
    int count = 0;
    (*dungeon)->entrance = createDungeonNode(roomCount, dungeon, &count, NONE, enemyDatabase);
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
        printf(" [ 1 ] Exit        [ 2 ] Continue");

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
                return EXIT;
            break;
            case '2':
                return enterDungeon(&(*gameState)->player, dungeon->dungeonName, dungeon->entrance, DB);
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
        charFiller(16, '-');
        charFiller(1, '\n');

        // we're making the options char and Dungeonreturs so we can match the player input to the actual enum easier
        // same for main options
        char *strEnemyOptions[] = {"Fight", "Inventory", "Run"};
        DungeonReturns retEnemyOptions[] = {FIGHT, INVENTORY, RUNAWAY};

        char *strMainOptions[] = {"Move", "Search Room", "Inventory", "Leave Dungeon"};
        DungeonReturns retMainOptions[] = {MOVE, SEARCHROOM, INVENTORY, LEAVE};

        DungeonReturns userInput;
        // we first check if all the enemies are dead if they are we cand display main options
        // if they arent dead we display fighting options
        if(!dungeonNode->enemiesDead && dungeonNode->enemiesCount > 0){
            userInput = playerOptions(sizeof(strEnemyOptions)/8, strEnemyOptions, retEnemyOptions);
        }else{
            userInput = playerOptions(sizeof(strMainOptions)/8, strMainOptions, retMainOptions);
        }
        
        Direction moveTo;
        DungeonReturns enemiesDefeated;
        // we choose based on the user input
        switch(userInput){
            case FIGHT:
                // this is where the fight actually happens
                enemiesDefeated = fightMenu(player, &dungeonNode->enemies, DB);

                // This checks if the enemies were deafted and they wernt then that means the player either ran or died
                if(enemiesDefeated != ENEMEYDEFEATED){
                    return enemiesDefeated;
                }
                dungeonNode->enemiesDead = true;
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
                        return enterDungeon(player, dungeonName, dungeonNode->north, DB);
                    break;
                    case WEST:
                        return enterDungeon(player, dungeonName, dungeonNode->west, DB);
                    break;
                    case EAST:
                        return enterDungeon(player, dungeonName, dungeonNode->east, DB);
                    break;
                    case SOUTH:
                        return enterDungeon(player, dungeonName, dungeonNode->south, DB);
                    break;
                    default:
                    break;
                }
            break;
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