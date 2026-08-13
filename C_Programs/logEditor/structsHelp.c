#include "headers/structsHelp.h"
// Formats the time struct so its human readable
void timeStampGen(log_t* log)
{
    snprintf(log->dateFormat, sizeof(log->dateFormat), " [%04d - %02d - %02d] [%02d:%02d]", log->timeStampStruct->tm_year + 1900, log->timeStampStruct->tm_mon + 1, log->timeStampStruct->tm_mday, log->timeStampStruct->tm_hour, log->timeStampStruct->tm_min);
}

// Turns user input from add log into a string 
bool getSeverity(int severityInt, log_t* log){
    bool valid = true;
    switch (severityInt)
    {
        case 0:
            sprintf(log->severity, "Emergency");
        break;
        case 1:
            sprintf(log->severity, "Alert");
        break;
        case 2:
            sprintf(log->severity, "Critical");
        break;
        case 3:
            sprintf(log->severity, "Error");
        break;
        case 4:
            sprintf(log->severity, "Warning");
        break;
        case 5:
            sprintf(log->severity, "Notification");
        break;
        case 6:
            sprintf(log->severity, "Informational");
        break;
        case 7:
            sprintf(log->severity, "Debugging");
        break;
        default:
            printf("Put in something valid pls");
            getchar();
            deleteLines(0);
            valid = false;
        break;
    }
    if(!valid) return false;
    return true;
}
