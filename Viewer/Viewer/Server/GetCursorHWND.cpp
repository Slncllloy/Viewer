#include "GetCursorHWND.h"

void Init_Buffer(std::vector<char>& buf,
    int index_mult_cx,
    int index_mult_cy,
    int index_remain_cx,
    int index_remain_cy,
    Cursor_info::CPose::CPose_converted_B Cpose_B)
{
    buf[index_mult_cx] = Cpose_B.index_multiplier_x;
    buf[index_mult_cy] = Cpose_B.index_multiplier_y;

    buf[index_remain_cx] = Cpose_B.index_remain_x;
    buf[index_remain_cy] = Cpose_B.index_remain_y;
}
void Convert_Byte(Cursor_info::CPose& CurPose)
{
    CurPose.CPose_Byte.index_multiplier_x = CurPose.win_cx / 256;
    CurPose.CPose_Byte.index_multiplier_y = CurPose.win_cy / 256;

    CurPose.CPose_Byte.index_remain_x = CurPose.win_cx % 256;
    CurPose.CPose_Byte.index_remain_y = CurPose.win_cy % 256;

}
void RangeCountCursPose(int& CursorPose_x, int& CursorPose_y, int WinRight, int WinBottom)
{
    if (CursorPose_x > WinRight)CursorPose_x = WinRight;
    if (CursorPose_x < 0) CursorPose_x = 0;
    if (CursorPose_y > WinBottom)CursorPose_y = WinBottom;
    if (CursorPose_y < 0)CursorPose_y = 0;
}
void Init_Buffer_Socket_CurPose(std::vector<char>& buf,
    int index_mult_cx,
    int index_mult_cy,
    int index_remain_cx,
    int index_remain_cy,
    struct Cursor_info s_Cursor,
    HWND WinHandle)
{
    GetClientRect(WinHandle, &s_Cursor.pWindowSZ);
    GetCursorPos(&s_Cursor.pCurs);
    ScreenToClient(WinHandle, &s_Cursor.pCurs);

    s_Cursor.CursPoseWin.win_cx = s_Cursor.pCurs.x;
    s_Cursor.CursPoseWin.win_cy = s_Cursor.pCurs.y;

    RangeCountCursPose(s_Cursor.CursPoseWin.win_cx, s_Cursor.CursPoseWin.win_cy, s_Cursor.pWindowSZ.right, s_Cursor.pWindowSZ.bottom);

    //std::cout << "X  = " << s_Cursor.CursPoseWin.win_cx << std::endl;
    //std::cout << "Y  " << s_Cursor.CursPoseWin.win_cy << std::endl;

    Convert_Byte(s_Cursor.CursPoseWin);

    Init_Buffer(buf, index_mult_cx, index_mult_cy, index_remain_cx, index_remain_cy, s_Cursor.CursPoseWin.CPose_Byte);
}