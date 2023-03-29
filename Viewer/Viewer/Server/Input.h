#pragma once
#include <dinput.h>
#include <iostream>
#include <Windows.h>
#include <vector>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

extern class Input_Kboard_Mouse
{
private:
	class KM_Input
	{
		virtual void createdi() = 0;
		virtual void destroydi() = 0;
		virtual void Init(std::vector<char>&, int) = 0;
	};
public:
	class Kboard_input:public KM_Input
	{
	public:

		void createdi() override;
		void destroydi() override;
		void Init(std::vector<char>&, int) override;

	private:
		IDirectInputDevice8W* lpdid8;
		IDirectInput8W* lpdi8;

		char bufer[256];
	};
	class Mouse_input :public KM_Input
	{
	public:

		void createdi() override;
		void destroydi() override;
		void Init(std::vector<char>&, int) override;

	private:
		IDirectInputDevice8W* lpdid8;
		IDirectInput8W* lpdi8;

		DIMOUSESTATE mouseInfo;
	};

	Kboard_input kInput;
	Mouse_input mInput;
	void Distroy()
	{
		kInput.destroydi();
		mInput.destroydi();
	}
	void Create()
	{
		kInput.createdi();
		mInput.createdi();
	}
};

