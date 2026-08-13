#include "inputValid.h"
#include "UI.h"
// checks if has spescial digits
bool hasSpecial(char validate[]){
    bool hasSpecial = false;

    for(int i = 0; i < strlen(validate); i++){
        char curr = validate[i];
        if(curr >= '!' && curr <= '/')
        {
            hasSpecial = true;
            break;
        }
        if(curr >= ':' && curr <= '@')
        {
            hasSpecial = true;
            break;
        }
        if(curr >= '[' && curr <= '`' || curr == '~')
        {
            hasSpecial = true;
            break;
        }
    }
    if(hasSpecial){return true;}
    return false;
}

// checks if contains number
bool hasDigits(char validate[]){

    for(int i = 0; i < strlen(validate); i++)
    {
        if(validate[i] >= '0' && validate[i] <= '9'){
            return true;
        }
    }
    return false;
}

// checks if has capital or lower case letters
bool checkCaps(char validate[]){
    bool hasCaps = false;
    bool hasLower = false;

    for(int i = 0; i < strlen(validate); i++)
    {
        if(validate[i] >= 'A' && validate[i] <= 'Z'){
            hasCaps = true;
        }
        if(validate[i] >= 'a' && validate[i] <= 'z'){
            hasLower = true;
        }
    }
    if(hasCaps && hasLower)return true;
    return false;
}

bool isDuplicate(char validate[]){
    FILE* accFile;
    accFile = fopen("Accounts.txt", "r");

    char line[100];
    char *match;

    while(fgets(line, sizeof(line), accFile) != NULL){
        match = strstr(line, validate);
        if(match != NULL)
        {
            return true;
        }
    }
    fclose(accFile);
    return false;
}
// validates username
bool accValidUser(char validate[])
{
    int validLength = strlen(validate);

    bool isValid = true;

    if(validLength > 15 || validLength < 4)
    {
        printf("Must be between 4 and 15 characters. Try again\n");
        isValid = false;
    }
    else if(hasSpecial(validate))
    {
        printf("Cannot contain any special character");
        isValid = false;
    }
    else if(validate[0] >= '0' && validate[0] <= '9')
    {
        printf("The beginning of username cannot contain a number");
        isValid = false;
    }
    else if(isDuplicate(validate))
    {
        printf("Username is taken please choose another");
        isValid = false;
    }

    if(!isValid)return false;
    return true;
}

// validates password
bool accValidPass(char validate[])
{
    int validLength = strlen(validate);
    bool isValid = true;

    if(validLength > 20 || validLength < 8)
    {
        printf("Must be between 8 and 20 characters. Try again\n");
        isValid = false;
    }
    if(!checkCaps(validate))
    {
        printf("Must have uppercase and lowercase letters");
        isValid = false;
    }
    if(!hasDigits(validate))
    {
        printf("Must have numeric digits");
        isValid = false;
    }
    if(!hasSpecial(validate))
    {
        printf("Must contain atleas one special character");
        isValid = false;
    }
    if(!isValid) return false;
    return true;
}

// validate login info
bool loginValidation(char userName[], char passWord[])
{
    // open account file
    FILE *accFile;
    accFile = fopen("Accounts.txt", "r");

    char bufferLine[MAX_CHAR];

    // create basic account structure including, username and id
    Account user;
    user.UserID = 0;
    strcpy(user.Username, userName);

    // read file line by line while cheacking if it found the username and password
    int id = -1;
    while(fgets(bufferLine, sizeof(bufferLine), accFile) != NULL)
    {
        char *matchUser;
        char *matchPass;
        matchUser = strstr(bufferLine, userName);
        matchPass = strstr(bufferLine, passWord);
        if(matchUser != NULL && matchPass != NULL)
        {
            user.UserID = id;
            break;
        }
        id++;

    }
    fclose(accFile);

    // if it did run the bank account menu function if not send user back to login screen
    if(user.UserID == 0)
    {
        return false;
    }
    else{
        // start of actual program
        accountGUI(user);
    }
    
}
