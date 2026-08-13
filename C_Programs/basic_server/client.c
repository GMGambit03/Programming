#include <arpa/inet.h>
#include <stddef.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int clientFunction(){
    struct sockaddr_in my_addr;
    socklen_t addrLength = sizeof(struct sockaddr);
    int sockFd;

    char *ipAddr = "127.0.0.1";

    sockFd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockFd == -1){
        perror("socket");
        exit(EXIT_FAILURE);
    }

    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = inet_addr(ipAddr);
    my_addr.sin_port = htons(8080);

    if(connect(sockFd, (struct sockaddr *)&my_addr, addrLength) != 0){
        perror("connect");
        exit(EXIT_FAILURE);
    }

    char serverMsg[256];
    ssize_t msgBytes = read(sockFd, serverMsg, sizeof(serverMsg));

    if(msgBytes > 0){
        serverMsg[msgBytes] = '\0';
        printf("%s", serverMsg);
    }

    char *msg = "Hello did we connect from: Client";
    size_t msgLength = strlen(msg);

    if(send(sockFd, msg, msgLength, 0) == -1){
        perror("send");
        exit(1);
    }

    close(sockFd);

    return 0;
    
}