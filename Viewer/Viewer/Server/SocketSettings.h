#pragma once
#include <winsock2.h>
#include <iostream>

#include "DebugConsole.h"
#include "Threads.h"

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

//#define COUNT_THREADS 2
//#define SUCCESS_S 0
//#define FAILED_S -1

struct ConnectionData
{
	int Result_Jr = SUCCESS_S;

	SOCKADDR_IN SocketAddr = SOCKADDR_IN();
	int SizeADDR = sizeof(struct sockaddr);
	
	SOCKET Socket_Jr = SOCKET();
	SOCKET Socket_II = SOCKET();

	u_int timeval = 0;

	MoodConnection ValidConnect;
};

 extern ConnectionData Init_Listen_Socket(struct ConnectionData sData, bool nonblock_socket = TRUE);
 extern ConnectionData Init_TCP_Socket();
 extern int Listening_Socket(struct ConnectionData &connection);							

