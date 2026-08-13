#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UI.h"

#define MAX_CHAR 1000

typedef struct Account user;

int addUsers();
void addBankInfo(int userId);
void addAccInfo(char userName[], char password[]);
void getBankInfo(Account* user);
void updateBank(Account* user);