#include "Headers/dice.h"

Dice createDice(DICETYPE diceType){

    Dice dice;
    dice.diceType = diceType;

    switch(diceType){
        case D4:
            dice.diceSides = 4;
        break;
        case D6:
            dice.diceSides = 6;
        break;
        case D8:
            dice.diceSides = 8;
        break;
        case D10:
            dice.diceSides = 10;
        break;
        case D12:
            dice.diceSides = 12;
        break;
        case D20:
            dice.diceSides = 20;
        break;
    }
    
    return dice;
}

double rollDice(Roll roll){

    Dice dice = createDice(roll.diceType);
    double sum = 0;

    for(int i = 0; i < roll.rolls; i++){
        double roll = (rand() % dice.diceSides) + 1 ;
        sum += roll;
    }

    // this might be replaced with modifier in the future
    // sum += roll.dmgReduction;

    return sum;
}

DICETYPE getDiceType(int diceSides){
    switch(diceSides){
        case 4:
            return D4;
        break;
        case 6:
            return D6;
        break;
        case 8:
            return D8;
        break;
        case 10:
            return D10;
        break;
        case 12:
            return D12;
        break;
        case 20:
            return D20;
        break;
    }
    return D4;
}