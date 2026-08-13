#include "Headers/gameLoop.h"
#include "Headers/menus.h"

Player newGameIntro(){
    Player player;

    char *dialogOptions[] = {"I'll go take a look", "What exactly is the \"seal?\"", "Why me?"};
    int optionsLength = sizeof(dialogOptions) / sizeof(dialogOptions[0]);

    while(true){
        clearScreen();

        char userInput[3];


        printf("");
        printf("");

        printf(" You wake up to shouting outside. The village square is full of lantern light and worried faces. ");
        printf(" The Elder stands at the well's edge. The water inside has turned black");
        printf("\n");
        printf("\n");
        printf(" **Elder**: The seal is failing. There's a passage east of here that wasn't open yesterday. It is now.");
        printf("\n");
        for(int i = 0; i < optionsLength; i++){
            printf("[ %d ]: %s\n", i + 1, dialogOptions[i]);
        }

        if(!clearBuffer((int)sizeof(userInput) ,userInput)){
            continue;
        }

        switch (userInput[0]) {
            case '1':
                printf("\n");
                printf("\n");

                printf(" **Elder**: Good, before you go what's your name and class");
                player.name = newSaveMenu();
                

        }




    }
}