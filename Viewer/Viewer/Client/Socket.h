#pragma once
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#pragma warning(disable:4996)

struct SocketData
{
    SOCKADDR_IN SocketAddr;
    int SizeADDR = 0;

    SOCKET Socket_Jr = 0;
    SOCKET Socket_II = 0;
};

SocketData Init_Socket(const char* IP_Addr);


