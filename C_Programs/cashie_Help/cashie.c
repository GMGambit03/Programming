#include <stdio.h>
#include <stdlib.h>

void pay_amount(int dollars, int *twenties, int *tens, int *fives, int *ones);

int main(int argc, char const *argv[])
{
    int dollars;
    int twenties;
    int tens;
    int fives;
    int ones;

    printf(" Please type only numbers how much change does the person have: ");
    scanf("%d", &dollars);

    pay_amount(dollars, &twenties, &tens, &fives, &ones);
    return 0;
}

void pay_amount(int dollars[], int *twenties, int *tens, int *fives, int *ones)
{

    while(dollars > 0)
    {
        if(dollars >= 20){
            dollars -= 20;
            (*twenties)++;
        }else if(dollars >= 10){
            dollars -= 10;
            (*tens)++;
        }else if(dollars >= 5){
            dollars -= 5;
            (*fives)++;
        }else if(dollars != 0){
            dollars -= 1;
            (*ones)++;
        }
    }
    printf("20s: %d, 10s: %d, 5s: %d, 1s: %d, ", *twenties, *tens, *fives, *ones);
    getchar();
}
