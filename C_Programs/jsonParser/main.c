#include "Headers/getFile.h"
#include "Headers/parser.h"
#include "Headers/structs.h"
#include <stdio.h>

int main(){
    char *fileName = "classes.json";

    char *jsonFile = getJsonFile(fileName);

    Parser parser = {0,0, jsonFile, jsonFile[0]};

    ObjectArray *myObj = searchMode(&parser);
    Object *fungalHusk = getObject(myObj , "Fungal Husk");
    JsonArray *items = getMember(fungalHusk, "Loot")->value.data.array;

    Object *first = items->values[0].data.obj;
    Object *second = items->values[1].data.obj;
    
    printf("Hello: %lf -> YOOO: %lf\n", getMember(first, "Hello")->value.data.number, getMember(first, "YOOO")->value.data.number);
    printf("PlsWork: %s -> Yoursmart %s", getMember(second, "PlsWork")->value.data.string, getMember(second, "Yoursmart")->value.data.string);

    
}