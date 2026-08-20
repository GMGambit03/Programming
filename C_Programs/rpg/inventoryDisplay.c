#include "Headers/inventoryDisplay.h"
#include "Headers/dialogue.h"
#include "Headers/fileHandle.h"
#include "Headers/itemHelper.h"
#include "Headers/stringHelpers.h"
#include <stdio.h>

void itemHeader(Inventory *inventory, ItemArray *items){
    charFiller(60, '-');
    printf("\n");
    printf("%-4s %-25s %-5s %-10s\n","#", "ITEM", "QTY", "WEIGHT");
    charFiller(60, '-');
    charFiller(1, '\n');

    for(int i = 0; i < items->itemsCount; i++){
        Item *currItem = items->items[i];
        printf("%-4d %-25s %-5d %-20.2lf", (i + 1), currItem->itemName, inventory->items[i].quantity, currItem->weight);
        printf("\n");
    }
    charFiller(60, '-');
    charFiller(1, '\n');
    printf(" [ # ] SELECT ITEM");
    printf("\n");
    printf(" [ 0 ] EXIT");
    charFiller(1, '\n');
    printf(" >");

}

ITEMOPTIONS *itemDisplay(Item *item, int *optionsSize){
    

    char *strWeapOpts[] = {"Equip", "Drop"};
    ITEMOPTIONS weapOpts[] = {EQUIP, DROP};
    int weapOptSize = sizeof(strWeapOpts)/sizeof(strWeapOpts[0]);

    char *strArmorOpts[] = {"Equip", "Drop"};
    ITEMOPTIONS armorOpts[] = {EQUIP, DROP};
    int armOptSize = sizeof(strArmorOpts)/sizeof(strArmorOpts[0]);

    char *strPotionOpts[] = {"Use", "Drop"};
     ITEMOPTIONS potionOpts[] = {USE, DROP, MULTIDROP};
    int potOptSize = sizeof(strPotionOpts)/sizeof(strPotionOpts[0]);

    // Theyre all the exact same amount of bytes so when we malloc itemDesc we can make it universal
    // Theyre also in the order of the ITEMTYPE enum so dont change the order unless you change the order of ITEMTYPE enum
    char *typeOfDesc[] = {" Penetration:        ", " Damage Reduction:   ", " Effect:            "};
    char *itemDesc = malloc(sizeof(char) * 21);
    double itemEffect;

    

    char **strOptions;
    ITEMOPTIONS *options;
    switch(item->itemType){
        case WEAPON:
            itemDesc = typeOfDesc[WEAPON];
            strOptions = strWeapOpts;
            *optionsSize = weapOptSize;
            options = weapOpts;
            itemEffect = item->effectData.penetration;
        break;
        case ARMOR:
            itemDesc = typeOfDesc[ARMOR];
            strOptions = strArmorOpts;
            *optionsSize = armOptSize;
            options = armorOpts;
            itemEffect = item->effectData.dmgReduction;
        case POTION:
            itemDesc = typeOfDesc[POTION];
            strOptions = strPotionOpts;
            *optionsSize = potOptSize;
            options = potionOpts;
            itemEffect = item->effectData.effect;
        break;
        default:
        break;
    }

    char *strTypesArr[] = {"WEAPON", "ARMOR", "POTION", "UTILITY, ARTIFACT"};
    char *itemType = strTypesArr[item->itemType];

    printf(" Type:              %s", itemType);
    printf("\n");
    printf("%s%.2lf", itemDesc, itemEffect);
    printf("\n");
    printf(" Weight:            %.2lf", item->weight);
    printf("\n");
    printf(" Value:             %.2lf Gold", item->value);
    charFiller(1, '\n');
    charFiller(60, 60);
    charFiller(1, '\n');

    for(int i = 0; i < *optionsSize; i++){
        printf(" [ %d ] %s", (i + 1), strOptions[i]);
        printf("\n");
    }

    printf(" [ 0 ] Back");
    charFiller(1, '\n');
    printf(" >");
    return options;
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