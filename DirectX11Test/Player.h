#pragma once

#include "GameObject.h"

#include "MeshBase.h"
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
	Mesh::MeshBase* m_mesh;

	ID3D11Resource* m_pTexture;

	ID3D11ShaderResourceView* m_pTextureView;
};

