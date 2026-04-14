/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include "network.h"

int NetInit() // Initialization of socket
{
#ifdef _WIN32
    WSADATA wsa;
    return WSAStartup(MAKEWORD(2,2), &wsa);
#else
    return 0;
#endif
}

int NetUPDOpen(unsigned short port) // Open socket
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr*)&addr, sizeof(addr));

    return sock;
}

int NetUPDSend(int sock, NetAddr *addr, void *data, int size) // Sending data
{
    struct sockaddr_in a;

    a.sin_family = AF_INET;
    a.sin_port = htons(addr->port);
    a.sin_addr.s_addr = addr->ip;

    return sendto(sock, data, size, 0,
                  (struct sockaddr*)&a, sizeof(a));
}

int NetUPDRecv(int sock, NetAddr *addr, void *buffer, int maxsize) // Getting data
{
    struct sockaddr_in a;
    socklen_t len = sizeof(a);

    int r = recvfrom(sock, buffer, maxsize, 0,
                     (struct sockaddr*)&a, &len);

    if(r > 0)
    {
        addr->ip = a.sin_addr.s_addr;
        addr->port = ntohs(a.sin_port);
    }

    return r;
}

void NetClose(int sock) // Closing socket
{
#ifdef _WIN32
    closesocket(sock);
    WSACleanup();
#else
    close(sock);
#endif
}
