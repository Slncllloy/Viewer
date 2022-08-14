#include "Input.h"

void Input_Kboard_Mouse::Kboard_input::createdi()
{
    DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&lpdi8, NULL);

    lpdi8->CreateDevice(GUID_SysKeyboard, &lpdid8, NULL);
    lpdid8->SetDataFormat(&c_dfDIKeyboard);
    lpdid8->SetCooperativeLevel(NULL, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
    lpdid8->Acquire();
}
void Input_Kboard_Mouse::Kboard_input::destroydi()
{
    lpdid8->Unacquire();
    lpdid8->Release();
}
void Input_Kboard_Mouse::Kboard_input::Init(std::vector<char>& buf, int kboard_index)
{
    lpdid8->GetDeviceState(256, &bufer);

    for (size_t i = 0; i < 255; i++)
    {
        if (bufer[i] != 0)
        {
            buf[kboard_index] = (int)i;
            //std::cout << " keyboard    = "<<(int)i << std::endl;
        }
    }
}

