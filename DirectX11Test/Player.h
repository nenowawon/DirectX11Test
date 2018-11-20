#pragma once

#include "GameObject.h"

#include "Sprite.h"

#include "RectangleCollider.h"
//class MeshBase;

class Player : public GameObject
{
public:
	Player();
	~Player();

	Player(float pos_x, float pos_y, float pos_z);

	HRESULT Create(HWND hwnd);
	void    Update(float deltaTime);
	void    LateUpdate(float deltaTime);
	void    Render();
	void    Release();

	void Move(DirectX::XMFLOAT3 movePos);
	void MoveX(float movePosX);
	void MoveY(float movePosY);
	void MoveZ(float movePosZ);

private:

	void ResetCurrentMoveTemp();

	void AddCurrentMoveTemp(float x,float y,float z);

	Mesh::Sprite* m_pSprite;

	std::string IMAGE_FILE_NAME = "player_Idle_1.png";

	RectangleCollider* m_pCollider;

	DirectX::XMFLOAT3 m_CurrentMoveTemp;
};

