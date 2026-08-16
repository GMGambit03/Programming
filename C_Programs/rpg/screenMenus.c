#include "Headers/screenMenus.h"

int startMenu(){
    srand(time(NULL));
    while(true){
        char userInput[3];
        Player player;

        clearScreen();

        printf("\n");
        printf("\n");

        printf(" ==== Welcome to IDK at the moment ====");
        printf("\n");
        printf("\n");
        printf("           [ 1 ][ New Game ]");
        printf("\n");
        printf("           [ 2 ][ Load Game ]");
        printf("\n: ");

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
        printf("\n");
        printf(" Player Name: ");

        fgets(userInput, sizeof(userInput), stdin);
        int inputLength = (int)strlen(userInput);
        if(!checkName(inputLength + 1,userInput)){
            continue;
        }

        userInput[inputLength - 1] = '\0';
        
        return userInput;
    }
}

Player *classMenu(ClassDatabase *classDataBase){
    Player *player = malloc(sizeof(Player));

    Class *barbarian = findClass(classDataBase, 11);
    Class *mage = findClass(classDataBase, 12);
    Class *assassin = findClass(classDataBase, 13);

    while(true){
        char userInput[3];
        int chosenClass;

        clearScreen();
        printf("\n");
        printf("\n");
        printf("       ======== Pick Your Class ========");
        printf("\n");
        printf(" [1]Barbarian        [2]Mage        [3]Assassin");
        printf("\n");
        printf("\n");
        printf("\n");
        printf(" Enter the coorosponding number to learn mmore about the class: ");

        fgets(userInput, sizeof(userInput), stdin);
        if(!clearBuffer((int)sizeof(userInput),userInput)){
            continue;
        }
        switch(*userInput){
            case '1':
                chosenClass = displayClassInfo(barbarian);
            break;
            case '2':
                chosenClass = displayClassInfo(mage);
            break;
            case '3':
                chosenClass = displayClassInfo(assassin);
            break;
        }

        switch (chosenClass) {
            case 1:
                if(*userInput == '1'){
                    player = newPlayerInfo(barbarian);
                }
                else if(*userInput == '2'){
                    player = newPlayerInfo(mage);
                }else{
                    player = newPlayerInfo(assassin);
                }
            break;
            default:
            break;
        }

        if(chosenClass == 1){
            return player;
        }
    }
}

int displayClassInfo(Class *classData){
    while(true){
        clearScreen();
        char userInput[3];
    
        printf("\n");
        printf("\n");
        printf(" [ %s ]\n", classData->className);
        printf("\n");
        printf(" [ Health ]: %.2lf",classData->hP);
        printf("\n");
        printf(" [ Strength ]: %.2lf",classData->strength);
        printf("\n");
        printf(" [ Speed ]: %.2lf", classData->speed);
        printf("\n");
        printf(" [ Mana ]: %.2lf", classData->mana);
        printf("\n");
        printf("\n");
        printf(" [ Description ]: %s", classData->description);
        printf("\n");
        printf("\n");
        printf(" [ 1 ] Choose the %s Class        [ 2 ] Exit", classData->className);
        printf("\n: ");
    
        fgets(userInput, sizeof(userInput), stdin);
        if(!clearBuffer((int)sizeof(userInput),userInput)){
            continue;
        }
        switch(*userInput){
            case '1':
                return 1;
            break;
            case '2':
                return 2;
            break;
            default:
                printf(" [ Please Enter valid number ]");
                getchar();
            break;
        }
    }
}