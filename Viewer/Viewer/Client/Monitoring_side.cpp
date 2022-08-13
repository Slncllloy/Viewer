#include "Monitoring_side.h"
#include <vector>
#include <iostream>

#define BITS_PER_PIX 3
#define FAILED_SOCKET -1



void CursorDraw(HDC memdc, HWND win)
{
    CURSORINFO cursor = { sizeof(cursor) };
    GetCursorInfo(&cursor);
    if (cursor.flags == CURSOR_SHOWING) {
        RECT rect;
        GetWindowRect(win, &rect);
        ICONINFO info = { sizeof(info) };
        GetIconInfo(cursor.hCursor, &info);
        /*const int x = cursor.ptScreenPos.x - rect.left - rect.left - info.xHotspot;
        const int y = cursor.ptScreenPos.y - rect.top - rect.top - info.yHotspot;*/
        const int x = (cursor.ptScreenPos.x - rect.left - rect.left - info.xHotspot);
        const int y = (cursor.ptScreenPos.y - rect.top - rect.top - info.yHotspot);
        BITMAP bmpCursor = { 0 };
        GetObject(info.hbmColor, sizeof(bmpCursor), &bmpCursor);
        DrawIconEx(memdc, x, y, cursor.hCursor, bmpCursor.bmWidth, bmpCursor.bmHeight,0, NULL, DI_NORMAL);
    }
}
inline void Cleaner(struct monitor_capture& mcArgh, HBITMAP& hbitmap, HGDIOBJ& oldbmp)
{
    DeleteObject(hbitmap);
    DeleteObject(oldbmp);
    ReleaseDC(NULL, mcArgh.dc_receiver);
    SelectObject(mcArgh.dc_receiver_comptbl, oldbmp);
    DeleteDC(mcArgh.dc_receiver_comptbl);
}
inline void Init_dc_receiver(struct monitor_capture& mcArgh)
{
    HWND win = GetDesktopWindow();

    mcArgh.dc_receiver = GetDC(win);
    mcArgh.dc_receiver_comptbl = CreateCompatibleDC(mcArgh.dc_receiver);
}
inline void Init_BITMAPINFO(struct monitor_capture& mcArgh)
{
    mcArgh.bi.bmiHeader.biSize = sizeof(mcArgh.bi.bmiHeader);
    mcArgh.bi.bmiHeader.biBitCount = 24;//set
    mcArgh.bi.bmiHeader.biPlanes = 1;
    mcArgh.bi.bmiHeader.biCompression = BI_RGB;
    mcArgh.bi.bmiHeader.biWidth = mcArgh.width_paint_dc;
    mcArgh.bi.bmiHeader.biHeight = -mcArgh.height_paint_dc;
}
inline void Init_size_screen(struct monitor_capture& mcArgh)
{
    SetProcessDPIAware();

    mcArgh.cx_screen_width = GetSystemMetrics(SM_CXSCREEN);
    mcArgh.cy_screen_height = GetSystemMetrics(SM_CYSCREEN);

}
inline void Init_size_paint_dc(struct monitor_capture& mcArgh)
{
    Init_size_screen(mcArgh);

    mcArgh.width_paint_dc = (int)(mcArgh.cx_screen_width / mcArgh.resol_K);
    mcArgh.height_paint_dc = (int)(mcArgh.cy_screen_height / mcArgh.resol_K);

}
void MonitorCapture(SOCKET s)
{
    monitor_capture mcArgh;
    int res_send = 0;

    while (res_send != -1)                                    
    {
        while (res_send != -1 && mcArgh.resol_K != 0)
        {
            Init_size_paint_dc(mcArgh);
            Init_BITMAPINFO(mcArgh);

            int count = mcArgh.width_paint_dc * mcArgh.height_paint_dc * BITS_PER_PIX;
            std::vector<char>foo(count);

            Init_dc_receiver(mcArgh);

            HBITMAP hbitmap = CreateCompatibleBitmap(mcArgh.dc_receiver, mcArgh.cx_screen_width, mcArgh.cy_screen_height);
            HGDIOBJ oldbmp = SelectObject(mcArgh.dc_receiver_comptbl, hbitmap);


            SetStretchBltMode(mcArgh.dc_receiver_comptbl, HALFTONE);
            StretchBlt(mcArgh.dc_receiver_comptbl,
                       0,
                       0,
                       mcArgh.width_paint_dc,
                       mcArgh.height_paint_dc,
                       mcArgh.dc_receiver,
                       0,
                       0,
                       mcArgh.cx_screen_width,
                       mcArgh.cy_screen_height,
                       SRCCOPY | CAPTUREBLT);

            GetDIBits(mcArgh.dc_receiver_comptbl, hbitmap, 0, mcArgh.height_paint_dc, foo.data(), &mcArgh.bi, DIB_RGB_COLORS);
            res_send = send(s, foo.data(), count, 0);
            //std::cout << "bites in buffer" << res_send << std::endl;

            Cleaner(mcArgh, hbitmap, oldbmp);

            Sleep(1);
        }
    }
}




