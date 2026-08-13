#include "Headers/network.h"

int main(int argc, char *argv[]){
    if(argc < 2){
        printf(" Password is missing, this requires 1 argument");
        exit(EXIT_FAILURE);
    }
    char *server_id = "6529";
    char *client_id = "12472";

    if(!strcmp(server_id, argv[1])){
        serverFunction();
    }
    else if(!strcmp(client_id, argv[1])){
        clientFunction();
    }
    return 0;
}