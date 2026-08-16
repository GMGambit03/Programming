#include "Headers/dice.h"

Dice createDice(DiceType diceType){

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
        double roll = rand() % (dice.diceSides + 1);
        sum += roll;
    }

    sum *= roll.multiplier;

    return sum;
}