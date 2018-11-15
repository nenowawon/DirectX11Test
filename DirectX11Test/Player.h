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

private:
	Mesh::Sprite* m_pSprite;

	std::string IMAGE_FILE_NAME = "sample.jpg";

	RectangleCollider* m_pCollider;
};

