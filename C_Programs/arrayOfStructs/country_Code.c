#include <stdio.h>
#include <string.h>

struct country_Code
{
    char *countryName;
    int code;
};


int main(int argc, char const *argv[])
{
    int userInput;
    struct country_Code Codes[] = 
    {
        {"Australia", 61},
        {"Brazil", 55},
        {"Canada", 1},
        {"Denmark", 45},
        {"Egypt", 20},
        {"France", 33},
        {"Germany", 49},
        {"India", 91},
        {"Italy", 39},
        {"Japan", 81},
    };

    printf("Type in a code and i display the country");
    scanf("%d", &userInput);

    int length = sizeof(Codes) / sizeof(Codes[0]);
    for(int i = 0; i < length; i++){
        //printf("%d", Codes[i].code);
        if(userInput == Codes[i].code)
        {
            printf("%s: %d", Codes[i].countryName, Codes[i].code);
        }else continue;
    }
    getchar();
    
    return 0;
}
