#include "stdafx.h"
//#include "vertex.h"

#include "Rectangle.h"

#include "MeshRenderer.h"

using namespace Mesh;

Rectangle::Rectangle()
{
}


Rectangle::~Rectangle()
{
	Release();
}

HRESULT Rectangle::Create(HWND hwnd)
{
	HRESULT hr;

	// メッシュ描画クラスを作成する
	m_meshRenderer = new MeshRenderer();

	hr = m_meshRenderer->Create(hwnd, m_pVertexArray, ARRAYSIZE(m_pVertexArray), m_IndexArray, ARRAYSIZE(m_IndexArray));

	return S_OK;
}

void Rectangle::Update()
{
	if (m_pos.x <= 0 && m_pos.x > -1) {
		m_pos.x -= 0.01f;
	}
	else
	{
		m_pos.x = 0;
	}

	//m_rotate.y -= 0.5f;
}

void Rectangle::Render()
{
	m_meshRenderer->Render(ARRAYSIZE(m_pVertexArray), m_pos, m_rotate,m_scale, ARRAYSIZE(m_IndexArray));

}

void Rectangle::Release()
{
	delete(m_meshRenderer);
}
