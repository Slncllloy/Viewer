#pragma once
#include <vector>

#include "EntryStruct.h"
#include"Input.h"
#include"GetCursorHWND.h"


#define COUNT_BUFFER_CELLS 7

void Init_Buffer_Socket_input(std::vector<char>& buf, Input_Kboard_Mouse s_mi);
void Init_Buffer_Socket_resol_C(std::vector<char>& buf);
void Send_Data_Packet(SOCKET sData);
