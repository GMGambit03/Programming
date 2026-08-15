#include "Headers/gameLoop.h"
#include "Headers/stringHelpers.h"

Player *newGameIntro(){
    // Loading assets, eventuallly turn this into a single function
    ClassDatabase *classDataBase = createClassDataBase();
    ItemDatabase *itemDataBase = createItemDatabase();

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

                Player *player = classMenu(classDataBase);
                player->name = newSaveMenu();

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

    }
}