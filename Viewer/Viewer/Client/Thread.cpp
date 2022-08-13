
#include "Thread.h"

#define COUNT_THREADS 2

void MultiThread(SOCKET sData)
{
    HANDLE hThr[COUNT_THREADS];

    hThr[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MonitorCapture, (LPTHREAD_START_ROUTINE)sData, 0, 0);
    hThr[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RecvData, (LPTHREAD_START_ROUTINE)sData, 0, 0);


    WaitForMultipleObjects(COUNT_THREADS, hThr, TRUE, INFINITE);
}
void MultiThread2(SOCKET sData)
{
    std::thread th1(MonitorCapture, sData);
    std::thread th2(RecvData, sData);

    th1.join();
    th2.join();
}

