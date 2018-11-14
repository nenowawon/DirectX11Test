#include "stdafx.h"
#include "SpriteTest.h"

using namespace DirectX;

SpriteTest::SpriteTest() :
	m_pSprite(nullptr)
{

}

SpriteTest::~SpriteTest()
{
	Release();
}

SpriteTest::SpriteTest(float pos_x, float pos_y, float pos_z)
{
	SetPosition(XMFLOAT3(pos_x, pos_y, pos_z));
}

HRESULT SpriteTest::Create(HWND hwnd)
{
	HRESULT hr;

	// �摜��`�悷��N���X���쐬����
	m_pSprite = new Mesh::Sprite();
	hr = m_pSprite->Create(hwnd, &IMAGE_FILE_NAME);

	// �R���C�_�[���쐬����
	m_pCollider = new RectangleCollider();
	m_pCollider->Create(this, m_pSprite->m_pVertexArray);

	return hr;
}

void SpriteTest::Update()
{

}

void SpriteTest::Render()
{
	m_pSprite->Render(m_transform);

}

void SpriteTest::Release()
{
	delete(m_pSprite);
}
