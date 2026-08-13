#ifndef GET_UNPACKING_H
#define GET_UNPACKING_H

#include <stdint.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "menus.h"


void clientRecieve(char *userRecv, char *userReq);
classList classStructUnpacking(char *userRecv);
void studentStructunPacking(Student **student, char *userRecv, int *offset, uint32_t studentCount);

#endif