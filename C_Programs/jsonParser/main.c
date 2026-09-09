#include "Headers/getFile.h"
#include "Headers/parser.h"
#include "Headers/structs.h"

int main(){
    char *fileName = "classes.json";

    char *jsonFile = getJsonFile(fileName);

    Parser parser = {0,0, jsonFile, jsonFile[0]};

    ObjectArray *myObj = searchMode(&parser);
    Object *rat = getObject(myObj , "Hollow Rat");

    printObj(rat);

    JsonArray *descriptions = getMember(rat, "RoomDescriptions")->value.data.array;

    for(int i = 0; i < descriptions->count; i++){
        char *string = descriptions->values[i].data.string;
        printf("%s ->\n", string);
    }

    
}