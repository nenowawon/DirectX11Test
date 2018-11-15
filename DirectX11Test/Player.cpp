#include "stdafx.h"
#include "Player.h"

#include "Input.h"

#include <directxmath.h>

#include "Sprite.h"

#include "DirectXRenderer.h"

using namespace System;
using namespace Mesh;
using namespace DirectX;

Player::Player():
	m_pSprite(nullptr),
	m_pCollider(nullptr)
{
	
}

Player::~Player()
{
	Release();
}

Player::Player(float pos_x, float pos_y, float pos_z)
{
	SetPosition(XMFLOAT3(pos_x, pos_y, pos_z));
}

HRESULT Player::Create(HWND hwnd)
{
	HRESULT hr;

	// 画像を描画するクラスを作成する
	m_pSprite = new Mesh::Sprite();
	hr = m_pSprite->Create(hwnd, &IMAGE_FILE_NAME);

	// コライダーを作成する
	m_pCollider = new RectangleCollider();
	m_pCollider->Create(this, m_pSprite->m_pVertexArray);

	// タグを設定する
	m_tag = Tag::PLAYER;

	return hr;
}

void Player::Update(float deltaTime)
{
	
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

	//RotateZ(-0.05f);

	Move(trans);
}

void Player::LateUpdate(float deltaTime)
{

}

void Player::Render()
{
	m_pSprite->Render(m_transform);

}

void Player::Release()
{
	delete(m_pSprite);
	delete(m_pCollider);
}
