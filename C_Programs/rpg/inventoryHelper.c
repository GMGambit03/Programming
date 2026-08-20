#include "Headers/combatDisplay.h"
#include "Headers/inventoryDisplay.h"
#include "Headers/itemHelper.h"
#include "Headers/fileHandle.h"
#include "Headers/stringHelpers.h"
#include <stdlib.h>
void displayInventoryItems(Player *player, ItemDatabase *itemDB){

    while(true){
        clearScreen();
        // Just displays inventory at the top of the terminal
        generalHeaderDisplay("Inventory", '=', 30);
    
        // Get the weight of the the entire inventory
        double inventoryWeight = getInventoryWeight(player->inventory, itemDB);
        printf(" Weight: %.2lf / %.2lf", inventoryWeight, player->inventory->weightCap);
        printf("\n");
    
        // create space for itemarray
        ItemArray *itemArray = malloc(sizeof(ItemArray));
        itemArray->itemsCount = player->inventory->count;
    
        // Create space for the items in the item array
        // for each item in the inventory get the id and and get the data of the item using getitembyid function
        itemArray->items = malloc(sizeof(Item *) * itemArray->itemsCount);
        for(int i = 0; i < itemArray->itemsCount; i++){
            Item *currItem = getItemById(itemDB, player->inventory->items[i].itemId);
            itemArray->items[i] = currItem;
        }
    
        // The using the itemheader we can display all the items 
        itemHeader(player->inventory, itemArray);
    
        // Next we're going to get the user input for all the items
        char userInput[3];
    
        fgets(userInput, sizeof(userInput), stdin);
        if(!clearBuffer((int)sizeof(userInput) ,userInput)){
            free(itemArray);
            continue;
        }

        // Put userinput into a integer format and we can get what enemy the player chose
        int userInt = *userInput - '0';
        if(userInt < 0 || userInt > player->inventory->count){
            free(itemArray);
            validOption();
            enterContinue();
            getchar();
            continue;
        }
        


        // The based on the input if the userint is 0 then we'll go back 
        if(userInt == 0){
            return;
        }

        // if its not 0 then we'll display the itemData
        displayItemData(player, itemArray->items[userInt - 1]);
    
        free(itemArray->items);
        free(itemArray);
    }
}

void displayItemData(Player *player, Item *item){
    while(true){
        clearScreen();
        // refer to inventoryDisplay for all the prints and displays
        generalHeaderDisplay(toUpper(item->itemName), '=', 30);
        charFiller(1, '\n');

        // This returns the list of options there are for the item
        int optionsSize = 0;
        ITEMOPTIONS *options = itemDisplay(item, &optionsSize);
        // We need this so we can easily compare what the user chose and corrdinate to the right option
    
        // then we'll go and get the user input
        char userInput[3];
    
        fgets(userInput, sizeof(userInput), stdin);
        if(!clearBuffer((int)sizeof(userInput) ,userInput)){
            continue;
        }
    
        // Put userinput into a integer format and we can get what option the player chose
        int userInt = *userInput - '0';
        if(userInt < 0 || userInt > optionsSize){
            validOption();
            enterContinue();
            getchar();
            continue;
        }

        // if its 0 then we;ll jsut return to go basck
        if(userInt == 0){
            return;
        }

        // we then get the option based on what the player number is since the options line up with eachother
        // depending on what the player chooses we'll go into the cooropsonf=ding function
        // refer to eadc function for more detail
        ITEMOPTIONS optionChose = options[userInt - 1];
        int dropQtc;
        switch(optionChose){
            case USE:
                // If it returns 0 that mean that item was last of what the player had
                // and were going to return to inventory menu
                if(useItem(player, item) == 0){
                    return;
                }
            break;
            case EQUIP:
                equipItem(player, item);
            break;
            case DROP:
                dropItem(player, item->itemId, 1);
            break;
            case MULTIDROP:
                dropQtc = dropQtcMenu();
                dropItem(player, item->itemId, dropQtc);
            break;
        }
    }
    
}

