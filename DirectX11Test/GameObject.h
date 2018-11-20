#pragma once

#include <directxmath.h>

#include "Transform.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	Transform* m_pTransform;

	virtual HRESULT Create(HWND hwnd) = 0;
	virtual void    Update(float deltaTime) = 0;
	virtual void    LateUpdate(float deltaTime) = 0;
	virtual void    Render() = 0;
	virtual void    Release() = 0;

	virtual void Move(DirectX::XMFLOAT3 movePos);
	virtual void MoveX(float movePosX);
	virtual void MoveY(float movePosY);
	virtual void MoveZ(float movePosZ);
	void SetPosition(DirectX::XMFLOAT3 pos);

	void RotateZ(float angle);

	enum Tag {
		PLAYER,TEST
	};

	Tag m_tag;
};

