#include "Headers/fileHandle.h"

ObjectArray *classDataBase(){
    char *fileName = "classes.json";

    char *jsonFile = getJsonFile(fileName);

    Parser parser = {0, jsonFile, jsonFile[0]};
    ObjectArray *classesData = searchMode(&parser);

    return classesData;
}
