#include "stdafx.h"
#include "Cube.h"

using namespace Mesh;

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

void Cube::Render()
{
	m_meshRenderer->Render(ARRAYSIZE(m_pVertexArray), m_pos, ARRAYSIZE(m_IndexArray));
}

void Cube::Release()
{
	delete(m_meshRenderer);
}
