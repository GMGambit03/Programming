#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int serverFunction(){
    struct sockaddr_storage clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    struct addrinfo hints, *serverinfo, *res;
    int serverFD, clientFD;
    char *serverAddr = "127.0.0.1";

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int info = getaddrinfo(serverAddr, "8080", &hints, &serverinfo);
    if(info != 0){
        perror("getaddrinfo");
        exit(EXIT_FAILURE);
    }

    for(res = serverinfo; res != NULL; res = res->ai_next){
        serverFD = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

        if(serverFD == -1){
            continue;
        }

        if(bind(serverFD, res->ai_addr, res->ai_addrlen) == 0){
            break;
        }
        close(serverFD);
    }
    if(res == NULL){
        fprintf(stderr, "Could not bind to any address");
        exit(1);
    }

    if(listen(serverFD, 1) != 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }
    clientFD = accept(serverFD, (struct sockaddr *)&clientAddr, &clientAddrLen);

    char *msg = "Did we connect";

    send(clientFD, msg, strlen(msg), 0);

    char clientMsg[256];
    ssize_t msgBytes = read(clientFD, clientMsg, sizeof(clientMsg));

    if(msgBytes > 0){
        clientMsg[msgBytes] = '\0';
        printf("%s", clientMsg);
    }
    else if(msgBytes < 0){
        perror("read \n");
    }

    printf("we recieved %zd bytes from client \n", msgBytes);

    close(serverFD);
    close(clientFD);
    freeaddrinfo(serverinfo);

    return 0;
}