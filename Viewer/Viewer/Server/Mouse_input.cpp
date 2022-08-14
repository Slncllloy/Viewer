#include "Input.h"

void Input_Kboard_Mouse::Mouse_input::createdi()
{
    DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&lpdi8, NULL);

    lpdi8->CreateDevice(GUID_SysMouse, &lpdid8, NULL);
    lpdid8->SetDataFormat(&c_dfDIMouse);
    lpdid8->SetCooperativeLevel(NULL, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
    lpdid8->Acquire();
}
void Input_Kboard_Mouse::Mouse_input::destroydi()
{
    lpdid8->Unacquire();
    lpdid8->Release();
}
void Input_Kboard_Mouse::Mouse_input::Init(std::vector<char>& buf, int mouse_index)
{
    lpdid8->GetDeviceState(sizeof(DIMOUSESTATE), &mouseInfo);

    if (mouseInfo.rgbButtons[0] != 0)
    {
        buf[mouse_index] = (char)1;
        //std::cout << "right mouse" << std::endl;
    }
    if (mouseInfo.rgbButtons[1] != 0)
    {
        buf[mouse_index] = (char)2;
        //std::cout << "left mouse" << std::endl;
    }
}
