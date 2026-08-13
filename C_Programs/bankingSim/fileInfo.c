#include "fileInfo.h"

// get number of userids and increment
int addUsers()
{
    FILE *ogFile;
    FILE *tempFile;

    ogFile = fopen("Accounts.txt", "r");
    tempFile = fopen("temp.txt", "w");

    char line[100];
    char buffer[10];
    const int start_line = 2;

    if(ogFile == NULL || tempFile == NULL)
    {
        printf("Error with file");
        return 0;
    }

    int Users; 
    (fscanf(ogFile,"Users: %d", &Users));
    Users++;

    fprintf(tempFile, "Users: %d\n\n", Users);

    for(int i = 0; i < start_line; i++){
        fgets(buffer, sizeof(buffer), ogFile);
    }

    while(fgets(line, sizeof(line), ogFile) != NULL){
        fputs(line, tempFile);
    }

    fclose(ogFile);
    fclose(tempFile);

    remove("Accounts.txt");
    rename("temp.txt", "Accounts.txt");

    return Users;

}

// add bank balances and userid
void addBankInfo(int userID)
{
    FILE *bankFile;
    bankFile = fopen("BankInfo.txt", "a");

    Account user;
    user.Checkings = 0.00;
    user.Savings = 0.00;

    // add UserID
    fprintf(bankFile, "User: %d", userID);
    // add checkings Balance
    fprintf(bankFile, " - Checkings Balance: %.2f", user.Checkings);
    // add savings Balance
    fprintf(bankFile, " - Savings Balance: %.2f", user.Savings);
    fprintf(bankFile, "\n");

    fclose(bankFile);
}

// add userid, username, and password to account file
void addAccInfo(char userName[], char password[])
{
    int userID = addUsers();
    // add userid
    FILE *accFile;
    accFile = fopen("Accounts.txt", "a");

    fprintf(accFile, "ID: %d", userID);

    // Add username and password
    fprintf(accFile, " - %s - %s", userName, password);
    fprintf(accFile, "\n");

    fclose(accFile);

    addBankInfo(userID);
}

// function to get money from database
void getBankInfo(Account* user)
{
    FILE *bankFile;
    bankFile = fopen("BankInfo.txt", "r");

    char bufferLine[MAX_CHAR];
    char userId[30];

    sprintf(userId, "User: %d", user->UserID);

    while(fgets(bufferLine, sizeof(bufferLine), bankFile) != NULL)
    {
        char*  matchUser;
        char* token;
        char* save = bufferLine;

        matchUser = strstr(bufferLine, userId);
        token = strtok_r(bufferLine, " -:", &save);
        int i = 0;
        if(matchUser != NULL)
        {
            while((token = strtok_r(save, " -:,", &save)) != NULL)
            {
                if(*token >= '0' && *token <= '9' && strlen(token) > 2)
                {
                    switch (i)
                    {
                    case 0:
                        user->Checkings = atof(token);
                        i++;
                    break;
                    case 1:
                        user->Savings = atof(token);
                    break;
                    default:
                        break;
                    }
                }
            }
        }
    }
}

// Update bank whenever we make changes to account struct
void updateBank(Account* user)
{
    FILE* bankFile;
    FILE* tempFile;
    bankFile = fopen("BankInfo.txt", "r");
    tempFile = fopen("tempfile.txt", "w");

    char line[100];
    char userId[20];
    char* matchUser;
    
    sprintf(userId, "User: %d ", user->UserID);

    while(fgets(line, sizeof(line), bankFile)){

        matchUser = strstr(line, userId);
        if(matchUser != NULL)
        {
            // replace old savings amount with new savings amount
            // add UserID
            fprintf(tempFile, "User: %d", user->UserID);
            // add checkings Balance
            fprintf(tempFile, " - Checkings Balance: %.2lf", user->Checkings);
            // add savings Balance
            fprintf(tempFile, " - Savings Balance: %.2lf", user->Savings);
            fprintf(tempFile, "\n");
        }
        else
        {
            fputs(line, tempFile);
        }
        
    }

    fclose(bankFile);
    fclose(tempFile);

    remove("BankInfo.txt");
    rename("tempfile.txt", "BankInfo.txt");
}
