#include "Headers/menus.h"
#include "Headers/fileHandle.h"
#include "Headers/jsonHeaders/structs.h"
#include "Headers/stringHelpers.h"

int startingMenu(){
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
                return 1;
            break;
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

void classMenu(Player *player){
    ObjectArray *classData = classDataBase();
    Object *barabarian = getObject(classData, "Barbarian");
    Object *mage = getObject(classData, "Mage");
    Object *assassin = getObject(classData, "Assassin");
    while(true){
        char userInput[3];

        clearScreen();
        printf("\n");
        printf("\n");
        printf(" ======== Pick Your Class ========");
        printf("\n");
        printf("[1]Barbarian        [2]Mage        [3]Assassin");
        printf("\n");
        printf(" Enter the coorosponding number to learn mmore about the class");

        fgets(userInput, sizeof(userInput), stdin);
        if(!clearBuffer((int)sizeof(userInput),userInput)){
            continue;
        }
        switch(*userInput){
            case '1':
                
        }


    }
}

void displayClassInfo(Object *classObj){
    clearScreen();
    printf("\n");
    printf("\n");
    printf(" [ %s ]\n", classObj->objName);
    printf("\n");
    printf(" [ Health ]: %d", getMember(ObjectArray *objArray, char *objcName, char *key))
    printf(" [ Health ]: %d")
    printf(" [ Health ]: %d")
    printf(" [ Health ]: %d")
    printf("\n");
    printf(" [ Health ]: %d")
}