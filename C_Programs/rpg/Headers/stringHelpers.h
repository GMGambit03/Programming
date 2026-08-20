#ifndef STRHELPER
#define STRHELPER

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void clearScreen();
bool clearBuffer(int s, char userInput[s]);
bool checkName(int s, char userInput[s]);
bool checkChars(char *userInput);
bool checkFirstDigit(char *userInput);
char *toUpper(char *string);
void charFiller(int length, char charc);

double max(double a, double b);

#endif