#include "lexer.h"

char lexer(char **file, int *cursor){

    while(true){
        *cursor += 1;
        char token = (*file)[*cursor];
        // we want scan every letter when we run into "{" we want to acivly continue and check until we found the string.
        if(token == ' ' || token == '\n'){
            continue;
        }

        return token;
        
    }
}