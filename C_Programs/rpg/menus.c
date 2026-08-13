#include "Headers/menus.h"
#include "Headers/gameLoop.h"
#include "Headers/stringHelpers.h"
#include <stdbool.h>
#include <stdio.h>

Player startingMenu(){
    while(true){
        char userInput[3];
        Player player;

        clearScreen();

        printf("");
        printf("");

        printf(" ==== Welcome to IDK at the moment ====");
        printf("\n");
        printf(" [ 1 ][ New Game ]");
        printf(" [ 2 ][ Load Game ]");

        fgets(userInput, sizeof(userInput), stdin);
        if(!clearBuffer((int)sizeof(userInput),userInput)){
            continue;
        }
        switch (userInput[0]) {
            case '1':
                player = newGameIntro();
        }
    }
}

char *newSaveMenu(){
    while(true){
        char *userInput = malloc(22 * sizeof(char));

        clearScreen();

        printf("\n");
        printf("\n");
        printf(" ==== IDK ====");
        printf(" Player Name: ");

        fgets(userInput, sizeof(userInput), stdin);

        if(!checkName((int)sizeof(userInput),userInput)){
            continue;
        }

        return userInput;
    }
}