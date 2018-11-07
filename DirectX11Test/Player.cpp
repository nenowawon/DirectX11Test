#include "stdafx.h"
#include "Player.h"

#include "Input.h"

#include <directxmath.h>

//#include "Cube.h"
//#include "Rectangle.h"

#include "Sprite.h"

#include "DirectXRenderer.h"

//#include "Triangle.h"

using namespace System;
using namespace Mesh;
using namespace DirectX;

Player::Player():
	m_pSprite(nullptr)
{
	
}

Player::~Player()
{
	Release();
}

HRESULT Player::Create(HWND hwnd)
{
	HRESULT hr;

	m_pSprite = new Mesh::Sprite();

	hr = m_pSprite->Create(hwnd,"Image/sample.jpg");

	return hr;
}

void Player::Update()
{
	//m_transform->m_rotate.x += 0.03f;
	//m_transform->m_rotate.y += 0.03f;
	//m_transform->m_rotate.z += 0.03f;
	
	XMFLOAT3 trans = XMFLOAT3(0,0,0);

	float moveSpeed = 0.01f;

	// 左キーが押されているとき
	if (Input::instance->GetKey(DIK_LEFT)) 
	{
		trans.x += -moveSpeed;
	}
	// 右キーが押されているとき
	else if(Input::instance->GetKey(DIK_RIGHT))
	{
		trans.x += moveSpeed;
	}

	// 上キーが押されているとき
	if (Input::instance->GetKey(DIK_UP)) 
	{
		trans.y += moveSpeed;
	}
	// 下キーが押されているとき
	else if (Input::instance->GetKey(DIK_DOWN))
	{
		trans.y += -moveSpeed;
	}

	Move(trans);
}

void Player::Render()
{
	m_pSprite->Render(m_transform);

}

void Player::Release()
{
	delete(m_pSprite);
}
