#include "helpers.h"

// clear the stdin file or the overflows
char* clearInputBuffer(char bufferStr[])
{
    if(strchr(bufferStr, '\n') == NULL){
        int i;
        while((i = getchar()) != '\n' && (i == EOF));
    }

    bufferStr[strcspn(bufferStr, "\n")] = '\0';

    return bufferStr;
}

// clears the screen
void clearScreen() {
    // \e[1;1H moves cursor to row 1, column 1
    // \e[2J clears the entire screen
    printf("\e[1;1H\e[2J");
}
