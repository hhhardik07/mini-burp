#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "server.h" // for the start server functionn

void start_server(void)
{
    int server_fd;
    char buffer[4096];
ssize_t bytes_read;

    struct sockaddr_in server_addr;
    int client_fd;
struct sockaddr_in client_addr;
socklen_t client_len = sizeof(client_addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);//default for tcp and ipv4 

    if (server_fd < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    printf("Socket created\n");

    memset(&server_addr, 0, sizeof(server_addr)); //for resettinf the values can also use bzero function but it accepts only 2 args ig 

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);//htons converts int to bytes 
    server_addr.sin_addr.s_addr = INADDR_ANY;
//now binding to the socket 
    if (bind(
            server_fd,
            (struct sockaddr *)&server_addr,
            sizeof(server_addr)) < 0) //typecastimg server_addr in to serveraddr (generic value as bind accepts)
    {
        perror("bind");//error function
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Bind successful\n");
    
   //now adding listen which basically listens to the incoming connections 
     if (listen(server_fd, SOMAXCONN) < 0)// SOMAXCONN defines the max no. of queued tcp connections which are unaccepted a socket can hold (backlogs basciaally) kernel stores them
{
    perror("listen");
    close(server_fd);
    exit(EXIT_FAILURE);
}

printf("Listening on port 8080...\n");

//adding acecept which creates a new fd when a client connects 

printf("Waiting for connections...\n");

client_fd = accept(
    server_fd,
    (struct sockaddr *)&client_addr,
    &client_len //typecaast again
);
if (client_fd < 0)
{
    perror("accept");
    close(server_fd);
    exit(EXIT_FAILURE);
}

printf("Client connected!\n");

bytes_read = read(
    client_fd,
    buffer,
    sizeof(buffer) - 1//as we need space for /0
);

if (bytes_read < 0)
{
    perror("read");

    close(client_fd);
    close(server_fd);

    exit(EXIT_FAILURE);
}
buffer[bytes_read] = '\0';

printf("\nREQUEST \n");
printf("%s\n", buffer);
printf("===================\n");


   
close(client_fd);
    close(server_fd);
}
