#ifndef ITEMHELPER
#define ITEMHELPER

#include "dice.h"
#include "jsonHeaders/structs.h"

typedef struct ItemDatabase ItemDatabase;
typedef struct Player Player;

typedef enum{
    USE,
    EQUIP,
    DROP,
    MULTIDROP
}ITEMOPTIONS;

typedef enum{
    WEAPON,
    ARMOR,
    POTION,
    UTILITY,
    ARTIFACT
}ITEMTYPE;

typedef enum{
    RESTOREHP,
    RESTOREMANA,
    STRINCREASE,
    DAMAGE,
    DEFENSE,
    RUN,
    NOEFFECT
}EFFECTTYPE;

typedef struct{
    int itemId;
    char *itemName;

    EFFECTTYPE effectType;
    ITEMTYPE itemType;

    bool stackable;
    double weight;
    double value;
    
    union
    {
        double effect;
        double dmgReduction;
        double penetration;
    }effectData;
    union{
        Roll roll;
    }rollData;
}Item;

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
double getInventoryWeight(Inventory *inventory, ItemDatabase *itemDB);

void displayInventoryItems(Player *player, ItemDatabase *itemDB);
void displayItemData(Player *player, Item *item);

void equipItem(Player *player, Item *item);
int useItem(Player *player, Item *item);

void addItem(Player *player, int itemId);
int dropItem(Player *player, int itemId, int count);
void removeItem(Player *player, int itemId);

Item *createItem(Object *itemData);
ITEMTYPE getItemType(char *type);
EFFECTTYPE getEffectType(char *type);

Item *getItemById(ItemDatabase *itemDataBase, int id);


#endif