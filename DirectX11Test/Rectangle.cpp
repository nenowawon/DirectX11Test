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
}

void Rectangle::Render(Transform* transform)
{
	m_meshRenderer->Render(ARRAYSIZE(m_pVertexArray), transform, ARRAYSIZE(m_IndexArray));

}

void Rectangle::Release()
{
	delete(m_meshRenderer);
}
