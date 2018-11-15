#include "stdafx.h"
#include "SpriteTest.h"

#include "DirectXRenderer.h"

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

	// �^�O��ݒ肷��
	m_tag = Tag::TEST;

	return hr;
}

void SpriteTest::Update(float deltaTime)
{

}

void SpriteTest::LateUpdate(float deltaTime)
{
	//bool isCollision = m_pCollider->CheckCollider(m_pCollider);
	// �R���C�_�[�̃��X�g���擾
	for (auto collider : DirectXRenderer::instance->m_ColliderList) {
		
		// �v���C���[�Ƃ̂ݏՓ˂���
		if (collider->m_pGameObject->m_tag != Tag::PLAYER) { continue; }

		// �Փ˔��������
		if (!m_pCollider->CheckCollider(collider)) { continue; }

		// �E�Ɉړ�(�e�X�g�p)
		MoveX(0.05f);
	}
	
}

void SpriteTest::Render()
{
	m_pSprite->Render(m_transform);

}

void SpriteTest::Release()
{
	delete(m_pSprite);
}
