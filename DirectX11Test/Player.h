#pragma once

#include "GameObject.h"

#include "Sprite.h"
//class MeshBase;

class Player : public GameObject
{
public:
	Player();
	~Player();

	HRESULT Create(HWND hwnd);
	void    Update();
	void    Render();
	void    Release();

private:
	Mesh::Sprite* m_pSprite;
};

