#include "Socket.h"
//#include <winsock2.h>
#include <windows.h>
#include <iostream>

#define SUCCESS_SOCKET 0
#define FAILED_SOCKET -1

SocketData Init_Socket(const char* IP_Addr)
{
    SocketData sData;
    sData.SizeADDR = sizeof(struct sockaddr);
    sData.Socket_II = SOCKET();
    sData.Socket_Jr = SOCKET();

    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 2);

    if (WSAStartup(DLLVersion, &wsaData) == SUCCESS_SOCKET)
    {
        memset(&sData.SocketAddr, 0, sizeof(sData.SocketAddr));

        sData.Socket_Jr = socket(AF_INET, SOCK_STREAM, NULL);
        sData.SocketAddr.sin_family = AF_INET;
        sData.SocketAddr.sin_port = htons(1334);
        sData.SocketAddr.sin_addr.S_un.S_addr = inet_addr(IP_Addr);

        return sData;
    }

    std::cout << "Error to Init_Socket " << std::endl;
    return sData;
}

