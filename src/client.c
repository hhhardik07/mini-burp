#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netdb.h>//has the getaddrinfoo api used for dns resolution

#include "client.h"


int connect_to_target_server(const char *host)
{
 struct addrinfo hints;
    struct addrinfo *result;// results is a pointer variable as it will store the the dns result that getaddrinfo api will generate and since it might generate multiple results for a single host so itll poibnt to the adress of the first result it doe

    int target_server_fd;

memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
// this all is for dns resolution
    if (getaddrinfo(
            host,
            "80",
            &hints,
            &result) != 0)//&result so that the adress OF the variable result can be modified thats why &result returns the adress where result is ,it wants to change what result points to 
    {
        fprintf(stderr, "DNS lookup failed\n");
        return -1;
    }
    
      printf("Resolved host: %s\n", host);
      
      // now creating socket 
      
target_server_fd = socket(
   result->ai_family,
 result->ai_socktype,
  result->ai_protocol
    );

    if (target_server_fd < 0)
    {
        perror("socket");

        freeaddrinfo(result);

        return -1;
    }
//connecting to the server normal textbook methodf
    if (connect(
            target_server_fd,
            result->ai_addr,
            result->ai_addrlen) < 0)
    {
        perror("connect");

        close(target_server_fd);

        freeaddrinfo(result);

        return -1;
    }

    printf("Connected to target server\n");

    freeaddrinfo(result);

    return target_server_fd;
}     

