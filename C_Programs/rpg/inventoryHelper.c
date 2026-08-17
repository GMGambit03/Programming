#include "Headers/itemHelper.h"
#include "Headers/fileHandle.h"
#include <time.h>

// void getInventoryItems(Inventory **inventory ,Node *items){
//     Node *tmp = items;

//     while(tmp != NULL){
        
//     }
// }

double getInventoryCount(Node *inventory){
    double count = 0;

    Node *tmp = inventory;

    while(tmp != NULL){
        count++;
        tmp = tmp->next;
    }
    return count;
}

// double getInventoryWeight(Node *inventory){
//     double weight = 0;


//     return weight;
// }

Item *createItem(Object *itemData){
    Item *item = malloc(sizeof(Item));

    item->itemId = getMember(itemData, "itemId")->value.data.number;
    item->itemIype = getItemType(getMember(itemData, "type")->value.data.string);
    item->effectType = getEffectType(getMember(itemData, "effectType")->value.data.string);
    item->effect = getMember(itemData, "effect")->value.data.number;
    item->itemName = getMember(itemData, "itemName")->value.data.string;
    item->value = getMember(itemData, "value")->value.data.number;
    item->stackable = getMember(itemData, "stackable")->value.data.boolean;
    item->weight = getMember(itemData, "weight")->value.data.number;

    // not all items have a multiplier
    if(item->itemId >= 1000 && item->itemId < 4000){
        item->multiplier = getMember(itemData, "multiplier")->value.data.number;
    }else{
        item->multiplier = 0;
    }

    return item;
}

ITEMTYPE getItemType(char *type){
    ITEMTYPE itemType;

    // Eventually we dont want it hardcoded but thats a change for the future
    char *strTypesArr[] = {"WEAPON", "ARMOR", "POTION", "UTILITY"};
    ITEMTYPE typesArr[] = {WEAPON, ARMOR, POTION, UTILITY};

    for(int i = 0; i < (int)sizeof(strTypesArr)/8; i++){
        int compare = strcmp(strTypesArr[i], type);

        if(compare == 0){
            itemType = typesArr[i];
            break;
        }
    }

    return itemType;
}

EFFECTTYPE getEffectType(char *type){
    EFFECTTYPE effectType;

    EFFECTTYPE typesArr[] = {NOEFFECT, HEAL, RESTOREMANA, STRINCREASE, DAMAGE, DEFENSE, RUN};
    char *strTypesArr[] = {"NONE", "HEAL", "RESTOREMANA", "STRINCREASE", "DAMAGE", "DEFENSE", "RUN"};

    for(int i = 0; i < (int)sizeof(strTypesArr)/8; i++){
        int compare = strcmp(strTypesArr[i], type);

        if(compare == 0){
            effectType = typesArr[i];
            break;
        }
    }

    return effectType;
}

Item *getItemById(ItemDatabase *itemDataBase, int id){
    for(int i = 0; i < itemDataBase->count; i++){
        Item *currItem = itemDataBase->items[i];

        if(currItem->itemId == id){
            return currItem;
        }
    }
    return NULL;
}

double applyArmor(double damage, int armorId, ItemDatabase *itemDB){
    damage *= getItemById(itemDB, armorId)->multiplier;
    return damage;
}
void applyWeapon(double *currDamage, int weaponId, ItemDatabase *itemDB){
    Item *weapon = getItemById(itemDB, weaponId);
    *currDamage += (weapon->effect * weapon->multiplier);
}
