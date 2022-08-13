#include "RecvData.h"
#include <iostream>

#define COUNT_BUFFER_CELLS 7
#define BITS_PER_PIX 3//set


void receive_CursorPose(std::vector<char>& buf)        // добавить коэффицент для перемещения 
{
	 //размеры экрана/размеры консоли

	int index_mult_cx = (BYTE)buf[3];
	int index_mult_cy = (BYTE)buf[4];
	int index_remain_cx = (BYTE)buf[5];
	int index_remain_cy = (BYTE)buf[6];

	int SetCursPoseX = index_mult_cx * 256;
	int SetCursPoseY = index_mult_cy * 256;

	SetCursPoseX += index_remain_cx;
	SetCursPoseY += index_remain_cy;

	int X=SetCursPoseX * 2; //
	int Y=SetCursPoseY * 2.25;
	std::cout << "X" << X << std::endl;
	std::cout << "Y" << Y << std::endl;
	SetCursorPos(X, Y);
}
void receive_resolution_monitoring(std::vector<char>& buf)
{
	monitor_capture mcArgh;
	mcArgh.resol_K = (int)buf[0];
	//std::cout << "received resol = " << mcArgh.resol_K << std::endl;
}
void receive_input(std::vector<char>& buf)
{
	int keyboardInput = (int)buf[1];
	int mouseInput = (int)buf[2];

	if (mouseInput == 1)
	{
		mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
	}
	if (mouseInput == 2)
	{
		mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}
	std::cout << "received mouse input = " << mouseInput << std::endl;
	std::cout << "received keyboard input = " << keyboardInput << std::endl;

	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.wVk = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.dwFlags = KEYEVENTF_SCANCODE;
	ip.ki.wScan = keyboardInput;

	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}
void RecvData(SOCKET sData)
{

	sRecvData receiveData;
	std::vector<char>buf(COUNT_BUFFER_CELLS);

	while (receiveData.result != FAILED_SOCKET)
	{
		receiveData.result = recv(sData, buf.data(), COUNT_BUFFER_CELLS, 0);

		receive_resolution_monitoring(buf);
		receive_input(buf);
		receive_CursorPose(buf);

	}
}
