#include "Headers/getFile.h"
#include "Headers/jsonChecker.h"
#include "Headers/parser.h"

int main(int argc, char *argv[]){

    // check if argument was provided
    if(argc < 2){
        printf("Must have a .json file argument");
        return 1;
    }

    // Check if argument has json extension
    if(!checkFile(argv[1])){
        printf(" Argument must have a json file extension");
        return 1;
    }

    // puts the file contents into a buffer to read from
    char *jsonFile = getJsonFile(argv[1]);

    // Send to lexer to start parsing
    Parser parser = { 0, jsonFile, jsonFile[0]};
    ObjectArray *myObj = searchMode(&parser);

    printObj(myObj->objects[0]);
    printObj(myObj->objects[1]);
    printObj(myObj->objects[2]);
    printObj(myObj->objects[3]);
    printObj(myObj->objects[4]);
    printObj(myObj->objects[5]);
    printObj(myObj->objects[6]);
    printObj(myObj->objects[7]);
    printObj(myObj->objects[8]);
    printObj(myObj->objects[9]);
    
    return 0;
}