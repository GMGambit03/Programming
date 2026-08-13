#ifndef GET_PACKING_H
#define GET_PACKING_H

#include <string.h>

#include <stdlib.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "menus.h"

char *serverRequest(char *userReq, ssize_t *requestSize);
char *classStructPacking(classList list, ssize_t *requestSize);
char *studentStructPacking(Student *student, uint32_t studentCount, int *studentOffset);

#endif