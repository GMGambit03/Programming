#include "Headers/getFile.h"
#include "Headers/parser.h"
#include "Headers/structs.h"
#include <stdio.h>

int main(){
    char *fileName = "classes.json";

    char *jsonFile = getJsonFile(fileName);

    Parser parser = {0,0, jsonFile, jsonFile[0]};

    ObjectArray *myObj = searchMode(&parser);
    Object *fungalHusk = getObject(myObj, "UnderDark Marauder");
    JsonArray *items = getMember(fungalHusk, "Loot")->value.data.array;
    

    
}