int useItem(Player *player, Item *item){
    // we figure out what effect the item does and then apply it
    // for the health and mana if the amount of the increase goes pass the max amount
    // we just set it to the max
    switch(item->effectType){
        case RESTOREHP:
            player->health += item->effectData.effect;
            if(player->health > player->maxHealth){
                player->health = player->maxHealth;
            }
        break;
        case RESTOREMANA:
            player->mana += item->effectData.effect;
            if(player->mana > player->maxMana){
                player->mana = player->maxMana;
            }
        break;
        case STRINCREASE:
        // For strength we make it so the the player can only invrease theyre by a maximum of 50%
            if(player->strength == player->maxStrength * 1.50){
                printf(" You cant use anymore strength potions");
                return 0;
            }
            player->strength += item->effectData.effect;
        break;
        default:
        break;
    }
    // We then drop the item
    // refer to dropItem function
    // If it returns 0 that mean that item was last of what the player had
    int anyMore = dropItem(player, item->itemId, 1);
    return anyMore;
}

void equipItem(Player *player, Item *item){
    // We first check what type of item we're equipping
    int currEquip;
    switch (item->itemType) {
        case WEAPON:
            currEquip = player->weapon;
        break;
        case ARMOR:
            currEquip = player->armorSet;
        break;
        default:
        break;
    }

    // We then check if the item is already equiped
    if(item->itemId == currEquip){
        printf(" item is already equiped");
        return;
    }
    // if its not then we equip the newitem
    player->weapon = item->itemId;
    switch (item->itemType) {
        case WEAPON:
            player->weapon = item->itemId;
        break;
        case ARMOR:
            player->armorSet = item->itemId;
        break;
        default:
        break;
    }
    // then we reomve the item from the player inventory 
    // and add the old equiped item to the inventory
    removeItem(player, item->itemId);
    addItem(player, currEquip);
}

void addItem(Player *player, int itemId){

    // We first start searching for the item to see if it already in the inventory
    // If it is we just simply increase the quantity
    for(int i = 0; i < player->inventory->count; i++){
        if(itemId == player->inventory->items[i].itemId){
            player->inventory->items[i].quantity++;
            return;
        }

        // if its not and we reach the end of the inventory 
        // we increase the count by one
        // Check if we've reach the capcity of the actual array
        // The just set the item at the end of the array
        if(i == player->inventory->count - 1){
            player->inventory->count++;
            if(player->inventory->count == player->inventory->capacity){
                player->inventory->capacity += 10;
                InventorySlot *tmp = realloc(player->inventory->items, sizeof(InventorySlot) * player->inventory->capacity);
                if(tmp != NULL){
                    player->inventory->items = tmp;
                }
            }
            player->inventory->items[i + 1].itemId = itemId;
            player->inventory->items[i + 1].quantity = 1;
            return;
        }
    }
}

void removeItem(Player *player, int itemId){
    // we search through the players inventory and basically move the item we;re trying to get rid to the end
    // We then just subtract the inventory count
    Inventory *inventory = player->inventory;
    for(int i = 0; i < inventory->count - 1; i++){
        InventorySlot currSlot = inventory->items[i];
        InventorySlot nxtSlot = inventory->items[i + 1];

        if(itemId == currSlot.itemId){
            player->inventory->items[i] = nxtSlot;
            player->inventory->items[i + 1] = currSlot;
        }
    }
    player->inventory->count--;
}

int dropItem(Player *player, int itemId, int count){
    // we go into a for loop and basically search through the array for the itemid
    for(int i = 0; i < player->inventory->count; i++){
        // When we find the item we first d=subtract the count from the quantity
        if(itemId == player->inventory->items[i].itemId){
            player->inventory->items[i].quantity -= count;
            // Then we first check if the count is greater then how much the player has
            // if its greater then we add the count back, let the plery know and return
            if(player->inventory->items[i].quantity < 0){
                player->inventory->items[i].quantity += count;
                printf(" You do not have enough to drop that much");
                return 1;
            }
            // If the quantity is eqaul to 0 meaning we dont have anymore of that item
            // We then just remove the item from the array
            // refer to removeItem function
            else if(player->inventory->items[i].quantity == 0){
                removeItem(player, itemId);
                return 0;
            }else{
                // if everything is fine we just return back to our function
                return 1;
            }
        }
    }
}

