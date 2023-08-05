#include "socketUtil.h"


//Create Ipv4 socket descriptor
int createTCPIpv4Socket()
{
    return socket(AF_INET , SOCK_STREAM , 0);
}

//create and initialize an Ipv4 socket address structure
struct sockaddr_in * createIpv4Address(char *ip , int port)
{
    struct sockaddr_in * address = malloc(sizeof(struct sockaddr_in));

    address -> sin_family = AF_INET;
    address -> sin_port = htons(port);

    if(strlen(ip) != 0)
	inet_pton(AF_INET , ip , &address -> sin_addr.s_addr);
    else
	address -> sin_addr.s_addr = INADDR_ANY;

    return address;
}

