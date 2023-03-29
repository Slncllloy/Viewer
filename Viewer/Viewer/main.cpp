#include <iostream>
#include"Client/Client.h"
#include"Server/Server.h"

void Server()
{
    std::cout << "Enter resolution (x)" << std::endl;
    std::cout << "(screen.weight_Pix * screen.height_Pix * RGB)/x = Bytes per flame" << std::endl;

    int resol;
    std::cin >> resol;

    if (std::cin.get() == '\n')
    {
        Start_ServerModule(GetConsoleWindow(), resol);
    }
}
void Client()
{
    std::cout << "Enter server IP mashine" << std::endl;
    std::cout << " cmd >> ipconfig >> IPv4" << std::endl;

    std::string IPv4;
    std::cin >> IPv4;

    const char* ip = const_cast<char*>(IPv4.c_str());

    if (std::cin.get() == '\n')
    {
        Start_ClientModule(ip);
    }
}
int main()
{
    std::cout << "Enter 1 - Client" << std::endl;
    std::cout << "Enter 2 - Server" << std::endl;

    int Enter;
    std::cin >> Enter;

    if (Enter == 1)
        Client();
    if (Enter == 2)
        Server();

    return 0;
}