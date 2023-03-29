#include "SendData.h"

extern void Init_Buffer_Socket_CurPose(std::vector<char>& buf,
										int index_mult_cx,
										int index_mult_cy,
										int index_remain_cx,
										int index_remain_cy,
										struct Cursor_info s_Cursor,
										HWND WinHandle);
void Init_Buffer_Socket_input(std::vector<char>& buf, Input_Kboard_Mouse s_mi,int index_kI,int index_mI)
{
	s_mi.kInput.Init(buf, index_kI);
	s_mi.mInput.Init(buf, index_mI);

	Sleep(1);

}
void Init_Buffer_Socket_resol_C(std::vector<char>& buf,int index)
{
	EntryData::Monitoring mData;

	buf[index] = ((char)mData.resol_C);
}
void Send_Data_Packet(SOCKET sData)
{
	std::vector<char>buf(COUNT_BUFFER_CELLS);		//todo: test speed

	Input_Kboard_Mouse _input;
	Cursor_info Cinfo;
	EntryData::Monitoring mData;

	_input.Create();
	int res = 0;
	do
	{
		Init_Buffer_Socket_resol_C(buf,0);
		Init_Buffer_Socket_input(buf, _input,1,2);
		Init_Buffer_Socket_CurPose(buf, 3, 4, 5, 6, Cinfo, mData.hWindowPaint);

		res = send(sData, buf.data(), COUNT_BUFFER_CELLS, 0);

		buf[1] = (char)0;
		buf[2] = (char)0;

		Sleep(1);
	} while (res != -1);

	_input.Distroy();
	MoodConnection::SignalConnection(0);
}