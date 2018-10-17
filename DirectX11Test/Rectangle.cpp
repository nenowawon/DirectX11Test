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
	HRESULT hr = 1;

	// メッシュ描画クラスを作成する
	m_meshRenderer = new MeshRenderer();

	hr = m_meshRenderer->Create(hwnd, m_pVertexArray,ARRAYSIZE(m_pVertexArray), m_IndexArray, ARRAYSIZE(m_IndexArray));

	return hr;
}

void Rectangle::Render()
{
	m_meshRenderer->Render(ARRAYSIZE(m_pVertexArray), m_pos, ARRAYSIZE(m_IndexArray));

}

void Rectangle::Release()
{
	delete(m_meshRenderer);
}
