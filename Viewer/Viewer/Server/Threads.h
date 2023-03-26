#include "GetMonitoring.h"			//open GetMonitorCapture
#include "SendData.h"				//open Send_Data_Packet
#include "DebugConsole.h"
#include <thread>

#define COUNT_THREADS 2

extern void CheckReturnValueThread2(HANDLE thread);
extern void OpenThread2(SOCKET Connection);
extern void OpenLocalDebugThread2(SOCKET Connection);
