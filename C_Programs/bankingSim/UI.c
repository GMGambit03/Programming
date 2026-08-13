#include "UI.h"
#include "fileInfo.h"
// Deposit Function and GUI
void depositGUI(Account* user)
{
    char userInput[17];
    clearScreen();

    printf("\n");
    printf("\n");
    printf(" How much would you like to deposit to checkings: ");

    fgets(userInput, sizeof(userInput), stdin);
    clearInputBuffer(userInput);   

    user->Checkings += atof(userInput);
    updateBank(user);
    printf(" Deposit was successful");
    getchar();
}

// Transfer GUI
void transGUI(Account* user)
{
    while(true)
    {
        clearScreen();

        char userInput[2];
        char transAmount[20];

        //GUI
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("          =========== (1)Checkings [%.2lf]       ", user->Checkings);
        printf(" (2)Savings [%.2lf] ===========\n", user->Savings);

        fgets(userInput, sizeof(userInput), stdin);
        clearInputBuffer(userInput);

        // switch if its checkings or savings
        switch (*userInput)
        {
        case '1':
            printf("          =========== How much would you like to transfer to savings =========\n");
            printf("\n");
            printf("                     --- $");
            fgets(transAmount, sizeof(transAmount), stdin);
            clearInputBuffer(transAmount);

            float ammount = atof(transAmount);

            // validate if user has that much
            if(ammount > user->Checkings){
                printf("You don't have enough to transfer that ammount");
                getchar();
                continue;
            }

            user->Checkings -= ammount;
            user->Savings += ammount;
            updateBank(user);
        break;
        case '2':
            printf("          =========== How much would you like to transfer to checkings =========\n");
            printf("\n");
            printf("                     --- $");

            fgets(transAmount, sizeof(transAmount), stdin);
            clearInputBuffer(transAmount);
            ammount = atof(transAmount);

            if(ammount > user->Savings){
                printf("You don't have enough to transfer");
                getchar();
                continue;
            }

            user->Savings -= ammount;
            user->Checkings += ammount;
            updateBank(user);
        break;
        
        default:
            printf(" Something went wrong");
        break;
        }
        break;
    }
    printf(" Transfer was successful");
    getchar();
}

// Withdraw function and GUI
void withDrawGUI(Account* user)
{
    while (true)
    {
        char userInput[17];
        clearScreen();

        printf("\n");
        printf("\n");
        printf(" How much would you like to withdraw to checkings: ");

        fgets(userInput, sizeof(userInput), stdin);
        clearInputBuffer(userInput);   

        double amount = atof(userInput);
        if(user->Checkings - amount < 0)
        {
            printf(" That exceeds the draw limit");
            getchar();
            continue;
        }
        user->Checkings -= amount;
        updateBank(user);
        printf(" Withdrawl was successful");
        getchar();
        break;
    }
}

void accountGUI(Account user)
{
    char userInput[2];
    while(true)
    {
        clearScreen();

        printf("\033[?25l");
        fflush(stdout);

        getBankInfo(&user);

        printf("\n");
        printf("\n");
        printf(" ========== Its Lovely to see you again at Bank of BallSacks [ %s ] ==========", user.Username);
        printf("\n");
        printf("\n");
        printf("                ===== Checking =====                 ===== Savings =====");
        printf("\n");
        printf("                    --- %.2lf ---                        ", user.Checkings);
        printf("--- %.2lf ---", user.Savings);
        printf("\n");
        printf("\n");
        printf("\n");
        printf(" --- (1)Deposit\n");
        printf(" --- (2)Withdraw\n");
        printf(" --- (3)Transfer\n");
        printf(" --- (4)Log Out\n");

        fgets(userInput, sizeof(userInput), stdin);
        clearInputBuffer(userInput);

        if(*userInput <= '0' || *userInput >= '5')
        {
            printf("Please enter valid key");
            getchar();
            continue;
        }
        
        switch (*userInput)
            {
            case '1':
                depositGUI(&user);
            break;
            case '2':
                withDrawGUI(&user);
            break;
            case '3':
                transGUI(&user);
            break;
            case '4':
                startingMenu();
            break;
            default:
            printf("Something went wwrong in Account GUI Switch Case");
        break;
        }
    }
}