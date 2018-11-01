#include "stdafx.h"
#include "Player.h"

#include "Input.h"

#include <directxmath.h>

#include "Cube.h"
#include "Rectangle.h"

#include <DirectXTex.h>
#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>

#include <WICTextureLoader.cpp>

#include "DirectXRenderer.h"

//#include "Triangle.h"

using namespace System;
using namespace Mesh;
using namespace DirectX;

Player::Player():
	m_mesh(nullptr)
{
	
}

Player::~Player()
{
	Release();
}

HRESULT Player::Create(HWND hwnd)
{
	HRESULT hr;

	m_mesh = new Mesh::Rectangle();

	hr = m_mesh->Create(hwnd);

	ID3D11Device* pDevice = DirectXRenderer::instance->m_pDevice;

	//テクスチャ読み込み
	hr = CreateWICTextureFromFile(pDevice, _T("Image/sample.jpg"), &m_pTexture, &m_pTextureView);
	if (FAILED(hr))
		return hr;


	return hr;
}

void Player::Update()
{
	//m_transform->m_rotate.x += 0.03f;
	//m_transform->m_rotate.y += 0.03f;
	//m_transform->m_rotate.z += 0.03f;
	
	XMFLOAT3 trans = XMFLOAT3(0,0,0);

	// 左キーが押されているとき
	if (Input::instance->GetKey(DIK_LEFT)) 
	{
		trans.x += -0.01f;
	}
	// 右キーが押されているとき
	else if(Input::instance->GetKey(DIK_RIGHT))
	{
		trans.x += 0.01f;
	}

	// 上キーが押されているとき
	if (Input::instance->GetKey(DIK_UP)) 
	{
		trans.y += 0.01f;
	}
	// 下キーが押されているとき
	else if (Input::instance->GetKey(DIK_DOWN))
	{
		trans.y += -0.01f;
	}

	Move(trans);
}

void Player::Render()
{
	m_mesh->Render(m_transform);

}

void Player::Release()
{
	delete(m_mesh);
}
