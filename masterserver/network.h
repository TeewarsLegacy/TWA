/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Windows net libs
#ifdef _WIN32
    #include <winsock2.h>
#else
	// Linux net livs
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <sys/socket.h>
#endif

#define MAX_PACKET_SIZE 1024

// Net address structure
typedef struct
{
    unsigned int ip;
    unsigned short port;
} NetAddr;

int NetInit(); // Initialization of socket
int NetUPDOpen(unsigned short port); // Open socket
int NetUPDSend(int sock, NetAddr *addr, void *data, int size); // Sending data
int NetUPDRecv(int sock, NetAddr *addr, void *buffer, int maxsize); // Getting data
void NetClose(int sock); // Closing socket

#endif