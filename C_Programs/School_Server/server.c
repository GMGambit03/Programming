#include "Headers/network.h"

int serverFunction(){
    struct addrinfo *res, hints, *serverInfo;
    struct sockaddr_storage clientAddr;
    socklen_t clientSize = sizeof(clientAddr);
    int serverFD, clientFd;
    char *serverIP = "127.0.0.1";

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;

    if(getaddrinfo(serverIP, "8080", &hints, &serverInfo) == -1){
        perror("getaddrinfo");
        exit(EXIT_FAILURE);
    }

    for(res = serverInfo; res != NULL; res = res->ai_next){
        serverFD = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

        if(serverFD == -1){
            continue;
        }

        // 1. Create an integer flag set to 1 (true)
        int opt = 1;
        // 2. Set the socket option to reuse the address instantly
        if (setsockopt(serverFD, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
            perror("setsockopt SO_REUSEADDR failed");
            exit(EXIT_FAILURE);
        }

        if(bind(serverFD, res->ai_addr, res->ai_addrlen) == 0){
            break;
        }
    }

    if(listen(serverFD, 0) == -1){
        printf("Something went wronf with listen");
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    clientFd = accept(serverFD, (struct sockaddr *)&clientAddr, &clientSize);
    if(clientFd < 0){
        printf("Something went wronf with accept");
        perror("accept");
        exit(EXIT_FAILURE);
    }

    while(true){
        char buffer[256];
        ssize_t bytes = recv(clientFd, buffer, strlen(buffer) - 1, 0);

        if(bytes != 1){
            buffer[bytes] = '\0';
        }else{
            printf("Error recieving message\n");
            perror("recv");
        }

        ssize_t messageSize;
        char *message = serverRequest(buffer, &messageSize);

        ssize_t bytesSent = send(clientFd, message, messageSize, 0);
        if(bytesSent < 0){
            printf("Something went wrong with sending");
            perror("send");
        }

        printf("Sent: %zd Amount of bytes\n", messageSize);
        break;
    }

    close(clientFd);
    close(serverFD);

    return 0;
}