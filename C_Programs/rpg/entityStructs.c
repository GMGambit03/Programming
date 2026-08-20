#include "Headers/entityStructs.h"
#include "Headers/itemHelper.h"
#include "Headers/jsonHeaders/structs.h"
#include "Headers/fileHandle.h"
#include <stdlib.h>

Class *createClass(Object *classData){
    Class *classStruct = malloc(sizeof(Class));

    classStruct->iD = getMember(classData, "ID")->value.data.number;
    classStruct->className = getMember(classData, "Class")->value.data.string;
    classStruct->description = getMember(classData, "Description")->value.data.string;
    classStruct->hP = getMember(classData, "Hp")->value.data.number;
    classStruct->strength = getMember(classData, "Strength")->value.data.number;
    classStruct->speed = getMember(classData, "Speed")->value.data.number;
    classStruct->mana = getMember(classData, "Mana")->value.data.number;

    Object *inventoryData =  getMember(classData, "Inventory")->value.data.obj;
    Inventory *inventory = malloc(sizeof(Inventory));
    inventory->count = getInventoryCount(inventoryData->subObjs);
    inventory->capacity = inventory->count * .50;
    inventory->weightCap = getMember(classData, "WeightCap")->value.data.number;
    inventory->currWeight = 0;
    
    inventory->items = malloc(sizeof(InventorySlot) * inventory->count);
    

    classStruct->weapon = getMember(classData, "Weapon")->value.data.number;
    classStruct->armorSet = getMember(classData, "Armor Set")->value.data.number;

    Node *tmp = inventoryData->subObjs;
    for(int i = 0; i < inventory->count; i++){
        inventory->items[i].itemId = tmp->value.data.number;
        inventory->items[i].quantity = 1;
        tmp = tmp->next;
    }

    classStruct->inventory = inventory;
    
    return classStruct;
}

Class *findClass(ClassDatabase *classDataBase, int classId){
    for(int i = 0; i < classDataBase->count; i++){
        if(classId == classDataBase->classes[i]->iD){
            return classDataBase->classes[i];
        }
    }
    return NULL;
}

Player *newPlayerInfo(Class *classData){

    Player *player = malloc(sizeof(Player));

    Roll goldRoll = {D4, 10};
    
    switch(classData->iD){
        case 1:
            goldRoll.rolls = 2;
        break;
        case 2:
            goldRoll.rolls = 3;
        break;
        case 3:
            goldRoll.rolls = 5;
            
        break;
    }

    player->level = 0;

    player->className = classData->className;
    player->level = 0;

    player->gold = rollDice(goldRoll);

    player->health = classData->hP;
    player->maxHealth = player->health;
    player->mana = classData->mana;
    player->maxMana = player->mana;

    player->speed = classData->speed;
    player->maxSpeed = player->speed;
    player->AC = player->maxSpeed + 8;

    player->strength = classData->strength;
    player->maxStrength = player->strength;

    player->inventory = classData->inventory;

    player->weapon = classData->weapon;
    player->armorSet = classData->armorSet;


    return player;
    
}

Enemy *createEnemy(Object *currEnemyData){
    Enemy *enemy = malloc(sizeof(Enemy));

    enemy->iD = getMember(currEnemyData, "ID")->value.data.number;
    enemy->name = getMember(currEnemyData, "Name")->value.data.string;
    
    JsonArray *lootArr = getMember(currEnemyData, "Loot")->value.data.array;
    int count = 0;
    enemy->loot = getIntArr(lootArr, &count);
    enemy->lootCount = count;

    enemy->health = getMember(currEnemyData, "Health")->value.data.number;

    enemy->speed = getMember(currEnemyData, "Speed")->value.data.number;
    enemy->AC = enemy->speed + 8;

    enemy->strength = getMember(currEnemyData, "Strength")->value.data.number;

    enemy->weapon = getMember(currEnemyData, "Weapon")->value.data.number;
    enemy->armor = getMember(currEnemyData, "Armor")->value.data.number;

    return enemy;
}

EnemyDataBase *getRanEnemies(int *possEnemies, int possEnemyCount, int enemyCount, EnemyDataBase **enemyDatabase){
    EnemyDataBase *enemies = malloc(sizeof(EnemyDataBase));
    enemies->enemiesCount = enemyCount;
    enemies->enemies = malloc(sizeof(Enemy) * enemies->enemiesCount);
    
    for(int i = enemyCount - 1; i >= 0; i--){
        int ranNum = rand() % (i + 1);

        int curr = possEnemies[i];
        int swap = possEnemies[ranNum];

        possEnemies[i] = swap;
        possEnemies[ranNum] = curr;
        
        enemies->enemies[i] = getEnemyById(possEnemies[i], enemyDatabase);
    }

    return enemies;
}

Enemy *getEnemyById(int enemyId, EnemyDataBase **enemyDatabase){
    Enemy *enemy = malloc(sizeof(Enemy));

    enemy->iD = enemyId;
    for(int i = 0; i < (*enemyDatabase)->enemiesCount; i++){
        Enemy *curr = (*enemyDatabase)->enemies[i];
        curr->isDead = false;
        if(enemyId == curr->iD){
            enemy->health = curr->health;
            enemy->loot = curr->loot;
            enemy->lootCount = curr->lootCount;
            enemy->name = curr->name;
            enemy->speed = curr->speed;
            enemy->strength = curr->strength;
            enemy->weapon = curr->weapon;
            enemy->armor = curr->armor;
            enemy->AC = curr->AC;
            return enemy;
        }
    }
    return NULL;
}
