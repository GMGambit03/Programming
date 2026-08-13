#include "Headers/stringHelpers.h"

void clearScreen(){
    printf("\033[H\033[2J");
    fflush(stdout);
}

bool clearBuffer(int s ,char userInput[s]){
    bool validInput = true;
    if(userInput[s - 2] != '\n'){
        validInput = false;
        printf("Please put in a valid input");
        getchar();
    }
    int ch;
    while((ch = getchar()) != EOF){
        continue;
    }
    return validInput;
}

bool checkChars(char *userInput){
    int s = strlen(userInput);

    for(int i = 0; i < s; i++){
        char curr = userInput[i];
        if(curr >= 'a' && curr <= 'z'){
            continue;
        }
        else if(curr >= 'A' && curr <= 'Z'){
            continue;
        }
        else{
            return false;
        }
    }
    return true;
}

bool checkFirstDigit(char *userInput){

    if(userInput[0] >= '0' && userInput[0] <= '9'){
        return true;
    }
    return false;
}

bool checkName(int s, char userInput[s]){
    bool isValid = false;
    if(!clearBuffer(s, userInput)){
        return isValid;
    }
    else if(!checkChars(userInput) && !checkFirstDigit(userInput)){
        return isValid;
    }
    return true;
}