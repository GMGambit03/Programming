#include "Headers/network.h"

int clientFunction(){
    struct sockaddr_in serverAddy;
    socklen_t serverSize = sizeof(serverAddy);
    struct in_addr serverIpBin;
    int clientFD;
    char *serverIp = "127.0.0.1";
    int portNum = 8080;

    if(inet_pton(AF_INET, serverIp, &serverIpBin) < 0){
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }

    serverAddy.sin_family = AF_INET;
    serverAddy.sin_addr = serverIpBin;
    serverAddy.sin_port = htons(portNum);

    clientFD = socket(AF_INET, SOCK_STREAM, 0);
    if(clientFD == -1){
        perror("socket");
        exit(EXIT_FAILURE);
    }

    if(connect(clientFD, (struct sockaddr *)&serverAddy, serverSize) < 0){
        perror("connect");
        exit(EXIT_FAILURE);
    }

    while(true){
        char *request = startMenu();
        send(clientFD, request, strlen(request), 0);

        char buffer[4096];
        ssize_t bytes = recv(clientFD, buffer, strlen(buffer) - 1, 0);

        if(bytes != -1){
            buffer[bytes] = '\0';
            printf("Recieved %zd bytes\n", bytes);
        }else{
            printf("Error recieving message\n");
            perror("recv");
        }

        // Unpack data from server first in unpacking.c then
        // Display what user requested in the menus.c
        clientRecieve(buffer, request);

        break;
    }

    


    return 0;
}