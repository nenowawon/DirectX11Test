#include "stdafx.h"
#include "Sprite.h"

#include "MeshRenderer.h"
#include "ImageRenderer.h"

#include "DirectXRenderer.h"

using namespace DirectX;
using namespace Mesh;

Sprite::Sprite()
{
}


Sprite::~Sprite()
{
	Release();
}

HRESULT Sprite::Create(HWND hwnd, std::string filePath)
{
	HRESULT hr;

	// メッシュ描画クラスを作成する
	m_pImageRenderer = new ImageRenderer();

	hr = m_pImageRenderer->Create(hwnd, m_pVertexArray, ARRAYSIZE(m_pVertexArray), m_IndexArray, ARRAYSIZE(m_IndexArray));

	m_pImageRenderer->CreateImage(filePath);
	
	if (FAILED(hr))
		return hr;

	return S_OK;
}

void Sprite::Update()
{
	
}

void Sprite::Render(Transform* transform)
{
	//MeshBase::Render(transform);
	m_pImageRenderer->Render(ARRAYSIZE(m_pVertexArray), transform, ARRAYSIZE(m_IndexArray));

}

void Sprite::Release()
{
	delete(m_pImageRenderer);
}
