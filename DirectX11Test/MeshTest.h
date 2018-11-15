#pragma once
#include "GameObject.h"
#include "MeshBase.h"

class MeshTest :
	public GameObject
{
public:
	MeshTest();
	~MeshTest();

	HRESULT Create(HWND hwnd);
	void    Update(float deltaTime);
	void    LateUpdate(float deltaTime);
	void    Render();
	void    Release();

private:
	Mesh::MeshBase* m_pMesh;
};

