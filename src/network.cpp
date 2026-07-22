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

void SetNONBlock(int sock){
// Non-blocking recv
#ifdef _WIN32
    u_long mode = 1;
    ioctlsocket(sock, FIONBIO, &mode);
#else
    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);
#endif
}

int NetUDPOpen(unsigned short port) // Open socket
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

int NetUDPSend(int sock, NetAddr *addr, const void *data, int size) // Sending data
{
    struct sockaddr_in a;

    a.sin_family = AF_INET;
    a.sin_port = htons(addr->port);
    a.sin_addr.s_addr = addr->ip;

    return sendto(sock, (const char*)data, size, 0,
                  (struct sockaddr*)&a, sizeof(a));
}

int NetUDPRecv(int sock, NetAddr *addr, void *buffer, int maxsize)
{
    struct sockaddr_in a;
    #ifdef _WIN32
    int len = sizeof(a);
    #else
    socklen_t len = sizeof(a);
    #endif

    int r = recvfrom(sock, (char*)buffer, maxsize, 0,
                     (struct sockaddr*)&a, &len);

    if (r <= 0)
        return 0;

    addr->ip = a.sin_addr.s_addr;
    addr->port = ntohs(a.sin_port);

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
