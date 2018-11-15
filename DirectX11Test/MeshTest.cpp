#include "stdafx.h"
#include "MeshTest.h"

#include <directxmath.h>

#include "Cube.h"
#include "Rectangle.h"
#include "Triangle.h"
//#include "Sprite.h"
#include "Triangle.h"

#include "DirectXRenderer.h"

using namespace Mesh;
using namespace DirectX;

MeshTest::MeshTest() :
	m_pMesh(nullptr)
{

}

MeshTest::~MeshTest()
{
	Release();
}

HRESULT MeshTest::Create(HWND hwnd)
{
	HRESULT hr;

	m_pMesh = new Mesh::Rectangle();

	hr = m_pMesh->Create(hwnd);

	// ちょっと横にずらす(テスト用)
	SetPosition(XMFLOAT3(0.6f,0.6f,0));

	// タグを設定する
	m_tag = Tag::TEST;

	return hr;
}

void MeshTest::Update(float deltaTime)
{
}

void MeshTest::LateUpdate(float deltaTime)
{
}

void MeshTest::Render()
{
	m_pMesh->Render(m_transform);

}

void MeshTest::Release()
{
	delete(m_pMesh);
}