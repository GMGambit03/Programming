#include "Headers/rpgStructs.h"

Player *assignBaseInfo(Object *classData){

    Player *player = malloc(sizeof(Player));

    Roll goldRoll = {D4, 10, 0};
    
    switch(classData->id){
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

    player->className = classData->objName;

    player->gold = rollDice(goldRoll);

    player->health = getMember(classData, "hp")->value.data.number;
    player->maxHealth = player->health;
    player->mana = getMember(classData, "Mana")->value.data.number;
    player->maxMana = player->mana;
    player->speed = getMember(classData, "Speed")->value.data.number;
    player->maxSpeed = player->speed;
    player->strength = getMember(classData, "Strength")->value.data.number;
    player->maxStrength = player->strength;

    return player;
    
}