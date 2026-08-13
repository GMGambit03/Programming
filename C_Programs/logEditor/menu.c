#include <stdio.h>

#include "headers/menu.h"
#include "headers/logs.h"
#include "headers/input.h"

// View Logs
void viewLog(log_t **logsArray, int* logCountPtr, bool *mainMenu){

    while(true)
    {
        int userInput;

        if(*logCountPtr == 0){
            printf(" You have no logs to view at the moment, please add a log");
            getchar();
            break;
        }
    
        clearScreen();
        printf("\n");
        printf("\n");
    
        for(int i = 0; i <= *logCountPtr - 1; i++){
            log_t current = (*logsArray)[i];
            
            printf(" [ Time Stamp: %s ] [Severity: %s] [logId: %d] [Content: %s]\n\n", current.dateFormat, current.severity, current.iD, current.contents);
        }
    
        printf("\n");
        printf("\n");
        printf(" [1]: Add  ");
        printf(" [2]: Delete  ");
        printf(" [3]: Save ");
        printf(" [4]: Main Menu ");
        printf("\n");
        printf("\n");

        userInput = inputManager();
    
        switch (userInput)
        {
        case 1:
            // Go to addLog through break
            *mainMenu = false;
        break;
        case 2:
            printf(" \nWhich log do you want to delete \n");
            printf(" Log: ");

            if(!deleteLog(logsArray, logCountPtr)){
                printf(" Unable to delete log... Log doesnt exist");
                getchar();
            }else{
                printf(" Log successfully deleted");
                getchar();
            }
        break;
        case 3:
            saveLogs(logCountPtr, logsArray);
        break;
        case 4:
            // Going to main menu through multiple breaks
            *mainMenu = true;
        break;
        default:
            printf("Something went fuckking wrong and yea");
            break;
        }
        if(userInput == 1 || userInput == 4) break;
    }
    
}
//create menu
void startingMenu(int* logCountPtr, log_t **logsArray)
{

    while (true)
    {
        clearScreen();
        bool mainMenu = false;
        int userInputInt;

        printf("\n");
        printf("\n");
        printf(" [ ===== Regular ass log editor =====]");
        printf("\n");
        printf("\n");

        // Options are view/add/delete/save current session
        printf(" [ [1]: View  ");
        printf("[2]: Add  ");
        printf("[3]: Save ");
        printf(" [4]: Exit ]");
        printf("\n");
        printf("\n");

        userInputInt = inputManager(); 

        if(userInputInt == 15){
            continue;
        }

        printf("\n");

        switch (userInputInt)
        {
        case 1:
            viewLog(logsArray, logCountPtr, &mainMenu);
        break;
        case 2: 
            addLog(logCountPtr, logsArray, &mainMenu);
            mainMenu = false;
        break;
        case 3:
            saveLogs(logCountPtr, logsArray);
        break;
        case 4:
            mainMenu = true;
        break;
        default:
            printf("Something went wrong or invalid input");
        break;
        }
        if (mainMenu == true) break;
    }

}
