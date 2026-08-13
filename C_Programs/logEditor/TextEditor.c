#include <stdio.h>
#include <stdlib.h>

#include "headers/menu.h"

int main(int argc, char const *argv[])
{
    int logCount = 0;
    log_t *logsArray = malloc((logCount + 1) * sizeof(log_t));

    startingMenu(&logCount, &logsArray);
    free(logsArray);

    return 0;
}
