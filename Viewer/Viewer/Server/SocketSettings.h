#pragma once
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include "GetMonitoring.h"
#include <iostream>


#pragma warning(disable:4996)

#define COUNT_THREADS 2
#define SUCCESS_S 0
#define FAILED_S -1

struct ConnectionData
{
	int Result_Jr = SUCCESS_S;

	SOCKADDR_IN SocketAddr = SOCKADDR_IN();
	int SizeADDR = sizeof(struct sockaddr);
	
	SOCKET Socket_Jr = SOCKET();
	SOCKET Socket_II = SOCKET();

	MoodConnection ValidConnect;
};

 extern void MultiThread2(struct ConnectionData sData1);
 extern ConnectionData Init_Listen_Socket(struct ConnectionData sData);  //static
 extern ConnectionData Init_Socket();
 extern void MultiThread(ConnectionData sData);
 extern int Listening_Socket(struct ConnectionData &connection);//struct SocketData& sData

