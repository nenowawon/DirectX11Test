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
	//std::cout << "Hello world." << std::endl;

	
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

	// �摜��`�悷��N���X���쐬����
	m_pSprite = new Mesh::Sprite();
	hr = m_pSprite->Create(hwnd, &IMAGE_FILE_NAME);

	// �R���C�_�[���쐬����
	m_pCollider = new RectangleCollider();
	m_pCollider->Create(this, m_pSprite->m_pVertexArray);

	// �^�O��ݒ肷��
	m_tag = Tag::PLAYER;

	return hr;
}

void Player::Update(float deltaTime)
{

	ResetCurrentMoveTemp();

	XMFLOAT3 trans = XMFLOAT3(0, 0, 0);

	float moveSpeed = 0.015f;

	// ���L�[��������Ă���Ƃ�
	if (Input::instance->GetKey(DIK_LEFT))
	{
		trans.x += -moveSpeed;
	}
	// �E�L�[��������Ă���Ƃ�
	else if (Input::instance->GetKey(DIK_RIGHT))
	{
		trans.x += moveSpeed;
	}

	// ��L�[��������Ă���Ƃ�
	if (Input::instance->GetKey(DIK_UP))
	{
		trans.y += moveSpeed;
	}
	// ���L�[��������Ă���Ƃ�
	else if (Input::instance->GetKey(DIK_DOWN))
	{
		trans.y += -moveSpeed;
	}

	float fallSpeed = 0.01f;

	// ����������
	trans.y -= fallSpeed;

	Move(trans);

}

void Player::LateUpdate(float deltaTime)
{

	vector<RectangleCollider*> colliderList;

	// �R���C�_�[�̃��X�g���擾
	for (auto collider : DirectXRenderer::instance->m_ColliderList) {

		//�e�X�g�p�I�u�W�F�N�g�ɂԂ������ꍇ
		if (collider->m_pGameObject->m_tag != Tag::TEST) { continue; }

		// �Փ˔��������
		if (!m_pCollider->CheckCollider(collider)) { continue; }

		// ���肷��R���C�_�[���i�[����
		colliderList.emplace_back(collider);
	}

	//const float margin = 0.000f;

	XMFLOAT3 movePos = XMFLOAT3(0.0f, 0.0f, 0.0f);

	for (auto collider : colliderList) {
		// �Փ˕��̍��W
		XMFLOAT3 checkColliderPos = collider->m_pGameObject->m_pTransform->m_pos;

		// �����̒��_���Ƃ̃��[���h���W
		RectangleVertex myRect = m_pCollider->GetRect(*m_pTransform);

		RectangleVertex collisionRect = collider->GetRect(*collider->m_pGameObject->m_pTransform);

		Transform transformTemp = *m_pTransform;

		bool isPositisionBackY = false;

		bool isPositisionBackX = false;

		// Y�����W�̈ړ����������ꍇ
		if (m_CurrentMoveTemp.y > 0.0f || m_CurrentMoveTemp.y < 0.0f) {
			
			// Y�����W��߂�
			transformTemp.m_pos.y -= m_CurrentMoveTemp.y;

			// �Փ˔��������
			if (!m_pCollider->CheckColliderTransform(collider, transformTemp)) {

				float moveYTemp = 0.0f;

				isPositisionBackY = true;

				OutputDebugString(_T("�c�ɖ߂�\n"));
			}
		}

		transformTemp = *m_pTransform;

		// X�����W�̈ړ����������ꍇ
		if (m_CurrentMoveTemp.x > 0.0f || m_CurrentMoveTemp.x < 0.0f) {
			// X�����W��߂�
			transformTemp.m_pos.x -= m_CurrentMoveTemp.x;

			// �Փ˔��������
			if (!m_pCollider->CheckColliderTransform(collider, transformTemp)) {

				float moveXTemp = 0.0f;

				isPositisionBackX = true;

				OutputDebugString(_T("���ɖ߂�\n"));

			} // if
		} // if

		if (isPositisionBackX&&isPositisionBackY) {
			// �Փ˂����R���C�_�[�����ɂ���ꍇ
			if (colliderList.size() > 0) {
				continue;
			}
		}

		// x���W�����ɖ߂�
		if (isPositisionBackX) {
			movePos.x = -m_CurrentMoveTemp.x;
		}
		// y���W�����ɖ߂�
		if (isPositisionBackY) {
			movePos.y = -m_CurrentMoveTemp.y;
		}

	} // for

	// �ړ�����
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
