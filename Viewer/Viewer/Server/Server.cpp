#include "SocketSettings.h"
#include "Server.h"

HWND EntryData::Monitoring::hWindowPaint = NULL;
int EntryData::Monitoring::resol_C = 0;
int MoodConnection::OpenConnection = 0;

void Start_Socket()
{
	while (true)
	{
		ConnectionData sData1 = Init_Socket();

		if (sData1.Result_Jr == SUCCESS_S)
		{
			std::cout << "Start listenning the locak ports..." << std::endl;
			Listening_Socket(sData1);
		}
		std::cout << "No connect" << std::endl;
	}
}
void Start_ServerModule(HWND hWindowPaint, int resol_C)
{
	EntryData::Monitoring mData;                                                                             // test
	mData.hWindowPaint = hWindowPaint;
	mData.resol_C = resol_C;

	Start_Socket();
}