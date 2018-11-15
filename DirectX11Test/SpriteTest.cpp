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

	// 画像を描画するクラスを作成する
	m_pSprite = new Mesh::Sprite();
	hr = m_pSprite->Create(hwnd, &IMAGE_FILE_NAME);

	// コライダーを作成する
	m_pCollider = new RectangleCollider();
	m_pCollider->Create(this, m_pSprite->m_pVertexArray);

	// タグを設定する
	m_tag = Tag::TEST;

	return hr;
}

void SpriteTest::Update(float deltaTime)
{

}

void SpriteTest::LateUpdate(float deltaTime)
{
	//bool isCollision = m_pCollider->CheckCollider(m_pCollider);
	// コライダーのリストを取得
	for (auto collider : DirectXRenderer::instance->m_ColliderList) {
		
		// プレイヤーとのみ衝突する
		if (collider->m_pGameObject->m_tag != Tag::PLAYER) { continue; }

		// 衝突判定をする
		if (!m_pCollider->CheckCollider(collider)) { continue; }

		// 右に移動(テスト用)
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
