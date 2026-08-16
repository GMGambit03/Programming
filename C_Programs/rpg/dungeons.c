#include "Headers/dungeons.h"
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
    for(int i = 0; i < (*DB)->dungeonDB->size; i++){
        Dungeon *currDungeon = (*DB)->dungeonDB->dungeons[i];
        if(currDungeon->dungeonId == dungeonId){
            getDungeonNodes(&currDungeon, &(*DB)->enemeyDB);
            return currDungeon;
        }
    }
    return NULL;
}

DungeonNode *createDungeonNode(int roomCount, Dungeon **dungeon, int *count, Direction Parent, EnemeyDataBase **enemeyDatabase){
    
    if(*count == roomCount){
        return NULL;
    }

    Dungeon *tmp = (*dungeon);

    DungeonNode *room = malloc(sizeof(DungeonNode));

    room->north = NULL;
    room->east = NULL;
    room->west = NULL;
    room->south = NULL;
    room->enemiesCount = rand() % (tmp->maxEnemyCnt - tmp->minEnemyCnt + 1) + tmp->minEnemyCnt;
    if(room->enemiesCount == 0){
        room->enemiesDead = true;
    }else{
        room->enemiesDead = false;
    }
    room->enemies = getRanEnemies(tmp->possibleEnemies, tmp->possEnemyCount, room->enemiesCount, enemeyDatabase);
    room->description = "We dont got anything";
    
    *count += 1;
    if(*count == 1){
        (*dungeon)->entrance = room;
    }else if(*count == roomCount){
        (*dungeon)->bossRoom = room;
    }

    Direction direction[4] = {NORTH, EAST, SOUTH, WEST};
    int dirSize = sizeof(direction)/sizeof(*direction);

    Direction *direct;
    if(Parent != NONE){
        Direction *tmp = malloc(sizeof(Direction) * 3);
        direct = tmp;
    }else{
        Direction *tmp = malloc(sizeof(Direction) * 4);
        direct = tmp;
    }
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
    // If we have 2 or less rooms those rooms will have the option between 1 and 3 options
    if(*count <= 2){
        int min = 1;
        dirCnt = newDirSize == dirSize ? (rand() % (dirSize - min + 1)) + min : (rand() % (newDirSize - min + 1)) + min;
    }else{
        // if we have moree then its between 0 and 2
        int min = 0;
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

    // Set the next direction to this function again and when it returns
    for(int i = 0; i < dirCnt; i++){
        Direction nxtRoom = direct[i];
        Direction childParent;
        switch (nxtRoom) {
            case NORTH:
                childParent = SOUTH;
                room->north = createDungeonNode(roomCount, dungeon, count, childParent, enemeyDatabase);
                if(room->north != NULL){
                    room->north->south = room;
                }
            break;
            case WEST:
                childParent = EAST;
                room->west = createDungeonNode(roomCount, dungeon, count, childParent, enemeyDatabase);
                if(room->west != NULL){
                    room->west->east = room;
                }
            break;
            case SOUTH:
                childParent = NORTH;
                room->south = createDungeonNode(roomCount, dungeon, count, childParent, enemeyDatabase);
                if(room->south != NULL){
                    room->south->north = room;
                }
            break;
            case EAST:
                childParent = WEST;
                room->east = createDungeonNode(roomCount, dungeon, count, childParent, enemeyDatabase);
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

void getDungeonNodes(Dungeon **dungeon, EnemeyDataBase **enemeyDatabase){

    int roomCount = (rand() + (*dungeon)->minRooms) % (*dungeon)->maxRooms + 1;
    int count = 0;
    (*dungeon)->entrance = createDungeonNode(roomCount, dungeon, &count, NONE, enemeyDatabase);
}

DungeonReturns dungeonEntrance(GameState **gameState, Database **DB, int dungeonId){
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
    while(true){
        clearScreen();
        dungeonHeader(dungeonName);
        charFiller(1, '\n');
        printf(" You enter a %s", dungeonNode->description);
        charFiller(1, '\n');
        playerStats((*player)->health, (*player)->maxHealth, (*player)->mana, (*player)->maxMana);
        charFiller(1, '\n');

        
        char *enemiesStrArr[dungeonNode->enemiesCount];
        for(int i = 0; i < dungeonNode->enemiesCount; i++){
            Enemey *currEnemy = dungeonNode->enemies->enemies[i];

            enemiesStrArr[i] = currEnemy->name;
        }
        printEnemies(dungeonNode->enemiesCount, enemiesStrArr);
        charFiller(1, '\n');
        charFiller(16, '-');
        charFiller(1, '\n');

        char *strEnemeyOptions[] = {"Fight", "Inventory", "Run"};
        DungeonReturns retEnemeyOptions[] = {FIGHT, INVENTORY, RUNAWAY};

        char *strMainOptions[] = {"Move", "Search Room", "Inventory", "Leave Dungeon"};
        DungeonReturns retMainOptions[] = {MOVE, SEARCHROOM, INVENTORY, LEAVE};

        DungeonReturns userInput;
        if(!dungeonNode->enemiesDead && dungeonNode->enemiesCount > 0){
            userInput = playerOptions(sizeof(strEnemeyOptions)/8, strEnemeyOptions, retEnemeyOptions);
        }else{
            userInput = playerOptions(sizeof(strMainOptions)/8, strMainOptions, retMainOptions);
        }
        
        Direction moveTo;
        DungeonReturns enemiesDefeated;
        switch(userInput){
            case FIGHT:
                enemiesDefeated = fightMenu(player, &dungeonNode->enemies, DB);
                if(enemiesDefeated != ENEMEYDEFEATED){
                    return enemiesDefeated;
                }
                dungeonNode->enemiesDead = true;
            break;
            case INVENTORY:
                // displayInventory(player);
            break;
            case MOVE:
                // moveTo = getDirections(dungeonNode);
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
        //     // case SEARCHROOM:
        //     //     return BOSSDEFEATED;
        //     // break;
            default:
                return userInput;
            break;
        }
    }



    printf("Everything works");
    getchar();
}