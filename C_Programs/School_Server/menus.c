#include "Headers/menus.h"


void clearScreen(){
    printf("\033[2J\033[1;1H");
    fflush(stdout); 
}

void clearInputBuffer(){
    int ch;

    while((ch = getchar()) != '\n' && ch != EOF);
}

bool inputChecker(int numInputs, char *userInput){
    bool noGo = false;
    for(int i = 1; i <= numInputs; i++){
        if((char)(i + '0') != userInput[0]){
            noGo = false;
        }
        else {
            noGo = true;
            return noGo;
        }
    }
    return noGo;
}

char *startMenu(){

    while(true){
        clearScreen();
        char userInput[3];

        printf("\n [ ==== Welcome to Pineforest School Database ==== ]");
        printf("\n [ What would you like to do ]\n");
        printf(" [1] Edit Classes\n");
        printf(" [2] View Classes\n");
        printf(" [3] View Teachers\n");
        printf(" [4] View Students\n");

        fgets(userInput, sizeof(userInput), stdin);

        if(strchr(userInput, '\n') == NULL || !inputChecker(4, userInput)){
            clearInputBuffer();
            printf(" [ Please enter a valid input ] %c", userInput[0]);
            getchar();
            continue;
        }

        switch (userInput[0]) {
            case '1':
            // Edit classes manu
                continue;
            break;
            case '2':
            // send server VIEW_CLASSES
            return "VIEW_CLASSES";
        }
        

    }
}