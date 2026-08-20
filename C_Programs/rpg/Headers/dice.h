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
}DICETYPE;

typedef struct{
    DICETYPE diceType;
    int diceSides;
}Dice;

typedef struct{
    DICETYPE diceType;
    int rolls;
}Roll;

double rollDice(Roll roll);
Dice createDice(DICETYPE diceType);
DICETYPE getDiceType(int diceSides);

#endif