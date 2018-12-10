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

	// �ڒn���Ă���ꍇ
	if (isGround) {
		MoveNormal();
	}
	// �󒆂ɂ���ꍇ
	else
	{
		MoveAir();
	}

	Jump();

	Move(m_velocity);

}

void Player::LateUpdate(float deltaTime)
{

	isGround = false;

	vector<RectangleCollider*> colliderList;

	// �R���C�_�[�̃��X�g���擾
	for (auto collider : DirectXRenderer::instance->m_ColliderList) {

		// �e�X�g�p�I�u�W�F�N�g�ɂԂ������ꍇ
		if (collider->m_pGameObject->m_tag != Tag::TEST) { continue; }

		// �Փ˔��������
		if (!m_pCollider->CheckCollider(collider)) { continue; }

		// ���肷��R���C�_�[���i�[����
		colliderList.emplace_back(collider);
	}

	XMFLOAT3 movePos = XMFLOAT3(0.0f, 0.0f, 0.0f);

	XMFLOAT3 movePosTemp = XMFLOAT3(0.0f, 0.0f, 0.0f);

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

			} // if
		} // if

		if (isPositisionBackX&&isPositisionBackY) {
			// �Փ˂����R���C�_�[�����ɂ���ꍇ
			if (colliderList.size() > 1) {
				continue;
			}
		}

		float margine = 0.001f;

		// x���W�����ɖ߂�
		if (isPositisionBackX) {

			// x���̖߂��ʂ��i�[����
			if (m_CurrentMoveTemp.x >= 0.0f) {

				// ���ɖ߂�
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
			// ���x�����ɖ߂�
			m_velocity.x = 0;
		}
		// y���W�����ɖ߂�
		if (isPositisionBackY) {

			float backDistance = movePos.y;
			// y���̖߂��ʂ��i�[����
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
			// ���x�����ɖ߂�
			m_velocity.y = 0;

			// ���Ɉړ����Ă����ꍇ
			if (m_CurrentMoveTemp.y < 0) {
				// �ڒn�t���O���I���ɂ���
				isGround = true;
			}
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

void Player::MoveNormal()
{
	// ���L�[�������ꂽ��
	if (Input::instance->GetKeyDown(DIK_LEFT)) {
		m_velocity.x -= startNormalMoveSpeed;
	}
	// ���L�[��������Ă���Ƃ�
	else if (Input::instance->GetKey(DIK_LEFT))
	{
		// ���Ɉړ�����
		m_velocity.x -= normalAccelSpeed;
		// �ō����x�𒴂����ꍇ
		if (m_velocity.x < -normalMoveSpeedLimit) {

			m_velocity.x = -normalMoveSpeedLimit;
		}

	}
	// ���C��������
	else {
		// ���Ɉړ����Ă���ꍇ
		if (m_velocity.x < 0) {

			// �E�ɗ͂�������
			m_velocity.x += groundFriction;

			if (m_velocity.x > 0) {
				m_velocity.x = 0;
			}
		}

	}

	// �E�L�[�������ꂽ��
	if (Input::instance->GetKeyDown(DIK_RIGHT)) {
		// �E�Ɉړ�����
		m_velocity.x += startNormalMoveSpeed;

	}
	// �E�L�[��������Ă���Ƃ�
	else if (Input::instance->GetKey(DIK_RIGHT))
	{
		m_velocity.x += normalAccelSpeed;
		// �ō����x�𒴂����ꍇ
		if (m_velocity.x > normalMoveSpeedLimit) {

			m_velocity.x = normalMoveSpeedLimit;
		}

	}
	// ���C��������
	else {
		// �E���Ɉړ����Ă���ꍇ
		if (m_velocity.x > 0) {
			// ���ɗ͂�������
			m_velocity.x -= groundFriction;

			if (m_velocity.x < 0) {
				m_velocity.x = 0;
			}
		}

	}
}

void Player::MoveDash()
{
}

void Player::MoveAir()
{
	// ���L�[�������Ă���ꍇ
	if (Input::instance->GetKey(DIK_LEFT)) {
		// ���Ɉړ�����
		m_velocity.x -= airSideMoveSpeed;

		// �ō����x�𒴂����ꍇ
		if (m_velocity.x < -airSideMoveSpeedLimit) {

			m_velocity.x = -airSideMoveSpeedLimit;
		}
	}
	// ���C��������
	else
	{
		// �����Ɉړ����Ă���ꍇ
		if (m_velocity.x < 0) {
			// �E�ɗ͂�������
			m_velocity.x += airFriction;

			if (m_velocity.x > 0) {
				m_velocity.x = 0;
			}
		}
	}

	// �E�L�[��������Ă���Ƃ�
	if (Input::instance->GetKey(DIK_RIGHT))
	{
		// �E�Ɉړ�����
		m_velocity.x += airSideMoveSpeed;
		// �ō����x�𒴂����ꍇ
		if (m_velocity.x > airSideMoveSpeedLimit) {

			m_velocity.x = airSideMoveSpeedLimit;
		}
	}
	// ���C��������
	else {
		// �E���Ɉړ����Ă���ꍇ
		if (m_velocity.x > 0) {
			// ���ɗ͂�������
			m_velocity.x -= airFriction;

			if (m_velocity.x < 0) {
				m_velocity.x = 0;
			}
		}
	}

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
	// �W�����v�L�[���������Ƃ�
	if (Input::instance->GetKeyDown(DIK_SPACE)) {
		// �ڒn���Ă���ꍇ�̂�
		if (isGround) {
			m_velocity.y = jumpForce;
		}

	}
	// �W�����v�L�[��������Ă���ꍇ
	else if (Input::instance->GetKey(DIK_SPACE)) {

		// �W�����v���I�����A�㏸���I���܂�
		if (m_velocity.y > 0)
		{
			m_velocity.y -= jumpFriction;

		}
		else
		{
			// �������㏸�ʂ����炷
			m_velocity.y -= jumpFallSpeed;
		}

	}

	else
	{
		// �������x�ɐ�����������
		if (m_velocity.y < fallSpeedLimit) {
			m_velocity.y = fallSpeedLimit;
		}
		else
		{
			// ����������
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
