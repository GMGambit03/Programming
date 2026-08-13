#include "server.h"
#include "client.h"
#include <string.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    char *server = "server";

    if(strcmp(server, argv[1]) == 0){
        printf("I am the server\n");
        serverFunction();
    }
    else{
        printf("I am the client\n");
        clientFunction();
    }
    return 0;
}
