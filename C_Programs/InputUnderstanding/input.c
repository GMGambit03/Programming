#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getString(){
    char *file = "\"Hello\"";  
    int size = 0;
    int cursor = 1;
    int curPtr = cursor;
    char token;

    while((token = file[curPtr]) != '"'){
        size++;
        curPtr++;
    }

    char *string = malloc(size + 1);

    memcpy(string, &file[cursor], size);
    string[size] = '\0';
    

    return string;

}

double getNumber(){
    char *getnumber = " 4567.87";
    char *end;

    double result = strtod(getnumber, &end);

    end -= 1;
    printf("%c", *end);
    return result;
}

int main(){

    printf("%lf", getNumber());
    // =============================
    //char *myString = getString();
    //printf("%s", myString);
    // =============================

    // ================================================================
    // char userChar[3];
    // // char hello[6];
    // char *userString = NULL;
    // //char userSTringSet[10];

    // fgets(userChar, sizeof(userChar), stdin);
    
    // printf("userChar: %c\n", userChar[0]);
    // if(userChar[1] == '\n'){
    //     printf("We found it");
    // }
    // else{
    //     printf("We didnt");
    // }

    // scanf(userString, "For userString");
    // printf("%s", userString);
    // ================================================================

    return 0;
}