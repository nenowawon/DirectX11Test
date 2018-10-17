#include "stdafx.h"
#include "GameObject.h"
#include "MeshRenderer.h"

using namespace DirectX;

GameObject::GameObject():
	m_meshRenderer(nullptr)
{
	m_pos = XMFLOAT3(0, 0, 0);
}


GameObject::~GameObject()
{
}

