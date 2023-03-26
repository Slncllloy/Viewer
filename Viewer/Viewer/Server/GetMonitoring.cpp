#include "GetMonitoring.h"
#include "_algorithm_.h"

void Init_size_main_dc(struct StretchArhg& upArgh, HWND hWindowPaint)
{
	EntryData::Monitoring mData;

	GetClientRect(mData.hWindowPaint, &upArgh.ConsRect);                            
	upArgh.width_main_dc = upArgh.ConsRect.right;
	upArgh.height_main_dc = upArgh.ConsRect.bottom;
}
void Init_BITMAPINFO(struct StretchArhg& upArgh)
{
	upArgh.bi.bmiHeader.biSize = sizeof(upArgh.bi.bmiHeader);
	upArgh.bi.bmiHeader.biWidth = upArgh.width_sourse_cupture;
	upArgh.bi.bmiHeader.biHeight = -upArgh.height_sourse_cupture;
	upArgh.bi.bmiHeader.biBitCount = 24; 
	upArgh.bi.bmiHeader.biPlanes = 1;
	upArgh.bi.bmiHeader.biCompression = BI_RGB;
}
void Init_size_sourse_cupture(struct StretchArhg& upArgh)
{
	SetProcessDPIAware();

	EntryData::Monitoring mData;                                                                   

	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);

	upArgh.width_sourse_cupture = (int)(width / mData.resol_C);                       
	upArgh.height_sourse_cupture = (int)(height / mData.resol_C);

}
void InitBuffersToStucturing(int iHeightScreen, int iWidthScreen, int Bit_per_pix, struct StructuringDataElements& StucturingData)
{
	StucturingData.Cells_into_full_Packet = iHeightScreen * iWidthScreen * Bit_per_pix;

	StucturingData.cBuffer = std::vector<char>(StucturingData.Cells_into_full_Packet * 2);
	StucturingData.rBuffer = std::vector<char>(StucturingData.Cells_into_full_Packet);

}
void InitStretchScreen(struct StretchArhg& upArgh,HWND hWnd)
{
	upArgh.dc_WindowPaint = GetDC(hWnd);
	SetStretchBltMode(upArgh.dc_WindowPaint, HALFTONE);
}
void Initialize_struct()
{
	EntryData::Monitoring mData;
	StretchArhg upArgh;
	StructuringDataElements StructuringData = { 0 };


	InitStretchScreen(upArgh, mData.hWindowPaint);
	Init_size_sourse_cupture(upArgh);
	Init_BITMAPINFO(upArgh);
	InitBuffersToStucturing(upArgh.height_sourse_cupture, upArgh.width_sourse_cupture, BITS_PER_PIX, StructuringData);
}
void GetMonitorCapture(SOCKET s)
{

	EntryData::Monitoring mData;						// Get HWND window
	StretchArhg StrechScreen;							// To settings Screen
	StructuringDataElements StructuringData;			// Structuring received element to buffer
                    
	InitStretchScreen(StrechScreen, mData.hWindowPaint);
	Init_size_sourse_cupture(StrechScreen);
	Init_BITMAPINFO(StrechScreen);
	InitBuffersToStucturing(StrechScreen.height_sourse_cupture, StrechScreen.width_sourse_cupture, BITS_PER_PIX, StructuringData);

	while (MoodConnection::OpenConnection > 0)
	{
		// For resize window
		Init_size_main_dc(StrechScreen, mData.hWindowPaint);

		StructuringData.Recv_count_cells = recv(s, 
												&StructuringData.cBuffer[StructuringData.iterator], 
												StructuringData.Cells_into_full_Packet, 
												0);

		if (SUCCESS_ALGR == _Queue_(StructuringData, StructuringData.rBuffer, StructuringData.cBuffer))
		{
			if (GDI_ERROR == StretchDIBits(StrechScreen.dc_WindowPaint,
										   0,
										   0,
										   StrechScreen.width_main_dc,
										   StrechScreen.height_main_dc,
										   0,
										   0,
										   StrechScreen.width_sourse_cupture,
										   StrechScreen.height_sourse_cupture,
										   StructuringData.rBuffer.data(),
										   &StrechScreen.bi,
										   DIB_RGB_COLORS,
										   SRCCOPY));
		}
		Sleep(1);
	}

}
