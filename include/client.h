#ifndef CLIENT_H
#define CLIENT_H

int connect_to_target_server(const char *host);//takes string as an input which on executing will return a fd

#endif

// host as a pointer as memst will want a pointer to clear later and also since itll accept a string so char will only hold one character so *host will store the address of the first character of the string for ease of access 
