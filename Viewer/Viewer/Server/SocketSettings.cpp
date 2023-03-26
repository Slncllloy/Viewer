#include "SocketSettings.h"

ConnectionData Init_Listen_Socket(struct ConnectionData sData)
{
	u_long nb = 1; // режим сокета

	int res;

	res = ioctlsocket(sData.Socket_Jr, FIONBIO, &nb); // non Blocking socket mode

	if (res != 0)
	{
		std::cout << "Error to set the non block" << std::endl;
		sData.Result_Jr = FAILED_S;
		return sData;
	}
	int optVal = 1; // bind,listen + accept
	int size = sizeof(optVal);
	res = setsockopt(sData.Socket_Jr, SOL_SOCKET, SO_REUSEADDR, (const char*)&optVal, size); // Splitting the PORT

	if (res < 0)
	{
		std::cout << "SETSOCKOPT == INVALID" << std::endl;
		sData.Result_Jr = FAILED_S;
		return sData;
	}
	res = bind(sData.Socket_Jr, (sockaddr*)&sData.SocketAddr, sizeof(sData.SocketAddr));

	if (res == INVALID_SOCKET)
	{
		std::cout << "BIND == INVALID" << std::endl;
		sData.Result_Jr = FAILED_S;
		return sData;
	}
	res = listen(sData.Socket_Jr, 100);

	if (res == INVALID_SOCKET)
	{
		std::cout << "Listen == INVALID" << std::endl;
		sData.Result_Jr = FAILED_S;
		return sData;
	}
	sData.Result_Jr = SUCCESS_S;
	return sData;
}
ConnectionData Init_Socket()
{
	ConnectionData sData = { 0 };

	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 2);

	if (WSAStartup(DLLVersion, &wsaData) == 0) // Ошибок нет
	{
		memset(&sData.SocketAddr, 0, sizeof(sData.SocketAddr));

		sData.SocketAddr.sin_family = AF_INET;
		sData.SocketAddr.sin_addr.s_addr = INADDR_ANY;
		sData.SocketAddr.sin_port = htons(1334);
		sData.Socket_Jr = socket(AF_INET, SOCK_STREAM, NULL);

		sData.Result_Jr = SUCCESS_S;

		return Init_Listen_Socket(sData);
	}
	std::cout << "Error to Init_Socket " << GetLastError()<< std::endl;
}
int Listening_Socket(struct ConnectionData& Connection) //struct SocketData &sData
{
	fd_set fr, fw, fe;

	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;

	while (1)
	{
		struct timeval tv;
		tv.tv_sec = 1;
		tv.tv_usec = 0;

		std::cout << "Listening_Socket" << std::endl;
		FD_ZERO(&fr);
		FD_ZERO(&fw);
		FD_ZERO(&fe);

		FD_SET(Connection.Socket_Jr, &fr);
		FD_SET(Connection.Socket_Jr, &fe);
		
		Connection.ValidConnect.OpenConnection= select(Connection.Socket_Jr + 1, &fr, nullptr, &fe, &tv);

		if (Connection.ValidConnect.OpenConnection > 0)
		{
			if (FD_ISSET(Connection.Socket_Jr, &fe))
			{
				std::cout << "Error exeption " << fr.fd_count << std::endl;
			}
			if (FD_ISSET(Connection.Socket_Jr, &fw))
			{
				std::cout << "ready to write something " << fr.fd_count << std::endl;
			}
			if (FD_ISSET(Connection.Socket_Jr, &fr))
			{
				Connection.Socket_II = accept(Connection.Socket_Jr, (sockaddr*)&Connection.SocketAddr, &Connection.SizeADDR);

				if (Connection.Socket_II != FAILED_S)
				{
					OpenThread2(Connection.Socket_II);
				}

			}
		}
		else if (Connection.ValidConnect.OpenConnection == 0)
		{
			std::cout << "NO Connect " << fr.fd_count << std::endl;
		}
		if (Connection.ValidConnect.OpenConnection < 0)
		{
			std::cout << "Error select " << fr.fd_count << std::endl;
			//Connection.MoodConnection = GetLastError();
			//std::cout <<"Last error of connection" << Connection.MoodConnection << std::endl;
		}
	}
	return 0;
}