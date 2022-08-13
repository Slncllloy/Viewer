#pragma once
#include <windows.h>
#include <ctime>
#include "EntryStruct.h"
#include "MoodConnection.h"


#define BITS_PER_PIX 3 //set


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
extern inline void Init_size_main_dc(struct StretchArhg& upArgh, HWND hWindowPaint);
extern inline void Init_BITMAPINFO(struct StretchArhg& upArgh);
extern inline void Init_size_sourse_cupture(struct StretchArhg& upArgh);
extern void GetMonitorCapture(SOCKET s);















