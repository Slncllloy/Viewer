#include "Threads.h"

void CheckReturnValueThread2(HANDLE thread)
{
	if (thread == NULL) { printf("Null Thread"); }
}
void OpenThread2(SOCKET Connection)
{
	HANDLE hThr[2];

	hThr[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)GetMonitorCapture, (LPTHREAD_START_ROUTINE)Connection, 0, 0);
	hThr[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Send_Data_Packet, (LPTHREAD_START_ROUTINE)Connection, 0, 0);

	CheckReturnValueThread2(hThr[0]);
	CheckReturnValueThread2(hThr[1]);


	WaitForMultipleObjects(COUNT_THREADS, hThr, TRUE, INFINITE);
}
void OpenLocalDebugThread2(SOCKET Connection)
{
	HANDLE hThr;
	hThr = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)GetMonitorCapture, (LPTHREAD_START_ROUTINE)Connection, 0, 0);
	CheckReturnValueThread2(hThr);
}