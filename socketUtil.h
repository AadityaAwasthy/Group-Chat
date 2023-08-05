#ifndef SOCKETUTIL_H
#define SOCKETUTIL_H

#include<stdio.h>
#include<malloc.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdbool.h>
#include<unistd.h>

int createTCPIpv4Socket();
struct sockaddr_in * createIpv4Address(char *, int);

#endif /* SOCKETUTIL_H */

