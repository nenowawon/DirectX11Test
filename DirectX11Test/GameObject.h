#pragma once

#include <directxmath.h>

class MeshRenderer;

class GameObject
{
public:
	GameObject();
	~GameObject();

	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT3 m_rotate;
	DirectX::XMFLOAT3 m_scale;

	virtual HRESULT Create(HWND hwnd) = 0;
	virtual void    Update() = 0;
	virtual void    Render() = 0;
	virtual void    Release() = 0;

	void Move(DirectX::XMFLOAT3 movePos);
	void SetPosition(DirectX::XMFLOAT3 pos);

protected:
	MeshRenderer* m_meshRenderer;
};

