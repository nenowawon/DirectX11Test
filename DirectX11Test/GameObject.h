#pragma once

#include <directxmath.h>

class MeshRenderer;

class GameObject
{
public:
	GameObject();
	~GameObject();

	DirectX::XMFLOAT3 m_pos;

	virtual HRESULT Create(HWND hwnd) =0;
	virtual void    Render() = 0;
	virtual void    Release() = 0;

protected:
	MeshRenderer* m_meshRenderer;
};

