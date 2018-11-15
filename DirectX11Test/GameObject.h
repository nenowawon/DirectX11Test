#pragma once

#include <directxmath.h>

#include "Transform.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	Transform* m_transform;

	virtual HRESULT Create(HWND hwnd) = 0;
	virtual void    Update(float deltaTime) = 0;
	virtual void    LateUpdate(float deltaTime) = 0;
	virtual void    Render() = 0;
	virtual void    Release() = 0;

	void Move(DirectX::XMFLOAT3 movePos);
	void MoveX(float movePosX);
	void SetPosition(DirectX::XMFLOAT3 pos);

	void RotateZ(float angle);

	enum Tag {
		PLAYER,TEST
	};

	Tag m_tag;
};

