#ifndef MENU_H
#define MENU_H 

#include "logs.h"

void viewLog(log_t **logsArray, int* logCountPtr, bool *mainMenu);
void startingMenu(int* logCountPtr, log_t **logsArray);

#endif