#include "stdafx.h"
#include "GameObject.h"
#include "MeshRenderer.h"

using namespace DirectX;

GameObject::GameObject()
{
	m_pTransform = new Transform();
	m_pTransform->m_scale = XMFLOAT3(1, 1, 1);
}

GameObject::~GameObject()
{
	Release();
}

void GameObject::Release() 
{
	delete(m_pTransform);
}

void GameObject::Move(DirectX::XMFLOAT3 movePos)
{
	MoveX(movePos.x);
	
	MoveY(movePos.y);

	m_pTransform->m_pos.z += movePos.z;
}

void GameObject::MoveX(float movePosX)
{
	m_pTransform->m_pos.x += movePosX;
}

void GameObject::MoveY(float movePosY)
{
	m_pTransform->m_pos.y += movePosY;
}

void GameObject::MoveZ(float movePosZ)
{
	m_pTransform->m_pos.z += movePosZ;
}

void GameObject::SetPosition(DirectX::XMFLOAT3 pos)
{
	m_pTransform->m_pos = pos;
}

void GameObject::RotateZ(float angle)
{
	m_pTransform->m_rotate.z += angle;
}



