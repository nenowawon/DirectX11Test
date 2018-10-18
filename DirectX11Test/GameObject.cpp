#include "stdafx.h"
#include "GameObject.h"
#include "MeshRenderer.h"

using namespace DirectX;

GameObject::GameObject():
	m_meshRenderer(nullptr),
	m_scale(1,1,1)
{
	m_pos = XMFLOAT3(0, 0, 0);
}


GameObject::~GameObject()
{
}

void GameObject::Move(DirectX::XMFLOAT3 movePos)
{
	m_pos.x += movePos.x;
	m_pos.y += movePos.y;
	m_pos.z += movePos.z;
}

void GameObject::SetPosition(DirectX::XMFLOAT3 pos)
{
	m_pos = pos;
}



