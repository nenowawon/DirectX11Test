#include "stdafx.h"
#include "Input.h"

using namespace System;

Input* Input::instance = nullptr;

Input::Input() :
	m_pDirectInput(nullptr)
{
	if (instance == nullptr)
	{
		instance = this;
	}
}


Input::~Input()
{
	Release();
}

HRESULT Input::Create(HWND hWnd, HINSTANCE hInst)
{
	HRESULT hr;

	// 入力オブジェクト作成
	hr = DirectInput8Create(
		hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, 0);
	
	if (FAILED(hr)) {
		return hr;
	}

	// キーボードの入力デバイスを作成
	hr = m_pDirectInput->CreateDevice(GUID_SysKeyboard,&m_pKeybordDevice,0);

	if (FAILED(hr)) {
		return hr;
	}

	// データフォーマットの設定
	hr = m_pKeybordDevice->SetDataFormat(&c_dfDIKeyboard);

	// 協調モードの設定
	hr = m_pKeybordDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	return S_OK;
}

void Input::Update()
{
	// 前フレームの入力値を格納
	memcpy(m_KBOldBuf, m_KBNowBuf, sizeof(m_KBNowBuf));
	ZeroMemory(m_KBNowBuf, sizeof(m_KBNowBuf));

	// デバイスロスト対策
	if (FAILED(m_pKeybordDevice->GetDeviceState(sizeof(m_KBNowBuf), m_KBNowBuf)))
	{
		while (m_pKeybordDevice->Acquire() == DIERR_INPUTLOST);
	}
}

// 指定したキーが押されているかどうかを取得する
bool Input::GetKey(UINT KeyCode)
{
	return (m_KBNowBuf[KeyCode]);
}

void Input::Release() 
{
	m_pKeybordDevice->Unacquire();
	if (m_pDirectInput != nullptr) 
	{
		delete(m_pDirectInput);
	}
	
}
