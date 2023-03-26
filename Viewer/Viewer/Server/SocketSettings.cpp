#include "SocketSettings.h"

ConnectionData Init_Listen_Socket(struct ConnectionData sData,bool nonblock_socket)
{
	u_long nb = (u_long)nonblock_socket;
	int optVal = 1;											//default
	int size = sizeof(optVal);

	int res = ioctlsocket(sData.Socket_Jr, FIONBIO, &nb); 

	if (res != 0)
	{
		sData.Result_Jr = ERROR_SET_NONBLOCK;
		ErrorSetNonblock();
		return sData;
	}
	res = setsockopt(sData.Socket_Jr, SOL_SOCKET, SO_REUSEADDR, (const char*)&optVal, size); 

	if (res < 0)
	{
		sData.Result_Jr = ERROR_SETSOCKOPT;
		ErrorSetNonblock();
		return sData;
	}
	res = bind(sData.Socket_Jr, (sockaddr*)&sData.SocketAddr, sizeof(sData.SocketAddr));

	if (res == INVALID_SOCKET)
	{
		sData.Result_Jr = ERROR_BINDING;
		ErrorBind();
		return sData;
	}
	res = listen(sData.Socket_Jr, 100);

	if (res == INVALID_SOCKET)
	{
		sData.Result_Jr = ERROR_LISTEN;
		ErrorListen();
		return sData;
	}
	sData.Result_Jr = SUCCESS_S;
	return sData;
}
ConnectionData Init_TCP_Socket()
{
	ConnectionData sData = { 0 };

	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 2);

	if (WSAStartup(DLLVersion, &wsaData) == 0)
	{
		memset(&sData.SocketAddr, 0, sizeof(sData.SocketAddr));

		sData.SocketAddr.sin_family = AF_INET;
		sData.SocketAddr.sin_addr.s_addr = INADDR_ANY;
		sData.SocketAddr.sin_port = htons(1334);
		sData.Socket_Jr = socket(AF_INET, SOCK_STREAM, NULL);

		sData.Result_Jr = SUCCESS_S;

		return Init_Listen_Socket(sData);
	}
	OpenError("Error to Init_Socket \n");
}
int Listening_Socket(struct ConnectionData& Connection)
{
	fd_set fr, fw, fe;

	

	while (1)
	{
		MessageToConsole("Listening_Socket");

		struct timeval tv;
		tv.tv_sec = Connection.timeval;
		tv.tv_usec = Connection.timeval;

		FD_ZERO(&fr);
		FD_ZERO(&fw);
		FD_ZERO(&fe);

		FD_SET(Connection.Socket_Jr, &fr);
		FD_SET(Connection.Socket_Jr, &fe);
		
		Connection.ValidConnect.OpenConnection = select(Connection.Socket_Jr + 1, &fr, nullptr, &fe, &tv);

		if (Connection.ValidConnect.OpenConnection > 0)
		{
			if (FD_ISSET(Connection.Socket_Jr, &fe))
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
			MessageToConsole("NO Connect\n");
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