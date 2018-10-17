#pragma once

#include <d3d11.h>

class Camera;

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

	static DirectXRenderer* instance;

	virtual HRESULT Create(HWND hwnd);
	virtual void    Render();
	virtual void    Release();
	

};

