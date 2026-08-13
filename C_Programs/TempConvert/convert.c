#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void clearScreen() {
    // \033[H moves cursor to home, \033[2J clears screen
    printf("\033[H\033[2J");
}

void outPutHelp(int toUnit, double sum)
{
    switch (toUnit)
    {
        case 1:
            printf("%lf", sum);
            printf("C\n");
        break;
        
        case 2:
            printf("%lf", sum);
            printf("F\n");
        break;
        
        case 3:
            printf("%lf", sum);
            printf("K\n");
        break;
        
        case 4:
            printf("%lf", sum);
            printf("R\n");
        break;
        
        case 5:
            printf("%lf", sum);
            printf("Re\n");
        break;
    
    default:
        printf("Somehtings wrong msybe");
    break;
    }
}

double fahrenheit(double value, int toUnit)
{
    double sum = 0;

    switch (toUnit)
    {
        case 1:
            sum = (value - 32.0) * (5.0/9);
        break;

        case 3:
            sum = (value + 459.67) * (5.0/9);
        break;

        case 4:
            sum = (value + 459.67);
        break;

        case 5:
            sum = (value - 32.0) * (4.0/9);
        break;
    default:
        printf("System is broken, idk");
        break;
    }

    return sum;
}

double celsius(double value, int toUnit)
{
    double sum = 0;

    switch (toUnit)
    {
        case 2:
            sum = (value * (9.0/5)) + 32;
        break;

        case 3:
            sum = (value + 273.15);
        break;

        case 4:
            sum = (value * (9.0/5)) + 491.67;
        break;

        case 5:
            sum = (value * (4.0/5));
        break;
    default:
        printf("System is broken, idk");
        break;
    }

    return sum;
}

double kelvin(double value, int toUnit)
{
    double sum = 0;

    switch (toUnit)
    {
        case 1:
            sum = (value - 273.15);;
        break;

        case 2:
            sum = (value * (9.0/5)) - 459.67;
        break;

        case 4:
            sum = (value * (9.0/5));
        break;

        case 5:
            sum = (value - 273.15) * (4.0/5);
        break;
    default:
        printf("System is broken, idk");
        break;
    }

    return sum;
}

double rankine(double value, int toUnit)
{
    double sum = 0;

    switch (toUnit)
    {
        case 1:
            sum = (value - 491.67) * (5.0/9);
        break;

        case 2:
            sum = (value - 459.67);
        break;

        case 3:
            sum = (value * (5.0/9));
        break;

        case 5:
            sum = (value - 491.67) * (4.0/9);
        break;
    default:
        printf("System is broken, idk");
        break;
    }

    return sum;
}

double reaumur(double value, int toUnit)
{
        double sum = 0;

    switch (toUnit)
    {
        case 1:
            sum = (value * (5.0/4));
        break;

        case 2:
            sum = (value * (9.0/4)) + 32;
        break;

        case 3:
            sum = (value * (5.0/4)) + 273.15;
        break;

        case 4:
            sum = (value * (9.0/4)) + 491.67;
        break;
    default:
        printf("System is broken, idk");
        break;
    }

    return sum;
}

int main(int argc, char const *argv[])
{
    while(true)
    {
        int base = 0;
        int conversion = 0;

        double value = 0;

        while(true)
        {
            base = 0;

            printf("Welcome to Temp Convert. Choose what you want to convert.\n");
            printf("From:\n Celsius(1)\n Fahrenheit(2)\n Kelvin(3)\n Rankine(4)\n Reaumur(5)\n");

            scanf("%d", &base);
            
            if(base == 0 || base > 5){
                printf("Please enter valid number\n");
                getchar();
            }
            else{
                while(true)
                {
                    value = 0;

                    printf("Enter value to convert: ");
                    scanf("%lf", &value);

                    if(value == 0){

                        printf("\nStop being a dumbass and enter a number\n");
                        getchar();
                        getchar();
                    }
                    else{
                        break;
                    }                
                }
                break;

            }
        }

        while(true)
        {
            conversion = 0;
            printf("Choose what you want to convert to.\n");
            printf("To:\n Celsius(1)\n Fahrenheit(2)\n Kelvin(3)\n Rankine(4)\n Reaumur(5)\n");

            scanf("%d", &conversion);
            
            if(conversion == 0 || conversion > 5){
                printf("Please enter valid number\n");
                getchar();
            }
            if(conversion == base){
                printf("Please choose a conversion thats different then the previous temperature type");

            }
            else{break;}       
        }

        clearScreen();

        switch (base)
        {
        case 1:
            printf("%lf", value);
            printf("C is ");
            outPutHelp(conversion, celsius(value, conversion));
        break;

        case 2:
            printf("%lf", value);
            printf("F is ");
            outPutHelp(conversion, fahrenheit(value, conversion));
        break;

        case 3:
            printf("%lf", value);
            printf("K is ");
            outPutHelp(conversion, kelvin(value, conversion));
        break;

        case 4:
            printf("%lf", value);
            printf("R is ");
            outPutHelp(conversion, rankine(value, conversion));
        break;

        case 5:
            printf("%lf", value);
            printf("Re is ");
            outPutHelp(conversion, reaumur(value, conversion));
        break;
        default:
            break;
        }
    }

}
