#ifndef LOG_H
#define LOG_H
#include <stdbool.h>
#include <time.h>

// Basically the log object/structure
typedef struct
{
    char contents[256];
    struct tm *timeStampStruct;
    char dateFormat[32];
    int iD;
    char severity[13];

}log_t;


void saveLogs(int* logCountPtr, log_t **logsArray);
bool deleteLog(log_t **logsArray, int* logCountPtr);
void addLog(int* logCountPtr, log_t **logsArray, bool *mainMenu);

#endif