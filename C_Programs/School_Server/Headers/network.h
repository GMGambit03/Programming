#ifndef NETWORK_H
#define NETWORK_H

#include <stdlib.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "packing.h"
#include "unpacking.h"

#define VIEW_CLASSES 2

int serverFunction();
int clientFunction();

#endif