#pragma once
#include<Windows.h>
#include <vector>
#include<iostream>

struct Cursor_info
{
    struct CPose
    {
        struct CPose_converted_B
        {
            int index_multiplier_x = 0;
            int index_multiplier_y = 0;
            int index_remain_x = 0;
            int index_remain_y = 0;
        };
        int win_cx = 0;
        int win_cy = 0;

        CPose_converted_B CPose_Byte;
    };
    POINT pCurs;
    RECT pWindowSZ;

    CPose CursPoseWin;
};

extern void Init_Buffer(std::vector<char>& buf,
                        int index_mult_cx,
                        int index_mult_cy,
                        int index_remain_cx,
                        int index_remain_cy,
                        Cursor_info::CPose::CPose_converted_B Cpose_B);
extern void Convert_Byte(Cursor_info::CPose& CurPose);
extern void RangeCountCursPose(int& CursorPose_x, int& CursorPose_y, int WinRight, int WinBottom);
extern void Init_Buffer_Socket_CurPose(std::vector<char>& buf,
                                       int index_mult_cx,
                                       int index_mult_cy,
                                       int index_remain_cx,
                                       int index_remain_cy,
                                       struct Cursor_info s_Cursor,
                                       HWND WinHandle);