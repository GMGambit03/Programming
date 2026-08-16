#include "Headers/fileHandle.h"
#include "Headers/dungeons.h"
#include "Headers/entityStructs.h"


ItemDatabase *createItemDB(){
    char *itemDBName = "dataJson/items.json";
    char *jsonFile = getJsonFile(itemDBName);
    
    Parser parser = {0, 0, jsonFile, jsonFile[0]};
    ObjectArray *itemsData = searchMode(&parser);
    
    ItemDatabase *itemDB = malloc(sizeof(ItemDatabase));
    itemDB->count = getObjectCount(itemsData);
    itemDB->items = malloc(sizeof(Item) * itemDB->count);
    
    for(int i = 0; i < itemDB->count; i++){
        Object *currItemData = itemsData->objects[i];
        Item *item = createItem(currItemData);
        
        itemDB->items[i] = item;
    }
    return itemDB;
}

// Change this later so you load classDB struct like the itemDB instead of just objects
ClassDatabase *createClassDB(){
    char *fileName = "dataJson/classes.json";

    char *jsonFile = getJsonFile(fileName);

    Parser parser = {0, 0, jsonFile, jsonFile[0]};
    ObjectArray *classesData = searchMode(&parser);

    ClassDatabase *classDB = malloc(sizeof(ClassDatabase));
    classDB->count = getObjectCount(classesData);
    classDB->classes = malloc(sizeof(Class) * classDB->count);

    for(int i = 0; i < classDB->count; i++){
        Object *currClassData = classesData->objects[i];
        Class *currClass = createClass(currClassData);

        classDB->classes[i] = currClass;
    }

    return classDB;
}

DungeonDatabase *createDungeonDB(){
    char *fileName = "dataJson/dungeons.json";
    char *jsonFile = getJsonFile(fileName);

    Parser parser = {0, 0, jsonFile, jsonFile[0]};
    ObjectArray *dungeonsData = searchMode(&parser);

    DungeonDatabase *dungeonDB = malloc(sizeof(DungeonDatabase));
    dungeonDB->size = getObjectCount(dungeonsData);
    dungeonDB->dungeons = malloc(sizeof(Dungeon) * dungeonDB->size);

    for(int i = 0; i < dungeonDB->size; i++){
        Object *currDungeonData = dungeonsData->objects[i];
        Dungeon *currDungeon = createDungeon(currDungeonData);

        dungeonDB->dungeons[i] = currDungeon;
    }

    return dungeonDB;
}

EnemeyDataBase *createEnemeyDB(){
    char *fileName = "dataJson/enemies.json";
    char *jsonFile = getJsonFile(fileName);

    Parser parser = {0, 0, jsonFile, jsonFile[0]};
    ObjectArray *enemiesData = searchMode(&parser);

    EnemeyDataBase *enemeyDB = malloc(sizeof(DungeonDatabase));
    enemeyDB->enemiesCount = getObjectCount(enemiesData);
    enemeyDB->enemies = malloc(sizeof(Dungeon) * enemeyDB->enemiesCount);

    for(int i = 0; i < enemeyDB->enemiesCount; i++){
        Object *currEnemeyData = enemiesData->objects[i];
        Enemey *currEnemey = createEnemey(currEnemeyData);

        enemeyDB->enemies[i] = currEnemey;
    }

    return enemeyDB;
}