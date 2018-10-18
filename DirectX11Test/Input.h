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

		// 現在のキー情報
		BYTE m_KBNowBuf[256];

		// 1フレーム前のキー情報
		BYTE m_KBOldBuf[256];

		HRESULT Create(HWND hWnd, HINSTANCE hInst);

		void Update();

		bool GetKey(UINT KeyCode);

		void Release();
	};
}


