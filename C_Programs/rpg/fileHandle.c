#include "Headers/fileHandle.h"
#include "Headers/dungeons.h"
#include "Headers/entityStructs.h"
#include "Headers/jsonHeaders/structs.h"


ItemDatabase *createItemDB(){
    // We make a string array of all the different item file names
    // We then get the count of the array for the actual jsonfile array
    // do not change order unless you match it to the itemtypes order in filehandle.h
    char *fileNames[] = {"dataJson/itemsJson/weapons.json", "dataJson/itemsJson/armor.json", "dataJson/itemsJson/potions.json", "dataJson/itemsJson/utilities.json", "dataJson/itemsJson/artifacts.json"};
    int jsonFileCount = sizeof(fileNames)/sizeof(fileNames)[0];

    // create space for each actual json file 
    char **jsonFile = malloc(jsonFileCount * sizeof(char *));

    // we then loop through each filename in filenames
    // and then we assign them to jsonfile at the same spot
    for(int i = 0; i < jsonFileCount; i++){
        jsonFile[i] = getJsonFile(fileNames[i]);
    }
    
    // we declare the size of itemDB so we can return it outside and input our attributes
    ItemDatabase *itemDB = malloc(sizeof(ItemDatabase));
    itemDB->itemCount = jsonFileCount;

    // We then declare the size of items array which is the sizeof the itemArray struct
    itemDB->itemsArray = malloc(sizeof(ItemArray *) * itemDB->itemCount);

    for(int i = 0; i < jsonFileCount; i++){
        // refer to jsonparser
        Parser parser = {0, 0, jsonFile[i], jsonFile[i][0]};
        ObjectArray *itemsData = searchMode(&parser);

        itemDB->itemsArray[i] = malloc(sizeof(ItemArray));
        ItemArray *currArray = itemDB->itemsArray[i];
        
        // Were going to get the how many objects the specific itemjson got
        // Then we're going to create space for the objects in the biiger itemdatabase so we can store the objects
        currArray->itemsCount = getObjectCount(itemsData);

        // We then have to create space for where the items are going
        currArray->items = malloc(sizeof(Item *) * currArray->itemsCount);
        
        // We then go into a for loop and we create each item in the currItemData using the createItem function
        for(int i = 0; i < currArray->itemsCount; i++){
            Object *currItemData = itemsData->objects[i];
            Item *item = createItem(currItemData);
            
            currArray->items[i] = item;   
        }
        // And we set our actual array equal to the tmp array we used to get everything
        itemDB->itemsArray[i] = currArray;
    }
    return itemDB;
}

// Change this later so you load classDB struct like the itemDB instead of just objects
ClassDatabase *createClassDB(){
    char *fileName = "dataJson/classes.json";

    char *jsonFile = getJsonFile(fileName);

    Parser parser = {0, 0, jsonFile, jsonFile[0]};
    ObjectArray *classesData = searchMode(&parser);

    // We just create space for the items inside the database
    // Then we get count of objects and create space for where the classes are going
    ClassDatabase *classDB = malloc(sizeof(ClassDatabase));
    classDB->count = getObjectCount(classesData);
    classDB->classes = malloc(sizeof(Class) * classDB->count);

    // we then go into the for loop and get all the classes using the createClass function
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

    // create space for the dungeondatabase then create space for the objects in the dungeondatabase
    DungeonDatabase *dungeonDB = malloc(sizeof(DungeonDatabase));
    dungeonDB->size = getObjectCount(dungeonsData);
    dungeonDB->dungeons = malloc(sizeof(Dungeon) * dungeonDB->size);

    // Go into a forloop and create each dungeon and put it into the dungeondatabase using the createDungeon function
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

    // Create space for the enemey database then create space for the enemies to go inside the enemey database
    EnemyDataBase *enemyDB = malloc(sizeof(DungeonDatabase));
    enemyDB->enemiesCount = getObjectCount(enemiesData);
    enemyDB->enemies = malloc(sizeof(Dungeon) * enemyDB->enemiesCount);

    // Go into a forloop and create each eneyem and put them inside of the enemeydatabse using createEnemy function
    for(int i = 0; i < enemyDB->enemiesCount; i++){
        Object *currEnemyData = enemiesData->objects[i];
        Enemy *currEnemy = createEnemy(currEnemyData);

        enemyDB->enemies[i] = currEnemy;
    }

    return enemyDB;
}

Database *createDB(){
    // Create space for all the different databases
    Database *DB = malloc(sizeof(Database));
    
    // Assign the different databases to its respective variable
    DB->classDB = createClassDB();
    DB->dungeonDB = createDungeonDB();
    DB->enemyDB = createEnemyDB();
    DB->itemDB = createItemDB();
    return DB;
}