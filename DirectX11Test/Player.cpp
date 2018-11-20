#include "stdafx.h"
#include "Player.h"

#include "Input.h"

#include <directxmath.h>

#include "Sprite.h"

#include "DirectXRenderer.h"

#include <cmath>

using namespace System;
using namespace Mesh;
using namespace DirectX;
using namespace std;

Player::Player() :
	m_pSprite(nullptr),
	m_pCollider(nullptr)
{

}

Player::~Player()
{
	Release();
}

Player::Player(float pos_x, float pos_y, float pos_z)
{
	SetPosition(XMFLOAT3(pos_x, pos_y, pos_z));
}

HRESULT Player::Create(HWND hwnd)
{
	HRESULT hr;

	// 画像を描画するクラスを作成する
	m_pSprite = new Mesh::Sprite();
	hr = m_pSprite->Create(hwnd, &IMAGE_FILE_NAME);

	// コライダーを作成する
	m_pCollider = new RectangleCollider();
	m_pCollider->Create(this, m_pSprite->m_pVertexArray);

	// タグを設定する
	m_tag = Tag::PLAYER;

	return hr;
}

void Player::Update(float deltaTime)
{

	ResetCurrentMoveTemp();

	XMFLOAT3 trans = XMFLOAT3(0, 0, 0);

	float moveSpeed = 0.015f;

	// 左キーが押されているとき
	if (Input::instance->GetKey(DIK_LEFT))
	{
		trans.x += -moveSpeed;
	}
	// 右キーが押されているとき
	else if (Input::instance->GetKey(DIK_RIGHT))
	{
		trans.x += moveSpeed;
	}

	// 上キーが押されているとき
	if (Input::instance->GetKey(DIK_UP))
	{
		trans.y += moveSpeed;
	}
	// 下キーが押されているとき
	else if (Input::instance->GetKey(DIK_DOWN))
	{
		trans.y += -moveSpeed;
	}

	float fallSpeed = 0.01f;

	// 落下させる
	trans.y -= fallSpeed;

	//MoveY(-fallSpeed);

	//AddCurrentMoveTemp(trans.x, trans.y, trans.z);

	Move(trans);

}

void Player::LateUpdate(float deltaTime)
{

	vector<RectangleCollider*> colliderList;

	// コライダーのリストを取得
	for (auto collider : DirectXRenderer::instance->m_ColliderList) {

		//テスト用オブジェクトにぶつかった場合
		if (collider->m_pGameObject->m_tag != Tag::TEST) { continue; }

		// 衝突判定をする
		if (!m_pCollider->CheckCollider(collider)) { continue; }

		// 判定するコライダーを格納する
		colliderList.emplace_back(collider);
	}

	float nearDistance = 9999;

	vector<float> distanceList;

	for (auto collider : colliderList) {

		// x軸の距離を取得する
		float distanceX = abs(m_pTransform->m_pos.x - collider->m_pGameObject->m_pTransform->m_pos.x);

		float distanceY = abs(m_pTransform->m_pos.y - collider->m_pGameObject->m_pTransform->m_pos.y);

		float distance = distanceX + distanceY;

		distanceList.emplace_back(distance);

		// 最小距離を取得する
		if (distance < nearDistance) {
			nearDistance = distance;
		}
	}

	// 衝突反応の判定用コライダーのリスト
	vector<RectangleCollider*> checkColliderList;

	// コライダーのリストのイテレータ
	auto itr = colliderList.begin();

	const float margin = 0.001f;

	for (auto distance : distanceList) {

		// 一番近いオブジェクトのみ格納
		if (distance <= nearDistance + margin) {
			checkColliderList.emplace_back(*itr);
		}

		itr++;
	}

	XMFLOAT3 movePos = XMFLOAT3(0.0f, 0.0f, 0.0f);

	for (auto collider : checkColliderList) {
		// 衝突物の座標
		XMFLOAT3 checkColliderPos = collider->m_pGameObject->m_pTransform->m_pos;

		// 自分の頂点ごとのワールド座標
		RectangleVertex myRect = m_pCollider->GetRect(*m_pTransform);

		RectangleVertex collisionRect = collider->GetRect(*collider->m_pGameObject->m_pTransform);

		Transform transformTemp = *m_pTransform;

		//bool isBreack = false;

		// Y軸座標の移動があった場合
		if (m_CurrentMoveTemp.y > 0.0f || m_CurrentMoveTemp.y < 0.0f) {
			// Y軸座標を戻す
			transformTemp.m_pos.y -= m_CurrentMoveTemp.y;

			// 衝突判定をする
			if (!m_pCollider->CheckColliderTransform(collider, transformTemp)) {

				float moveYTemp = 0.0f;

				//上に移動している場合
				if (m_CurrentMoveTemp.y >= 0.0f) {
					// 下に移動する
					moveYTemp = -abs(collisionRect.bottom - myRect.top) - margin;
				}
				// 下の場合
				else
				{
					// 上に移動する
					moveYTemp = abs(collisionRect.top - myRect.bottom) + margin;
				}
				// 移動量を格納する
				movePos.y = moveYTemp;

				//isBreack = true;
			}
		}

		transformTemp = *m_pTransform;

		// X軸座標の移動があった場合
		if (m_CurrentMoveTemp.x > 0.0f || m_CurrentMoveTemp.x < 0.0f) {
			// X軸座標を戻す
			transformTemp.m_pos.x -= m_CurrentMoveTemp.x;

			// 衝突判定をする
			if (!m_pCollider->CheckColliderTransform(collider, transformTemp)) {

				float moveXTemp = 0.0f;

				//moveXTemp = -m_CurrentMoveTemp.x;
				//右に移動している場合
				if (m_CurrentMoveTemp.x >= 0.0f) {
					// 左に移動する
					moveXTemp = -abs(collisionRect.left - myRect.right) - margin;
				}
				// 左の場合
				else
				{
					// 右に移動する
					moveXTemp = abs(collisionRect.right - myRect.left) + margin;
				}
				// 移動量を格納する
				movePos.x = moveXTemp;

			} // if
		} // if
	} // for

	// 移動する
	Move(movePos);

}


void Player::Render()
{
	m_pSprite->Render(m_pTransform);

}

void Player::Release()
{
	delete(m_pSprite);
	delete(m_pCollider);
}

void Player::Move(DirectX::XMFLOAT3 movePos)
{
	MoveX(movePos.x);

	MoveY(movePos.y);

	MoveZ(movePos.z);
}

void Player::MoveX(float movePosX)
{
	GameObject::MoveX(movePosX);
	AddCurrentMoveTemp(movePosX, 0, 0);
}

void Player::MoveY(float movePosY)
{
	GameObject::MoveY(movePosY);
	AddCurrentMoveTemp(0, movePosY, 0);
}

void Player::MoveZ(float movePosZ)
{
	GameObject::MoveZ(movePosZ);
	AddCurrentMoveTemp(0, 0, movePosZ);
}

void Player::ResetCurrentMoveTemp()
{
	m_CurrentMoveTemp.x = 0.0f;
	m_CurrentMoveTemp.y = 0.0f;
	m_CurrentMoveTemp.z = 0.0f;
}

void Player::AddCurrentMoveTemp(float x, float y, float z)
{
	m_CurrentMoveTemp.x += x;
	m_CurrentMoveTemp.y += y;
	m_CurrentMoveTemp.z += z;
}
