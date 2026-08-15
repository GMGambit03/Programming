#include "Headers/getFile.h"
#include "Headers/parser.h"
#include "Headers/structs.h"

int main(){
    char *fileName = "classes.json";

    char *jsonFile = getJsonFile(fileName);

    Parser parser = {0,0, jsonFile, jsonFile[0]};

    ObjectArray *myObj = searchMode(&parser);
    Object *barbarian = getObject(myObj, "Barbarian");

    Member *enemies = getMember(barbarian, "PossibleEnemies");
    
    JsonArray *array = enemies->value.data.array;
    int arrayCount = 0;
    int *intArr = getIntArr(array, &arrayCount);
    printf("%d", arrayCount);
    

    
}