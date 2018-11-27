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

	DirectX::XMFLOAT3 m_velocity;

	bool isGround = false;

	// 地面での移動開始速度
	float startSideMoveSpeed = 0.015f;

	// 空中での横移動スピード
	float airSideMoveSpeed = 0.003f;

	// 地面での加速度
	float sideAccelSpeed = 0.001f;

	float groundFriction = 0.005f;

	float airFriction = 0.003f;

	float startJumpSpeed = 0.075f;

	float jumpFriction = 0.003f;

	float fallSpeed = 0.006f;

	float jumpFallSpeed = 0.0025f;

	float fallSpeedLimit = -0.05f;
};

