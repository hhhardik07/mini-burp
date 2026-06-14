#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "client.h"
#include "server.h" // for the start server functionn

void start_server(void)
{
    int listen_from_browser_fd;
    char buffer[4096];
ssize_t bytes_read;

    struct sockaddr_in server_addr;
    int browser_fd;;
struct sockaddr_in client_addr;
socklen_t client_len = sizeof(client_addr);

   listen_from_browser_fd  = socket(AF_INET, SOCK_STREAM, 0);//default for tcp and ipv4 

    if (listen_from_browser_fd < 0)
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
           listen_from_browser_fd ,
            (struct sockaddr *)&server_addr,
            sizeof(server_addr)) < 0) //typecastimg server_addr to sockaddr as bind accepts that only and server_addr is strcut sockaddr_in
    {
        perror("bind");//error function
        close(listen_from_browser_fd);
        exit(EXIT_FAILURE);
    }

    printf("Bind successful\n");
    
   //now adding listen which basically listens to the incoming connections 
     if (listen(listen_from_browser_fd , SOMAXCONN) < 0)// SOMAXCONN defines the max no. of queued tcp connections which are unaccepted a socket can hold (backlogs basciaally) kernel stores them
{
    perror("listen");
    close(listen_from_browser_fd );
    exit(EXIT_FAILURE);
}

printf("Listening on port 8080...\n");

//adding acecept which creates a new fd when a client connects 

printf("Waiting for connections...\n");

browser_fd = accept(
    listen_from_browser_fd ,
    (struct sockaddr *)&client_addr,
    &client_len //typecaast again
);
if (browser_fd < 0)
{
    perror("accept");
    close(listen_from_browser_fd );
    exit(EXIT_FAILURE);
}

printf("Client connected!\n");

bytes_read = read(
    browser_fd,
    buffer,
    sizeof(buffer) - 1//as we need space for /0
);

if (bytes_read < 0)
{
    perror("read");

    close(browser_fd);
    close(listen_from_browser_fd );

    exit(EXIT_FAILURE);
}
buffer[bytes_read] = '\0';

printf("\nREQUEST \n");
printf("%s\n", buffer);
printf("===================\n");
char host[256];
char *host_header;

host_header = strstr(buffer, "Host:");

//extracting the hostt

if (host_header == NULL)
{
    printf("Host header not found\n");

    close(browser_fd);
    close(listen_from_browser_fd);

    return;
}
sscanf(
    host_header,
    "Host: %255s",
    host
);

printf("Extracted Host: %s\n", host);

// connect to the websitr 

int target_server_fd;

target_server_fd =
    connect_to_target_server(host);
    
if (target_server_fd < 0)
{
    printf("Failed to connect\n");

    close(browser_fd);
    close(listen_from_browser_fd);

    return;
}
    
    
    
    
    
    
    
    // forwarding the browser requst to the website since after cpnnexipm thsi file owns bothr the browser fd and the target server fd 
ssize_t bytes_sent;

bytes_sent = write(
    target_server_fd,
    buffer,
    bytes_read
);

if (bytes_sent < 0)
{
    perror("write");

    close(target_server_fd);
    close(browser_fd);
    close(listen_from_browser_fd);

    return;
}

printf("Request forwarded\n");


char response[8192];
ssize_t response_bytes;


while ((response_bytes =
        read(
            target_server_fd,
            response,
            sizeof(response) - 1
        )) > 0)
{
    response[response_bytes] = '\0';

    printf("%s", response);

    write(
        browser_fd,
        response,
        response_bytes
    );
}

if (target_server_fd < 0)
{
    printf("Failed to connect\n");

    close(browser_fd);
    close(listen_from_browser_fd);

    return;
}
   
close(browser_fd);
    close(listen_from_browser_fd );
    close(target_server_fd);
}
