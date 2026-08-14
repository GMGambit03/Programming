#include "Headers/rpgStructs.h"

Player assignBaseInfo(Object *classData){
    struct roll{
        DiceType diceType;
        int do
    }

    Player *player = malloc(sizeof(Player));

    player->className = classData->objName;
    
    switch(classData->id){
        case 1:
            player->gold = rollDice(D4, 10, 4);
    }
    
}