#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "headers/logs.h"
#include "headers/menu.h"
#include "headers/input.h"
#include "headers/color.h"
#include "headers/structsHelp.h"

// Save Logs to a file
void saveLogs(int* logCountPtr, log_t **logsArray){

    while (true)
    {
        clearScreen();
        int validater;
        char fileName[21];
        FILE *logFile;

        if(*logCountPtr == 0){
            printf(" You have no logs to be saved");
            getchar();
            break;
        }
    
        printf("\n");
        printf("\n");
        printf(GREY " # Please input file name maximum ammount of charcters is 2\n\n" RESET);

        validater = inputLengthManger(fileName, sizeof(fileName));
        switch (validater)
        {
        case 1:
            printf(" Please input a file name with a length greater then 0");
            getchar();
            deleteLines(5);
            continue;
        break;
        case 2:
            continue;
        break;
        default:
        break;
        }

        logFile = fopen(fileName, "w");
        if(logFile == NULL)
        {
            printf(GREY" # Something went wrong please try again" RESET);
            getchar();
        }

        fprintf(logFile,"\n\n");
        for(int i = 0; i <= (*logCountPtr) - 1; i++){
            log_t current = (*logsArray)[i];
            
            fprintf(logFile," [ logId: %d ] [ Time Stamp: %s ] [ Severity: %s ] [ Content: %s ]\n\n", current.iD, current.dateFormat, current.severity, current.contents);
        }

        fclose(logFile);
        *logCountPtr = 0;
        free(*logsArray);
        (*logsArray) = malloc((*logCountPtr + 1) * sizeof(log_t));
        printf(" Logs save complete");
        getchar();
        break;
        
    }
    


}

// Delete Logs function
bool deleteLog(log_t **logsArray, int* logCountPtr){
    int userInput = inputManager() - 1;

    if(userInput >= *logCountPtr || userInput < 0)
    {
        return false;
    }
    if(*logCountPtr > 1)
    {
        for(int i = userInput; i <= *logCountPtr - 1; i++){
            (*logsArray)[i + 1].iD--;
            (*logsArray)[i] = (*logsArray)[i + 1];
        }
    }
    (*logCountPtr)--;

    log_t* temp = realloc((*logsArray),((*logCountPtr) + 1) * sizeof(log_t));
    if(temp == NULL){
        printf("Something went wronf with resizing realloc, im not handling it tho");
        return 1;
    }

    *logsArray = temp;
    return true;

}

/**
 * arguments~:
 * return va;ue
 * 
 */
void addLog(int* logCountPtr, log_t **logsArray, bool *mainMenu)
{
    bool pass = false;
    clearScreen();

    while(true){
        log_t newLog;
        time_t raw_time;

        static char command[10] = "/menuOpen";

        int userInputInt;

        if(pass == false){
            clearScreen();
            printf("\n");
            printf("\n");
            printf(GREY " # Maximum of 256 characters write log and press enter when your done\n " RESET);
            printf(GREY " # if you would like to pull up the menu input /menuOpen\n\n " RESET);
        }else{
            printf(GREY " # Input Log\n\n " RESET);
        } 

        int validater = inputLengthManger(newLog.contents, sizeof(newLog.contents));

        if(validater == 1){
            if(pass == true){
                deleteLines(2);
            }
            printf(" Please type in a log or /menuOpen for the menu");
            getchar();
            deleteLines(1);
            printf("\n");
        }if(validater == 2 || validater == 1){
            continue;
        }

        if(strcmp(newLog.contents, command) == 0){

            printf(" [ [1] Add log");
            printf(" [2] View logs");
            printf(" [3] Main Menu ]");
            printf("\n\n ");

            userInputInt = inputManager();

            switch (userInputInt)
            {
            case 1:
                deleteLines(5);
            break;
            case 2:
                viewLog(logsArray, logCountPtr, mainMenu);
                pass = false;
            break;
            case 3:
                *mainMenu = true;
            break;
            default:
                printf("Something went fuckking wrong and yea");
                getchar();
            break;
            }
            if(*mainMenu) break;
            continue;
            
        }

        while(true)
        {
            if (*mainMenu) break;
            // get severity 1-7
            printf(GREY "\n # Please enter severity of log");
            printf("\n");
            printf("\n");
            printf(" [ [0] Emergency ]\n [ [1] Alert ]\n [ [2] Critical ]\n [ [3] Error ]\n "
                    "[ [4] Warning ]\n [ [5] Notification ]\n [ [6] Informational ]\n [ [7] Debugging]" RESET);
            printf("\n");
    
            userInputInt = inputManager();

            deleteLines(10);
            if(!getSeverity(userInputInt,&newLog) || userInputInt == 15){
                deleteLines(0);
                continue;
            }
            break;
        }

        time(&raw_time);
        newLog.timeStampStruct = localtime(&raw_time);
        timeStampGen(&newLog);

        newLog.iD = (*logCountPtr) + 1;
        (*logCountPtr)++;

        log_t *temp = realloc((*logsArray), ((*logCountPtr) + 1) * sizeof(log_t));

        
        if (temp == NULL) {
            printf("Resizing failed! Original data is still safe.\n");
            getchar();
            break;
        }else{
            *logsArray = temp;
            (*logsArray)[*logCountPtr - 1] = newLog;
        }
        
        if(*mainMenu) break;
        pass = true;
    }

}