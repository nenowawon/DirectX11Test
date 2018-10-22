#include "stdafx.h"



#include "Triangle.h"


#include "MeshRenderer.h"

using namespace Mesh;

using namespace DirectX;

Triangle::Triangle()
{
	//m_pos = XMFLOAT3(1, 0, 0);
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

	hr = m_meshRenderer->Create(hwnd, m_pVertexArray, ARRAYSIZE(m_pVertexArray));

	return S_OK;
}

void Triangle::Update()
{
	/*if (m_scale.x >= 0 && m_scale.x < 1.5f) {
		m_scale.x += 0.01f;
	}
	else
	{
		m_scale.x = 0;
	}

	if (m_scale.y >= 0 && m_scale.y < 1.5f) {
		m_scale.y += 0.01f;
	}
	else
	{
		m_scale.y = 0;
	}*/

}

void Triangle::Render(Transform* transform)
{
	m_meshRenderer->Render(ARRAYSIZE(m_pVertexArray), transform);
}

void Triangle::Release()
{
	delete(m_meshRenderer);
}


