#include "stdafx.h"
#include "Cube.h"
#include "Input.h"

#include <directxmath.h>

using namespace Mesh;
using namespace System;
using namespace DirectX;

#include "MeshRenderer.h"

Cube::Cube()
{
}


Cube::~Cube()
{
	Release();
}

HRESULT Cube::Create(HWND hwnd)
{
	HRESULT hr;

	// メッシュ描画クラスを作成する
	m_meshRenderer = new MeshRenderer();

	hr = m_meshRenderer->Create(hwnd, m_pVertexArray, ARRAYSIZE(m_pVertexArray), m_IndexArray, ARRAYSIZE(m_IndexArray));

	return S_OK;
}

void Cube::Update()
{
	m_rotate.x += 0.01f;
	m_rotate.y += 0.01f;
	m_rotate.z += 0.01f;

	
	XMFLOAT3 trans = XMFLOAT3(0,0,0);

	// 左キーが押されているとき
	if (Input::instance->GetKey(DIK_LEFT)) {
		trans.x += -0.01f;
	}
	// 右キーが押されているとき
	else if(Input::instance->GetKey(DIK_RIGHT))
	{
		trans.x += 0.01f;
	}

	// 上キーが押されているとき
	if (Input::instance->GetKey(DIK_UP)) {
		trans.y += 0.01f;
	}
	// 右キーが押されているとき
	else if (Input::instance->GetKey(DIK_DOWN))
	{
		trans.y += -0.01f;
	}

	Move(trans);
}

void Cube::Render()
{

	m_meshRenderer->Render(ARRAYSIZE(m_pVertexArray), m_pos, m_rotate, m_scale, ARRAYSIZE(m_IndexArray));
}

void Cube::Release()
{
	delete(m_meshRenderer);
}
