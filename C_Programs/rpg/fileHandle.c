#include "Headers/fileHandle.h"
#include "Headers/dungeons.h"
#include "Headers/entityStructs.h"


ItemDatabase *createItemDB(){
    // We make a string array of all the different item file names
    // We then get the count of the array for the actual jsonfile array
    // do not change order unless you match it to the itemtypes order in filehandle.h
    const char *fileNames[] = {"dataJson/weapons.json", "dataJson/armor.json", "dataJson/potions.json", "dataJson/utilities.json", "dataJson/artifacts.json"};
    int jsonFileCount = sizeof(fileNames)/sizeof(fileNames)[0];

    // create space for each actual json file 
    char **jsonFile = malloc(jsonFileCount * sizeof(char));

    // we then loop through each filename in filenames
    // and then we assign them to jsonfile at the same spot
    for(int i = 0; i < jsonFileCount; i++){
        jsonFile[i] = getJsonFile(fileNames[i]);
    }
    
    // we declare the size of itemDB so we can return it outside and input our attributes
    ItemDatabase *itemDB = malloc(sizeof(ItemDatabase));
    itemDB->itemCounts = malloc(sizeof(int) * jsonFileCount);
    itemDB->itemsArray = malloc(sizeof)

    for(int i = 0; i < jsonFileCount; i++){
        // refer to jsonparser
        Parser parser = {0, 0, jsonFile[i], jsonFile[i][0]};
        ObjectArray *itemsData = searchMode(&parser);
        
        itemDB->itemCounts[i] = getObjectCount(itemsData);
        i
        
        
        for(int i = 0; i < itemDB->itemCounts[i]; i++){
            Object *currItemData = itemsData->objects[i];
            Item *item = createItem(currItemData);
            
            itemDB->items[i] = item;
        }
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

EnemyDataBase *createEnemyDB(){
    char *fileName = "dataJson/enemies.json";
    char *jsonFile = getJsonFile(fileName);

    Parser parser = {0, 0, jsonFile, jsonFile[0]};
    ObjectArray *enemiesData = searchMode(&parser);

    EnemyDataBase *enemyDB = malloc(sizeof(DungeonDatabase));
    enemyDB->enemiesCount = getObjectCount(enemiesData);
    enemyDB->enemies = malloc(sizeof(Dungeon) * enemyDB->enemiesCount);

    for(int i = 0; i < enemyDB->enemiesCount; i++){
        Object *currEnemyData = enemiesData->objects[i];
        Enemy *currEnemy = createEnemy(currEnemyData);

        enemyDB->enemies[i] = currEnemy;
    }

    return enemyDB;
}

Database *createDB(){
    Database *DB = malloc(sizeof(Database));
    
    DB->classDB = createClassDB();
    DB->dungeonDB = createDungeonDB();
    DB->enemyDB = createEnemyDB();
    DB->itemDB = createItemDB();
    return DB;
}