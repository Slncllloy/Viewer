#pragma once

#include "Monitoring_side.h"
#include <vector>

#define FAILED_SOCKET -1

struct sRecvData
{
	int result = 0;

	struct Input
	{
		int mouseInput = 0;
		int keyboardInput = 0;
	};
	struct CursorPose
	{
		int index_mult_cx = 0;
		int index_mult_cy = 0;
		int index_remain_cx = 0;
		int index_remain_cy = 0;

		int SetCursPoseX = 0;
		int SetCursPoseY = 0;
	};
	Input kmInput;
	CursorPose CPose;

	//monitor_capture mcArgh;
};
extern void receive_CursorPose(std::vector<char>& buf);
extern void receive_resolution_monitoring(std::vector<char>& buf);
extern void receive_input(std::vector<char>& buf);
extern void RecvData(SOCKET sData);

