#ifndef INVENHELPER
#define INVENHELPER

#include "jsonHeaders/structs.h"

typedef enum{
    WEAPON,
    ARMOR,
    POTION,
    UTILITY
}ITEMTYPE;

typedef enum{
    NOEFFECT,
    HEAL,
    RESTOREMANA,
    STRINCREASE,
    DAMAGE,
    DEFENSE,
    RUN
}EFFECTTYPE;

typedef struct{
    int itemId;
    char *itemName;

    EFFECTTYPE effectType;
    ITEMTYPE itemIype;

    bool stackable;
    double weight;
    double value;
    double effect;


}Item;

typedef struct{
    Item **items;
    int count;
}ItemDatabase;

typedef struct{
    int itemId;
    int quantity;
}InventorySlot;

typedef struct{
    InventorySlot *items;

    int count;
    int capacity;

    double currWeight;
    double weightCap;
}Inventory;

double getInventoryCount(Node *inventory);
double getInventoryWeight(Node *inventory);
void getInventoryItems(Inventory **inventory, Node *items);
Item *createItem(Object *itemData);
ITEMTYPE getItemType(char *type);
EFFECTTYPE getEffectType(char *type);

#endif