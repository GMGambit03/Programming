#include "Headers/dialogue.h"
#include <stdio.h>

void createDialogue(char *who, char *print){
    
    printf(" **%s**: %s\n", who, print);
}

void enterContinue(){
    printf(" [ Enter any key to continue ]");
}

void validOption(){
    printf(" [ Please enter a valid option ]");
}