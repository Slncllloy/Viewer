#include "GetMonitoring.h"
#include "_algorithm_.h"

inline void Init_size_main_dc(struct StretchArhg& upArgh, HWND hWindowPaint)
{
	EntryData::Monitoring mData;

	GetClientRect(mData.hWindowPaint, &upArgh.ConsRect);                            
	upArgh.width_main_dc = upArgh.ConsRect.right;
	upArgh.height_main_dc = upArgh.ConsRect.bottom;
}
inline void Init_BITMAPINFO(struct StretchArhg& upArgh)
{
	upArgh.bi.bmiHeader.biSize = sizeof(upArgh.bi.bmiHeader);
	upArgh.bi.bmiHeader.biWidth = upArgh.width_sourse_cupture;
	upArgh.bi.bmiHeader.biHeight = -upArgh.height_sourse_cupture;
	upArgh.bi.bmiHeader.biBitCount = 24; //set
	upArgh.bi.bmiHeader.biPlanes = 1;
	upArgh.bi.bmiHeader.biCompression = BI_RGB;
}
inline void Init_size_sourse_cupture(struct StretchArhg& upArgh)
{
	SetProcessDPIAware();

	EntryData::Monitoring mData;                                                                   

	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);

	upArgh.width_sourse_cupture = (int)(width / mData.resol_C);                       
	upArgh.height_sourse_cupture = (int)(height / mData.resol_C);

}
void GetMonitorCapture(SOCKET s)
{

	EntryData::Monitoring mData;		
	StretchArhg upArgh;
	AlgorithmData alg_Data = { 0 };

	int alg_res = 0;

	upArgh.dc_WindowPaint = GetDC(mData.hWindowPaint);                               

	Init_size_sourse_cupture(upArgh);
	Init_BITMAPINFO(upArgh);

	alg_Data.Cells_into_full_Packet = upArgh.height_sourse_cupture * upArgh.width_sourse_cupture * BITS_PER_PIX;

	std::vector<char>dirty_Buf(alg_Data.Cells_into_full_Packet * 2);
	std::vector<char>Packet_bits_cupture(alg_Data.Cells_into_full_Packet);

	SetStretchBltMode(upArgh.dc_WindowPaint,HALFTONE);

	while (MoodConnection::OpenConnection>0)
	{
		Init_size_main_dc(upArgh, mData.hWindowPaint);

		alg_Data.Recv_count_cells = recv(s, &dirty_Buf[alg_Data.iterator], alg_Data.Cells_into_full_Packet, 0);
		//std::cout << "Recv_count_cells = "<< alg_Data.Recv_count_cells << std::endl;

		int alg_res = _Queue_(alg_Data, Packet_bits_cupture, dirty_Buf);

		if (alg_res == SUCCESS_ALGR)
		{
			if (GDI_ERROR == StretchDIBits(upArgh.dc_WindowPaint,
						        0,
							0,
							upArgh.width_main_dc,
							upArgh.height_main_dc,
							0,
							0,
							upArgh.width_sourse_cupture,
							upArgh.height_sourse_cupture,
							Packet_bits_cupture.data(),
							&upArgh.bi,
							DIB_RGB_COLORS,
							SRCCOPY))
			//std::cout << "StrtchDibBits = 0" << GetLastError() << std::endl;
		}
		Sleep(1);
	}

}
