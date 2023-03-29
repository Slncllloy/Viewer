#pragma once
#include <windows.h>
#include <ctime>
#include "EntryStruct.h"
#include "MoodConnection.h"


#define BITS_PER_PIX 3


struct StretchArhg                                                                                
{
	HDC dc_WindowPaint = NULL;
	RECT ConsRect;
	BITMAPINFO bi = { 0 };

	int width_sourse_cupture = 0;
	int height_sourse_cupture = 0;

	int width_main_dc = 0;
	int height_main_dc = 0;

};


extern void Init_size_main_dc(struct StretchArhg& upArgh, HWND hWindowPaint);
extern void Init_BITMAPINFO(struct StretchArhg& upArgh);
extern void Init_size_sourse_cupture(struct StretchArhg& upArgh, const int resolution);
extern void InitBuffersToStucturing(int iHeightScreen,
									int iWidthScreen,
									int Bit_per_pix,
									struct StructuringDataElements& StucturingData);
extern void InitStretchScreen(struct StretchArhg& upArgh, HWND hWnd);
extern void GetMonitorCapture(SOCKET s);















