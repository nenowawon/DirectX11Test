#include "stdafx.h"
#include "GameObject.h"
#include "MeshRenderer.h"

using namespace DirectX;

GameObject::GameObject()
{
	m_transform = new Transform();
	m_transform->m_scale = XMFLOAT3(1, 1, 1);
}

GameObject::~GameObject()
{
	Release();
}

void GameObject::Release() 
{
	delete(m_transform);
}

void GameObject::Move(DirectX::XMFLOAT3 movePos)
{
	m_transform->m_pos.x += movePos.x;
	
	m_transform->m_pos.y += movePos.y;

	m_transform->m_pos.z += movePos.z;
}

void GameObject::SetPosition(DirectX::XMFLOAT3 pos)
{
	m_transform->m_pos = pos;
}

void GameObject::RotateZ(float angle)
{
	m_transform->m_rotate.z += angle;
}



