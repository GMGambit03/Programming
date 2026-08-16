#include "Headers/entityStructs.h"
#include "Headers/itemHelper.h"
#include "Headers/jsonHeaders/structs.h"

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

    inventory->items = malloc(sizeof(Item) * inventory->capacity);

    Node *tmp = inventoryData->subObjs;
    for(int i = 0; i < inventory->count; i++){
        inventory->items[i].itemId = tmp->value.data.number;
        inventory->items[i].quantity = 0;
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

    Roll goldRoll = {D4, 10, 0};
    
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
    player->strength = classData->strength;
    player->maxStrength = player->strength;

    player->inventory = classData->inventory;

    return player;
    
}


Enemey *createEnemey(Object *currEnemeyData){
    Enemey *enemey = malloc(sizeof(Enemey));

    enemey->iD = getMember(currEnemeyData, "ID")->value.data.number;
    enemey->name = getMember(currEnemeyData, "Name")->value.data.string;
    
    JsonArray *lootArr = getMember(currEnemeyData, "Loot")->value.data.array;
    int count = 0;
    enemey->loot = getIntArr(lootArr, &count);
    enemey->lootCount = count;

    enemey->health = getMember(currEnemeyData, "Health")->value.data.number;
    enemey->speed = getMember(currEnemeyData, "Speed")->value.data.number;
    enemey->strength = getMember(currEnemeyData, "Strength")->value.data.number;

    enemey->weapon = getMember(currEnemeyData, "Weapon")->value.data.number;

    return enemey;
}
