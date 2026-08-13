#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHAR 1000

#ifndef ACCOUNT_H
#define ACCOUNT_H

typedef struct
{
    char Username[16];
    int UserID;
    float Checkings;
    float Savings;
}Account;
#endif

bool hasSpecial(char validate[]);
bool hasDigit(char validate[]);
bool checkCaps(char validate[]);
bool isDuplicate(char validate[]);
bool accValidUser(char validate[]);
bool accValidPass(char validate[]);
bool loginValidation(char userName[], char passWord[]);
