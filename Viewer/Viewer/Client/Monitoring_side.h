#pragma once
#include "Socket.h"
#include <windows.h>
                                   // поменять вызов + изменение через сокет

struct monitor_capture
{
    int cx_screen_width = 0;
    int cy_screen_height = 0;

    int width_paint_dc = 0;
    int height_paint_dc = 0;


    BITMAPINFO bi = { 0 };

    HDC dc_receiver = nullptr;
    HDC dc_receiver_comptbl = nullptr;

    static double resol_K;
};


void CursorDraw(HDC memdc, HWND win);
inline void Cleaner(struct monitor_capture& mcArgh, HBITMAP& hbitmap, HGDIOBJ& oldbmp);
inline void Init_dc_receiver(struct monitor_capture& mcArgh);
inline void Init_BITMAPINFO(struct monitor_capture& mcArgh);
inline void Init_size_screen(struct monitor_capture& mcArgh);
inline void Init_size_paint_dc(struct monitor_capture& mcArgh);
void MonitorCapture(SOCKET s);





