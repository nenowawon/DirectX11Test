#include "stdafx.h"
//#include "vertex.h"

#include "Rectangle.h"

#include "MeshRenderer.h"

using namespace Mesh;
using namespace DirectX;

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
	//if (m_pos.x <= 0 && m_pos.x > -1) {
	//	//m_pos.x -= 0.01f;
	//	Move(XMFLOAT3(-0.01f,0,0));
	//}
	//else
	//{
	//	SetPosition(XMFLOAT3(0, 0, 0));
	//}

	//m_rotate.y -= 0.5f;
}

void Rectangle::Render(Transform* transform)
{
	m_meshRenderer->Render(ARRAYSIZE(m_pVertexArray), transform, ARRAYSIZE(m_IndexArray));

}

void Rectangle::Release()
{
	delete(m_meshRenderer);
}
