#include "stdafx.h"
#include "Player.h"

#include "Input.h"

#include <directxmath.h>

#include "Sprite.h"

#include "DirectXRenderer.h"

#include <cmath>

#include <Windows.h>

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

	XMFLOAT3 velTemp = XMFLOAT3(0, 0, 0);

	// 左キーが押された時
	if (Input::instance->GetKeyDown(DIK_LEFT)) {
		if (isGround) {
			m_velocity.x -= startNormalMoveSpeed;
		}
		
	}
	// 左キーが押されているとき
	else if (Input::instance->GetKey(DIK_LEFT))
	{
		// 接地しているか
		switch (isGround)
		{
			// 接地している場合
		case true:
			m_velocity.x -= normalAccelSpeed;
			// 最高速度を超えた場合
			if (m_velocity.x < -normalMoveSpeedLimit) {

				m_velocity.x = -normalMoveSpeedLimit;
			}
			break;
			// 空中の場合
		case false:
			m_velocity.x -= airSideMoveSpeed;

			// 最高速度を超えた場合
			if (m_velocity.x < -airSideMoveSpeedLimit) {

				m_velocity.x = -airSideMoveSpeedLimit;
			}
			break;
		}
		
	}
	// 摩擦をかける
	else {
		// 左に移動している場合
		if (m_velocity.x < 0) {

			// 接地している場合
			if (isGround) {
				// 右に力をかける
				m_velocity.x += groundFriction;
			}
			// 空中の場合
			else
			{
				// 右に力を加える
				m_velocity.x += airFriction;
			}

			if (m_velocity.x > 0) {
				m_velocity.x = 0;
			}
		}

	}

	// 右キーが押された時
	if (Input::instance->GetKeyDown(DIK_RIGHT)) {
		// 接地している場合
		if (isGround) {
			m_velocity.x += startNormalMoveSpeed;
		}

	}
	// 右キーが押されているとき
	else if (Input::instance->GetKey(DIK_RIGHT))
	{
		// 接地しているかどうか
		switch (isGround)
		{
			// 接地している場合
		case true:
			m_velocity.x += normalAccelSpeed;
			// 最高速度を超えた場合
			if (m_velocity.x > normalMoveSpeedLimit) {

				m_velocity.x = normalMoveSpeedLimit;
			}
			break;
			// 空中にいる場合
		case false:
			m_velocity.x += airSideMoveSpeed;
			// 最高速度を超えた場合
			if (m_velocity.x > airSideMoveSpeedLimit) {

				m_velocity.x = airSideMoveSpeedLimit;
			}
			break;
		}

	}
	// 摩擦をかける
	else {
		// 右側に移動している場合
		if (m_velocity.x > 0) {

			// 接地している場合
			if (isGround) {
				// 左に力を加える
				m_velocity.x -= groundFriction;
			}
			// 空中の場合
			else
			{
				// 左に力を加える
				m_velocity.x -= airFriction;
			}

			if (m_velocity.x < 0) {
				m_velocity.x = 0;
			}
		}

	}

	Jump();

	Move(m_velocity);

}

void Player::LateUpdate(float deltaTime)
{

	isGround = false;

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

	XMFLOAT3 movePos = XMFLOAT3(0.0f, 0.0f, 0.0f);

	XMFLOAT3 movePosTemp = XMFLOAT3(0.0f, 0.0f, 0.0f);

	for (auto collider : colliderList) {
		// 衝突物の座標
		XMFLOAT3 checkColliderPos = collider->m_pGameObject->m_pTransform->m_pos;

		// 自分の頂点ごとのワールド座標
		RectangleVertex myRect = m_pCollider->GetRect(*m_pTransform);

		RectangleVertex collisionRect = collider->GetRect(*collider->m_pGameObject->m_pTransform);

		Transform transformTemp = *m_pTransform;

		bool isPositisionBackY = false;

		bool isPositisionBackX = false;

		// Y軸座標の移動があった場合
		if (m_CurrentMoveTemp.y > 0.0f || m_CurrentMoveTemp.y < 0.0f) {

			// Y軸座標を戻す
			transformTemp.m_pos.y -= m_CurrentMoveTemp.y;

			// 衝突判定をする
			if (!m_pCollider->CheckColliderTransform(collider, transformTemp)) {

				float moveYTemp = 0.0f;

				isPositisionBackY = true;
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

				isPositisionBackX = true;

			} // if
		} // if

		if (isPositisionBackX&&isPositisionBackY) {
			// 衝突したコライダーが他にある場合
			if (colliderList.size() > 0) {
				continue;
			}
		}

		float margine = 0.001f;

		// x座標を元に戻す
		if (isPositisionBackX) {

			// x軸の戻す量を格納する
			if (m_CurrentMoveTemp.x >= 0.0f) {

				// 左に戻す
				float backDistance = -abs(collisionRect.left - myRect.right) - margine;

				if (backDistance < movePos.x) {
					movePos.x = backDistance;
				}

			}
			else
			{
				float backDistance = abs(collisionRect.right - myRect.left) + margine;

				if (backDistance > movePos.x) {
					movePos.x = backDistance;
				}
			}
			// 速度を元に戻す
			m_velocity.x = 0;
		}
		// y座標を元に戻す
		if (isPositisionBackY) {

			float backDistance = movePos.y;
			// y軸の戻す量を格納する
			if (m_CurrentMoveTemp.y >= 0.0f) {

				backDistance = -abs(collisionRect.bottom - myRect.top) - margine;

				if (backDistance < movePos.y) {
					movePos.y = backDistance;
				}

			}
			else
			{
				backDistance = abs(collisionRect.top - myRect.bottom) + margine;

				if (backDistance > movePos.y) {
					movePos.y = backDistance;
				}
			}
			// 速度を元に戻す
			m_velocity.y = 0;

			// 下に移動していた場合
			if (m_CurrentMoveTemp.y < 0) {
				// 接地フラグをオンにする
				isGround = true;
			}
		}

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

void Player::SideNormalMove(float moveVelX)
{

	MoveX(moveVelX);
}

void Player::Jump()
{
	// ジャンプキーを押したとき
	if (Input::instance->GetKeyDown(DIK_SPACE)) {
		// 接地している場合のみ
		if (isGround) {
			m_velocity.y = jumpForce;
		}

	}
	// ジャンプキーが押されている場合
	else if (Input::instance->GetKey(DIK_SPACE)) {

		// ジャンプが終了し、上昇が終わるまで
		if (m_velocity.y > 0)
		{
			m_velocity.y -= jumpFriction;

		}
		else
		{
			// 少しずつ上昇量を減らす
			m_velocity.y -= jumpFallSpeed;
		}

	}

	else
	{
		// 落下速度に制限をかける
		if (m_velocity.y < fallSpeedLimit) {
			m_velocity.y = fallSpeedLimit;
		}
		else
		{
			// 落下させる
			m_velocity.y -= fallSpeed;
		}

	}
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
