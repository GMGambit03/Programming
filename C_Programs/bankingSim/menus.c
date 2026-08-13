#include "menu.h"
#include "fileInfo.h"

// System Login Menu
void loginMenu()
{
    while(true)
    {
        clearScreen();

        char userName[17] = "";
        char passWord[30] = "";

        printf("\n");
        printf("\n");
        printf(" ====== Login Menu ======\n\n");
        printf(" Please provide your credentials to continue.\n\n");

        printf(" [ Username ] : \n\n");


        printf(" [ Password ] : \n\n");

        printf(" (1)Exit");

        printf("\033[7;17H");
        fflush(stdout);
        fgets(userName, sizeof(userName), stdin);
        clearInputBuffer(userName);

        if(*userName == '1')
        {
            startingMenu();
        }

        printf("\033[9;17H");
        fflush(stdout);
        fgets(passWord, sizeof(passWord), stdin);
        clearInputBuffer(userName);

        // validate username and passWord is an actual account;
        //if not continue loop else grab account id and use it to create menu
        if(strlen(userName) > 15 || strlen(userName) < 4 || strlen(passWord) < 8 || !loginValidation(userName, passWord))
        {
            printf("The username or password entered is incorrect please try again");
            getchar();
            continue;
        }else{printf("Something went wrong");}

        printf("Something went wrong");
        clearScreen();

        // validate username and passWord is an actual account;
        //if not continue loop else grab account id and use it to create menu
        break;
    }

}

// System Create Account Menu
void createAccount()
{
    while(true)
    {
        clearScreen();

        char userName[17] = "";
        char passWord[22] = "";

        printf("\n");
        printf("\n");
        printf(" ====== Create Account ======\n\n");
        printf(" Welcome to Bumb Ass Ball Sacks.\n\n");

        printf(" [ Username ]: \n\n");

        printf(" * Requirements:\n");
        printf("   • Must be 4 to 15 characters long\n");
        printf("   • Must have at least one uppercase letter\n");
        printf("   • Letters and numbers only\n");
        printf("   • Cannot start with a number\n\n");


        printf(" [ Password ]: \n\n");

        printf(" * Requirements:\n");
        printf("   • Must be 8 to 20 characters long\n");
        printf("   • Must contain at least:\n");
        printf("   • One uppercase letter\n");
        printf("   • One lowercase letter\n");
        printf("   • One numeric digit\n");
        printf("   • One special character\n");
        printf("\n");
        printf("\n");
        printf(" (1)Exit");

        //Go to username line
        printf("\033[7;16H");
        fflush(stdout);

        // Get username entry and preventing buffer over flow
        fgets(userName, (sizeof(userName)), stdin);
        clearInputBuffer(userName);

        if(*userName == '1')
        {
            startingMenu();
        }

        // Validate username
        if(!accValidUser(userName)){
            getchar();
            continue;
        }

        // Put cursor next to password
        printf("\033[15;16H");
        fflush(stdout);

        fgets(passWord, (sizeof(passWord)), stdin);
        clearInputBuffer(passWord);

        if(!accValidPass(passWord)){
            getchar();
            continue;
        }

        clearScreen();
        addAccInfo(userName, passWord);
        break;
    }
    loginMenu();

}

// Screen when you first come in
void startingMenu()
{
    while(true){
        clearScreen();
        printf("\033[?25l");
        char userInput[2];

        printf("\n");
        printf("\n");
        printf("                    =========== Welcome to Ball Sacks Bank ===========\n");
        printf("\n");
        printf("            [1][ Create a account ]");
        printf("            [2][ Login ]");
        printf("            [3][ Exit ]\n");

        fgets(userInput, sizeof(userInput), stdin);
        clearInputBuffer(userInput);

        switch (*userInput)
        {
        case '1':
            createAccount();
        break;
        case '2':
            loginMenu();
        break;
        case '3':
            printf(" Have a nice one");
            getchar();
        break;
        
        default:
            printf(" Didint quite get that, please try again");
            getchar();
        continue;
        break;
        }
        break;
    }
}
