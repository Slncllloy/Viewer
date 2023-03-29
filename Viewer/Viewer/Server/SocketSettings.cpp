#include "SocketSettings.h"

ConnectionData Init_Proto(u_int proto)
{
	ConnectionData sData;

	switch (proto)
	{
	case 1:
		return Init_TCP_Socket(sData);
	case 2:
		return sData;
	}
}
ConnectionData Init_Listen_Socket(struct ConnectionData sData, u_long nonblock_socket,char OptValMode, int backlog)
{
 
	if (ioctlsocket(sData.Socket_Jr, FIONBIO, &nonblock_socket)  // why work,where is nonblock_socket variable ?
		!= 0)
		goto Error;

	if (setsockopt(sData.Socket_Jr, SOL_SOCKET, SO_REUSEADDR, (char*)&OptValMode, sizeof(OptValMode))
		< 0)
		goto Error;

	if (bind(sData.Socket_Jr, (sockaddr*)&sData.SocketAddr, sizeof(sData.SocketAddr))
		== INVALID_SOCKET)
		goto Error;

	if (listen(sData.Socket_Jr, backlog)
		== INVALID_SOCKET)
		goto Error;
	return sData;

Error:
	CheckErrorSocket();
	return sData;
}
ConnectionData Init_TCP_Socket(ConnectionData sData)
{

	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 2);

	if (WSAStartup(DLLVersion, &wsaData) == 0)
	{
		sData.SocketAddr.sin_family =			AF_INET;
		sData.SocketAddr.sin_addr.s_addr =		INADDR_ANY;
		sData.SocketAddr.sin_port =				htons(1334);
		sData.Socket_Jr =						socket(AF_INET, SOCK_STREAM, NULL);

		sData.Result_Jr = SUCCESS_S;

		return Init_Listen_Socket(sData);
	}
	else
		ErrorWSAStarup();
}
int OpenServer(struct ConnectionData& Connection,int reconnect_time_per_sec)
{
	fd_set fr, fw, fe;

	

	while (1)												//todo: set condition
	{
		MessageToConsole("Listening_Socket	\n");

		struct timeval tv;
		tv.tv_sec = reconnect_time_per_sec;
		tv.tv_usec = reconnect_time_per_sec;

		FD_ZERO(&fr);
		FD_ZERO(&fw);
		FD_ZERO(&fe);

		FD_SET(Connection.Socket_Jr, &fr);
		FD_SET(Connection.Socket_Jr, &fe);
		
		Connection.ValidConnect.OpenConnection = select(Connection.Socket_Jr + 1, &fr, nullptr, &fe, &tv);		//todo: debug.h return

		if (Connection.ValidConnect.OpenConnection > 0)
		{
			if (FD_ISSET(Connection.Socket_Jr, &fe))							//todo: realize error
			{
				MessageToConsole("Error exeption\n");								
				//std::cout << "Error exeption " << fr.fd_count << std::endl;
			}
			if (FD_ISSET(Connection.Socket_Jr, &fw))
			{
				MessageToConsole("ready to write something \n");
				//std::cout << "ready to write something " << fr.fd_count << std::endl;
			}
			if (FD_ISSET(Connection.Socket_Jr, &fr))
			{
				Connection.Socket_II = accept(Connection.Socket_Jr, (sockaddr*)&Connection.SocketAddr, &Connection.SizeADDR);

				if (Connection.Socket_II != INVALID_SOCKET)
				{
					OpenThread2(Connection.Socket_II);
				}

			}
		}
		else if (Connection.ValidConnect.OpenConnection == 0)
		{
			MessageToConsole("no Connect\n");
			//std::cout << "NO Connect " << fr.fd_count << std::endl;
		}
		if (Connection.ValidConnect.OpenConnection < 0)
		{
			MessageToConsole("Error select\n");
			//std::cout << "Error select " << fr.fd_count << std::endl;
		}
	}
	return 0;
}