double getInventoryCount(Node *inventory){
    double count = 0;

    Node *tmp = inventory;

    while(tmp != NULL){
        count++;
        tmp = tmp->next;
    }
    return count;
}

double getInventoryWeight(Inventory *inventory, ItemDatabase *itemDB){
    double weight = 0;

    for(int i = 0; i < inventory->count; i++){
        int currItemId = inventory->items[i].itemId;

        Item *currItem = getItemById(itemDB, currItemId);
        
        weight += currItem->weight;
    }

    return weight;
}
// Creates the item based on the different objects the jsonparser gets
Item *createItem(Object *itemData){
    // Create space for the data in theitem struct
    Item *item = malloc(sizeof(Item));

    // Start filling in all the differnt attributes for the struct
    item->itemId = getMember(itemData, "itemId")->value.data.number;

    // Transforms the string the jsonparsed for item type and turns it into a ItemType enum.
    // Refer to Itemhelper header
    item->itemType = getItemType(getMember(itemData, "type")->value.data.string);

    // Transforms the string the jsonparsed for item effect type and turns it into a EffectType enum.
    // Refer to Itemhelper header
    item->effectType = getEffectType(getMember(itemData, "effectType")->value.data.string);

    item->itemName = getMember(itemData, "itemName")->value.data.string;
    item->value = getMember(itemData, "value")->value.data.number;
    item->stackable = getMember(itemData, "stackable")->value.data.boolean;
    item->weight = getMember(itemData, "weight")->value.data.number;

    // For weapons they have pentration and armor has dmg reduction
    // for weapons they also have roll attribute thats considered a object in json
    // based on type we're going to get them
    switch(item->itemType){
        case WEAPON:
            item->effectData.penetration = getMember(itemData, "penetration")->value.data.number;

            // Get the subobject diceRoll thats in itemData then based on the diceSides and roll we cn make a Roll struct
            Object *rollObj = getMember(itemData, "diceRoll")->value.data.obj;
            item->rollData.roll.diceType = getDiceType(getMember(rollObj, "diceSides")->value.data.number);
            item->rollData.roll.rolls = getMember(rollObj, "rolls")->value.data.number;
        break;
        case ARMOR:
            item->effectData.dmgReduction = getMember(itemData, "dmgReduction")->value.data.number;
        break;
        case POTION:
            item->effectData.effect = getMember(itemData, "effect")->value.data.number;
        break;
        default:
        break;
    }

    return item;
}

ITEMTYPE getItemType(char *type){
    ITEMTYPE itemType;

    // Eventually we dont want it hardcoded but thats a change for the future
    char *strTypesArr[] = {"WEAPON", "ARMOR", "POTION", "UTILITY, ARTIFACT"};
    ITEMTYPE typesArr[] = {WEAPON, ARMOR, POTION, UTILITY, ARTIFACT};

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

    EFFECTTYPE typesArr[] = {NOEFFECT, RESTOREHP, RESTOREMANA, STRINCREASE, DAMAGE, DEFENSE, RUN};
    char *strTypesArr[] = {"NONE", "RESTOREHP", "RESTOREMANA", "STRINCREASE", "DAMAGE", "DEFENSE", "RUN"};

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

    // Based on the items id we can know what type of item it is eventually we'll create hash map fro easier use
    ITEMTYPE database;
    if(id < 2000){
        database = WEAPON;
    }else if(id < 3000){
        database = ARMOR;
    }else if(id < 4000){
        database = POTION;
    }else if(id < 5000){
        database = UTILITY;
    }else{
        database = ARTIFACT;
    }

    // Then based on the is we can search for the item effectivly
    for(int i = 0; i < itemDataBase->itemsArray[database]->itemsCount; i++){        
        Item *currItem = itemDataBase->itemsArray[database]->items[i];

        // if id matches we return the entire item
        if(currItem->itemId == id){
            return currItem;
        }
    }
    return NULL;
}
