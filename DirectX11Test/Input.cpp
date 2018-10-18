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

	// ���̓I�u�W�F�N�g�쐬
	hr = DirectInput8Create(
		hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, 0);
	
	if (FAILED(hr)) {
		return hr;
	}

	// �L�[�{�[�h�̓��̓f�o�C�X���쐬
	hr = m_pDirectInput->CreateDevice(GUID_SysKeyboard,&m_pKeybordDevice,0);

	if (FAILED(hr)) {
		return hr;
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	hr = m_pKeybordDevice->SetDataFormat(&c_dfDIKeyboard);

	// �������[�h�̐ݒ�
	hr = m_pKeybordDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	return S_OK;
}

void Input::Update()
{
	// �O�t���[���̓��͒l���i�[
	memcpy(m_KBOldBuf, m_KBNowBuf, sizeof(m_KBNowBuf));
	ZeroMemory(m_KBNowBuf, sizeof(m_KBNowBuf));

	// �f�o�C�X���X�g�΍�
	if (FAILED(m_pKeybordDevice->GetDeviceState(sizeof(m_KBNowBuf), m_KBNowBuf)))
	{
		while (m_pKeybordDevice->Acquire() == DIERR_INPUTLOST);
	}
}

// �w�肵���L�[��������Ă��邩�ǂ������擾����
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
