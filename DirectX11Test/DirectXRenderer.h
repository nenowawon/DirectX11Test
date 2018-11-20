#pragma once

#include <d3d11.h>
#include <vector>

#include "GameObject.h"

class RectangleCollider;

class Camera;

class StageCreater;

class DirectXRenderer
{

public:
	DirectXRenderer();
	~DirectXRenderer();

	ID3D11Device*           m_pDevice;
	ID3D11DeviceContext*    m_pImmediateContext;
	IDXGISwapChain*         m_pSwapChain;
	ID3D11RenderTargetView* m_pRenderTargetView;

	ID3D11Texture2D*        m_pDepthStencilTexture;
	ID3D11DepthStencilView* m_pDepthStencilView;

	Camera*                 m_camera;

	ID3D11RasterizerState*  m_pRasterizerState;

	std::vector<RectangleCollider*> m_ColliderList;

	std::vector<GameObject*> m_gameObjectList;

	StageCreater* m_pStageCreater;

	static DirectXRenderer* instance;

	virtual HRESULT Create(HWND hwnd);
	virtual void    Update(float deltaTime);
	virtual void    LateUpdate(float deltaTime);
	virtual void    Render();
	virtual void    Release();

	void AddGameObject(GameObject* gameObject);

	void RemoveGameObject(GameObject* gameObject);

	void AddCollider(RectangleCollider* collider);

	void RemoveCollider(RectangleCollider* collider);
};

