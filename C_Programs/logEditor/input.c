#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "headers/input.h"

// clears the screen
void clearScreen(){
    printf("\033[2J\033[H]]");
}
int inputLengthManger(char input[], int length)
{
    fgets(input, length, stdin);
    size_t len = strlen(input);

    if(len == 1){
        return 1;
    }
    if(len > 0 && input[len-1] == '\n'){
        input[len - 1] = '\0';
        return 3;
    }else{
        printf("Error: Input too long! Make it shorter... \n");
        int ch;
        while((ch = getchar()) != '\n' && ch != EOF);
        getchar();
        return 2;
    }
}
int inputManager(){
    char userInputStr[3];
    fgets(userInputStr, sizeof userInputStr, stdin);

    size_t len = strlen(userInputStr);

    if(len > 0 && userInputStr[len-1] == '\n'){
        userInputStr[len - 1] = '\0';
        if((userInputStr[0] < 48) || (userInputStr[0] >= 58 )){
            return 15;
        }
        return strtol(userInputStr, NULL, 0);
    }
    if(userInputStr[0] == '\n');
    else{
        int ch;
        while((ch = getchar()) != '\n' && ch != EOF);
        return 15;
    }
    return 15;
}
// delete the previous linethat is on screen so user doesnt see theyre input after pressing enter
void deleteLines(int lines){

    for(int i = 0; i <= lines; i++)
    {
        printf("\033[1A");
        printf("\033[2K");
        fflush(stdout); 
    }
}