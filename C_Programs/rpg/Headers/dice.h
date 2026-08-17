#ifndef DICE
#define DICE

#include <time.h>
#include <stdlib.h>

typedef enum{
    D4,
    D6,
    D8,
    D10,
    D12,
    D20
}DiceType;

typedef struct{
    DiceType diceType;
    int diceSides;
}Dice;

typedef struct{
        DiceType diceType;
        double dmgReduction;
        int rolls;
}Roll;

double rollDice(Roll roll);
Dice createDice(DiceType diceType);

#endif