#include "Headers/fileHandle.h"
#include "Headers/rpgStructs.h"


ItemDatabase *createItemDatabase(){
    char *itemDatabaseName = "dataJson/items.json";
    char *jsonFile = getJsonFile(itemDatabaseName);
    
    Parser parser = {0, 0, jsonFile, jsonFile[0]};
    ObjectArray *itemsData = searchMode(&parser);
    
    ItemDatabase *itemDataBase = malloc(sizeof(ItemDatabase));
    itemDataBase->count = getObjectCount(itemsData);
    itemDataBase->items = malloc(sizeof(Item) * itemDataBase->count);
    
    for(int i = 0; i < itemDataBase->count; i++){
        Object *currItemData = itemsData->objects[i];
        Item *item = createItem(currItemData);
        
        itemDataBase->items[i] = item;
    }
    return itemDataBase;
}

// Change this later so you load classdatabase struct like the itemdatabase instead of just objects
ClassDatabase *createClassDataBase(){
    char *fileName = "dataJson/classes.json";

    char *jsonFile = getJsonFile(fileName);

    Parser parser = {0, 0, jsonFile, jsonFile[0]};
    ObjectArray *classesData = searchMode(&parser);

    ClassDatabase *classDataBase = malloc(sizeof(ClassDatabase));
    classDataBase->count = getObjectCount(classesData);
    classDataBase->classes = malloc(sizeof(Class) * classDataBase->count);

    for(int i = 0; i < classDataBase->count; i++){
        Object *currClassData = classesData->objects[i];
        Class *currClass = createClass(currClassData);

        classDataBase->classes[i] = currClass;
    }

    return classDataBase;
}