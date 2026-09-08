#include "Headers/inventoryDisplay.h"
#include "Headers/dialogue.h"
#include "Headers/fileHandle.h"
#include "Headers/itemHelper.h"
#include "Headers/stringHelpers.h"
#include <stdio.h>

void itemHeader(ItemArray *items, Item *currWeapon, Item *currArmor, Player *player){
    char wepPEN[20];
    char armDEF[20];

    sprintf(wepPEN, "PEN: %.2lf", currWeapon->effectData.penetration);
    sprintf(armDEF, "DEF: %.2lf", currArmor->effectData.dmgReduction);

    printf(" %-44s   %s", "INVENTORY", "CHARACTER");
    printf("\n");
    charFiller(45, '-');
    printf(" ");
    charFiller(35, '-');
    printf("\n");
    printf(" %-4s %-25s %-6s %-8s","#", "ITEM", "QTY", "WEIGHT");
    printf(" %s - %s", player->className, player->name);
    printf("\n");
    charFiller(45, '-');
    printf(" ");
    charFiller(35, '-');
    charFiller(1, '\n');


    // ADD WISDOM STAT EVENTUALLY
    int characterRows = 14;
    int rows = max(items->itemsCount, characterRows);

    for(int i = 0; i < rows; i++){

    /* LEFT PANEL */
    if(i < items->itemsCount){
        Item *currItem = items->items[i];

        printf(" %-4d %-25s x%-5d %-9.2lf ",
                i + 1,
                currItem->itemName,
                currItem->quantity,
                currItem->weight);
        }else{
            printf("%-49s", "");
        }

        /* RIGHT PANEL */
        switch(i){
            case 0:
                printf("%-11s %.2lf / %.2lf", "HP", player->health, player->maxHealth);
            break;

            case 1:
                printf("%-11s %.2lf / %.2lf", "MANA", player->mana, player->maxMana);
            break;

            case 2:
                printf("%-11s %.2lf", "STRENGTH", player->strength);
            break;

            case 3:
                printf("%-11s %.2lf", "SPEED", player->speed);
            break;

            case 4:
            break;

            case 5:
                printf("%-11s [ # ] ITEM", "EQUIPPED");
            break;

            case 6:
                charFiller(33, '-');
            break;

            case 7:
                printf("%-11s [ %d ] %s", "WEAPON", items->itemsCount + 1, currWeapon->itemName);
            break;

            case 8:
                printf("%-11s PEN: %.2lf", "", currWeapon->effectData.penetration);
            break;

            case 9:
                printf("\n");
            break;

            case 10:
                printf("%-11s [ %d ] %s", "ARMOR", items->itemsCount + 2, currArmor->itemName);
            break;

            case 11:
                printf("%-11s DEF: %.2lf", "", currArmor->effectData.dmgReduction);
            break;

            case 12:
                charFiller(33, '-');
            break;

            case 13:
                printf("%-11s %.2lf", "Gold", player->gold);
            break;
        }

        printf("\n");
    }

    printf("\n");
    charFiller(82, '-');
    charFiller(1, '\n');
    printf(" [ # ] SELECT ITEM");
    printf("\n");
    printf(" [ 0 ] EXIT");
    charFiller(1, '\n');
    printf(" >");

}

ItemOptions *itemDisplay(Item *item, Player *player, int *optionsSize){
    

    static ItemOptions weaponOptions[] = {
        {"Equip", EQUIP}, 
        {"Drop", DROP}
    };
    static ItemOptions equipedOptions[] ={
        {"Unequip", UNEQUIP}
    };
    static ItemOptions armorOptions[] = {
        {"Equip", EQUIP}, 
        {"Drop", DROP}
    };
    static ItemOptions potionsOptions[] = {
        {"Use", USE}, 
        {"Drop", DROP}
    };
    static ItemOptions otherOptions[] = {
        {"Drop", DROP}
    };

    // Theyre all the exact same amount of bytes so when we malloc itemDesc we can make it universal
    // Theyre also in the order of the ITEMTYPE enum so dont change the order unless you change the order of ITEMTYPE enum
    char *typeOfDesc[] = {"Penetration:", "Damage Reduction:", "Effect:"};
    char *itemDesc;
    double itemEffect;

    ItemOptions *options;
    switch(item->itemType){
        case WEAPON:
            itemDesc = typeOfDesc[WEAPON];
            InventoryOptions = weaponOptions;
            *optionsSize = sizeof(weaponOptions)/sizeof(weaponOptions[0]);
            itemEffect = item->effectData.penetration;
        break;
        case ARMOR:
            itemDesc = typeOfDesc[ARMOR];
            InventoryOptions = armorOptions;
            *optionsSize = sizeof(armorOptions)/sizeof(armorOptions[0]);
            itemEffect = item->effectData.dmgReduction;
        break;
        case POTION:
            itemDesc = typeOfDesc[POTION];
            InventoryOptions = potionsOptions;
            *optionsSize = sizeof(potionsOptions)/sizeof(potionsOptions[0]);
            itemEffect = item->effectData.effect;
        break;
        default:
            itemDesc = "";
            InventoryOptions = otherOptions;
            *optionsSize = sizeof(otherOptions)/sizeof(otherOptions[0]);
            itemEffect = NONE;
        break;
    }

    if(item->itemId == player->armorSet || item->itemId == player->weapon){
        options = equipedOptions;
        *optionsSize = sizeof(equipedOptions)/sizeof(equipedOptions[0]);
    }

    char *strTypesArr[] = {"WEAPON", "ARMOR", "POTION", "UTILITY", "ARTIFACT", "MATERIAL"};
    char *itemType = strTypesArr[item->itemType];

    printf(" %-23s %s", "Type:", itemType);
    printf("\n");

    if(itemEffect != NONE){
        printf(" %-23s %.2lf", itemDesc, itemEffect);
        printf("\n");
    }
    
    printf(" %-23s %.2lf", "Weight:", item->weight);
    printf("\n");
    printf(" %-23s %.2lf Gold", "Value:", item->value);
    charFiller(1, '\n');
    charFiller(60, 60);
    charFiller(1, '\n');

    for(int i = 0; i < *optionsSize; i++){
        printf(" [ %d ] %s", (i + 1), InventoryOptions[i].name);
        printf("\n");
    }

    printf(" [ 0 ] Back");
    charFiller(1, '\n');
    printf(" >");
    return InventoryOptions;
}

int dropQtcMenu(){
    while(true){
        clearScreen();
        char userInput[5];
    
        printf(" >");
        fgets(userInput, sizeof(userInput), stdin);
        if(!clearBuffer((int)sizeof(userInput) ,userInput)){
            continue;
        }

        for(int i = 0; i < strlen(userInput); i++){
            if(userInput[i] < '0' || userInput[i] > '9'){
                validOption();
                enterContinue();
                getchar();
                continue;
            }
        }
        int userInt = atoi(userInput);
        return userInt;
    }
}