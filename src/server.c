#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include "server.h" //for the start server functionn

void start_server(void)
{
    int server_fd;

    server_fd = socket(AF_INET, SOCK_STREAM, 0); //for a tcp server these are the default values of the args 

    if (server_fd < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
     else {
    printf("Socket created\n");
}
}
