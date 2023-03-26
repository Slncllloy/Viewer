#pragma once

#include <stdio.h>
#include <winsock.h>

#define SUCCESS_S				 0
#define ERROR_SET_NONBLOCK		-1
#define ERROR_SETSOCKOPT		-2
#define ERROR_BINDING			-3
#define ERROR_LISTEN			-4
#define FAILED_S				-5


inline static void MessageToConsole(const char* Message) // todo add "..."
{
	printf(Message);
};
inline static void OpenError(const char* Message)
{
	MessageToConsole(Message);
	printf("%lu\n", GetLastError());
};
inline static void ErrorSetNonblock()
{
	int res = WSAGetLastError();

	MessageToConsole("ERROR_SET_NONBLOCK\n");

	if (res == WSANOTINITIALISED)
		MessageToConsole("WSANOTINITIALISED\n");
	if (res == WSAENETDOWN)
		MessageToConsole("WSAENETDOWN\n");
	if (res == WSAEINPROGRESS)
		MessageToConsole("WSAEINPROGRESS\n");
	if (res == WSAENOTSOCK)
		MessageToConsole("WSAENOTSOCK\n");
	if (res == WSAEFAULT)
		MessageToConsole("WSAEFAULT\n");
};
inline static void ErrorSetSockOpt()
{
	int res = WSAGetLastError();

	MessageToConsole("ERROR_SETSOCKOPT\n");

	if (res == WSANOTINITIALISED)
		MessageToConsole("WSANOTINITIALISED\n");
	if (res == WSAENETDOWN)
		MessageToConsole("WSAENETDOWN\n");
	if (res == WSAEFAULT)
		MessageToConsole("WSAEFAULT\n");
	if (res == WSAEINPROGRESS)
		MessageToConsole("WSAEINPROGRESS\n");
	if (res == WSAEINVAL)
		MessageToConsole("WSAEINVAL\n");
	if (res == WSAENETRESET)
		MessageToConsole("WSAENETRESET\n");
	if (res == WSAENOTCONN)
		MessageToConsole("WSAENOTCONN\n");
	if (res == WSAENOTSOCK)
		MessageToConsole("WSAENOTSOCK\n");
};
inline static void ErrorBind()
{
	OpenError("ErrorBind\n");
};
inline static void ErrorListen()
{
	int res = WSAGetLastError();

	MessageToConsole("ERROR_LISTEN\n");

	if (res == WSANOTINITIALISED)
		MessageToConsole("WSANOTINITIALISED\n");
	if (res == WSAENETDOWN)
		MessageToConsole("WSAENETDOWN\n");
	if (res == WSAEADDRINUSE)
		MessageToConsole("WSAEADDRINUSE\n");
	if (res == WSAEINPROGRESS)
		MessageToConsole("WSAEINPROGRESS\n");
	if (res == WSAEINVAL)
		MessageToConsole("WSAEINVAL\n");
	if (res == WSAEISCONN)
		MessageToConsole("WSAEISCONN\n");
	if (res == WSAENOTCONN)
		MessageToConsole("WSAENOTCONN\n");
	if (res == WSAEMFILE)
		MessageToConsole("WSAEMFILE\n");
	if (res == WSAENOBUFS)
		MessageToConsole("WSAENOBUFS\n");
	if (res == WSAENOTSOCK)
		MessageToConsole("WSAENOTSOCK\n");
	if (res == WSAEOPNOTSUPP)
		MessageToConsole("WSAEOPNOTSUPP\n");
};
inline static void ErrorWSAStarup() 
{
	int res = WSAGetLastError();

	MessageToConsole("ERROR_WSAStarup\n");

	if (res == WSASYSNOTREADY)
		MessageToConsole("WSASYSNOTREADY\n");
	if (res == WSAVERNOTSUPPORTED)
		MessageToConsole("WSAVERNOTSUPPORTED\n");
	if (res == WSAEINPROGRESS)
		MessageToConsole("WSAEINPROGRESS\n");
	if (res == WSAEPROCLIM)
		MessageToConsole("WSAEPROCLIM\n");
	if (res == WSAEINVAL)
		MessageToConsole("WSAEINVAL\n");
	if (res == WSAEFAULT)
		MessageToConsole("WSAEFAULT\n");
	
};
