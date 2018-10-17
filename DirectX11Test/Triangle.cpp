#include "stdafx.h"



#include "Triangle.h"


#include "MeshRenderer.h"

using namespace Mesh;

Triangle::Triangle()
{

}


Triangle::~Triangle()
{
	Release();
}

HRESULT Triangle::Create(HWND hwnd)
{
	HRESULT hr;

	// メッシュ描画クラスを作成する
	m_meshRenderer = new MeshRenderer();

	hr = m_meshRenderer->Create(hwnd, m_pVertexArray,ARRAYSIZE(m_pVertexArray));

	return S_OK;
}

void Triangle::Render()
{
	m_meshRenderer->Render(ARRAYSIZE(m_pVertexArray), m_pos);
}

void Triangle::Release()
{
	delete(m_meshRenderer);
}


