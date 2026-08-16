#include "Headers/gameLoop.h"
#include "Headers/dialogue.h"
#include "Headers/dungeons.h"

GameState *newGameIntro(){
    // Loading assets, eventuallly turn this into a single function
    ClassDatabase *classDataBase = createClassDB();
    ItemDatabase *itemDataBase = createItemDB();
    DungeonDatabase *dungeonDataBase = createDungeonDB();
    GameState *gameState = malloc(sizeof(GameState));
    gameState->player = NULL;

    char *dialogOptions[] = {"I'll go take a look", "What exactly is the \"seal?\"", "Why me?"};
    int optionsLength = sizeof(dialogOptions) / sizeof(dialogOptions[0]);

    while(true){
        clearScreen();

        char userInput[3];

        printf("\n");
        printf("\n");
        printf(" You wake up to shouting outside. The village square is full of lantern light and worried faces. ");
        printf(" The Elder stands at the well's edge. The water inside has turned black");
        printf("\n");
        printf("\n");
        printf(" **Elder**: The seal is failing. There's a passage east of here that wasn't open yesterday. It is now.");
        printf("\n");
        for(int i = 0; i < optionsLength; i++){
            printf("[ %d ]: %s\n", i + 1, dialogOptions[i]);
        }
        printf(": ");

        fgets(userInput, sizeof(userInput), stdin);
        if(!clearBuffer((int)sizeof(userInput) ,userInput)){
            continue;
        }

        clearScreen();
        switch (userInput[0]) {
            case '1':
                printf("\n");
                printf("\n");
                printf(" **Elder**: Good, before you go what's your class and name\n");
                printf("\n");
                enterContinue();
                getchar();

                Player *player = classMenu(classDataBase);
                player->name = newSaveMenu();

                gameState->player = player;

                printf(" **Elder**: Nice to have you stand and cure our village.\n");
                printf(" **Elder**: Lets head to the first dungeon.\n");
            break;
            case '2':
                printf("\n");
                printf("\n");
                printf(" **Elder**: Generations ago, something tore open beneath this village\n");
                printf(" **Elder**: The Warden's Heart has kept it shut ever since.\n");
                printf(" **Elder**: Until now\n");
                printf("\n");
                printf(" [ Enter any key to continue ]");
                getchar();
            break;
            case '3':
                printf("\n");
                printf("\n");
                printf(" **Elder**: Because you're the only one standing here, and the rest of everyone else is sleep\n");
                printf("\n");
                printf(" [ Enter any key to continue ]\n");
                getchar();
            break;
            default:
                printf("\n");
                printf("\n");
                printf("[ Please enter a valid response ]");
                printf("\n");
                printf(" [ Enter any key to continue ]");
                getchar();
            break;
        }

        if(gameState->player != NULL){
            gameState->locoUnlockedSize = 4;
            gameState->locationsUnlocked = malloc(sizeof(int)*gameState->locoUnlockedSize);
            gameState->locationsUnlocked[0] = 1001;
            gameState->currLocation = gameState->locationsUnlocked[0];

            while(true){
                clearScreen();
                DungeonReturns dungeonReturn = dungeonEntrance(&gameState, &dungeonDataBase, 1001);
    
                switch(dungeonReturn){
                    case EXIT:
                        createDialogue("Elder", "Adventurer don't be scared you are mighty hero, here to save us all");
                        printf("\n");
                        enterContinue();
                        getchar();
                    break;
                    case RAN:
                        createDialogue("Elder", "Them damn fiegns almost killed you.");
                        createDialogue("Elder", "Lets go to the villiage and get you some better equipment.");
                        enterContinue();
                        getchar();
                    break;
                    case DIED:
                        createDialogue("Elder", "Truly hero we thank you for risking your life.");
                        createDialogue("Elder", "Maybe you can get the next time.");
                        createDialogue("Elder", "Lets go to the villiage and get you some better equipment.");
                    break;
                    case BOSSDEFEATED:
                        createDialogue("Elder", "I knew you were the one to call on.");
                        createDialogue("Elder", "On behalf the entire village we thank you.");
                        createDialogue("Elder", "Lets go to the villiage and get you some better equipment for the next dungeon");
                        enterContinue();
                        getchar();
                    break;
                }
                if(dungeonReturn == EXIT){
                    continue;
                }else{
                    break;
                }
            }

            return gameState;
        }

    }


}

void mainLoop(GameState gameState){
    Player *player = gameState.player;


}