#include "Server.h"
#include "DebugConsole.h"


// declarate static struct
HWND EntryData::Monitoring::hWindowPaint = NULL;
int EntryData::Monitoring::resol_C = 0;
int MoodConnection::OpenConnection = 0;

void Start_Socket()
{
	while (true)
	{	
		ConnectionData sData1 = Init_Proto(TCP);

		if (sData1.Result_Jr != INVALID_SOCKET)
		{
			MessageToConsole("Start listenning the locak ports...\n");
			OpenServer(sData1);
		}
		MessageToConsole("Try to connect\n");
	}
}
void Start_ServerModule(HWND hWindowPaint, int resol_C)
{
	EntryData::Monitoring mData;                                                                             
		mData.hWindowPaint = hWindowPaint;
		mData.resol_C = resol_C;


	Start_Socket();
}