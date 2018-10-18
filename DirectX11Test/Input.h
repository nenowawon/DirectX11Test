#pragma once

#define DIRECTINPUT_VERSION     0x0800
#include<dinput.h>

namespace System {
	class Input
	{
	public:
		Input();
		~Input();

		IDirectInput8* m_pDirectInput;

		IDirectInputDevice8* m_pKeybordDevice;

		static Input* instance;

		// ���݂̃L�[���
		BYTE m_KBNowBuf[256];

		// 1�t���[���O�̃L�[���
		BYTE m_KBOldBuf[256];

		HRESULT Create(HWND hWnd, HINSTANCE hInst);

		void Update();

		bool GetKey(UINT KeyCode);

		void Release();
	};
}


