#pragma once
#include <vector>

#include "EntryStruct.h"
#include "Input.h"
#include "GetCursorHWND.h"
#include "MoodConnection.h"


#define COUNT_BUFFER_CELLS 7

void Init_Buffer_Socket_input(std::vector<char>& buf, Input_Kboard_Mouse s_mi, int index_kI, int index_mI);
void Init_Buffer_Socket_resol_C(std::vector<char>& buf, int index);
void Send_Data_Packet(SOCKET sData);
