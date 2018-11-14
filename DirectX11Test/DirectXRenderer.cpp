#include "stdafx.h"
#include "DirectXRenderer.h"
#include <atltypes.h>

#include "GameObject.h"

#include "Player.h"
#include "MeshTest.h"
#include "SpriteTest.h"

#include <directxmath.h>

#include "Camera.h"

GameObject* g_gameObjectArray[] = { 
								new Player(),
								new MeshTest(),
								
								/*new Player(0.5f,0.0f,0.0f),
								new Player(-0.5f,0.0f,0.0f),*/
								new SpriteTest(-0.5f,-0.5f,0.0f),
								new SpriteTest(0.5f,-0.5f,0.0f),
								new SpriteTest(0.0f,-0.5f,0.0f),
							};

DirectXRenderer* DirectXRenderer::instance = nullptr;

DirectXRenderer::DirectXRenderer():
	m_pDevice(nullptr),
	m_pImmediateContext(nullptr),
	m_pSwapChain(nullptr),
	m_pRenderTargetView(nullptr),
	m_camera(nullptr)
{

	if (instance == nullptr)
	{
		instance = this;
	}

}


DirectXRenderer::~DirectXRenderer()
{
	Release();
}

HRESULT DirectXRenderer::Create(HWND hwnd)
{
	HRESULT  hr;

	UINT flags = 0;
#ifdef _DEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL pLevels[] = { D3D_FEATURE_LEVEL_11_0 };
	D3D_FEATURE_LEVEL level;

	CRect                rect;
	DXGI_SWAP_CHAIN_DESC scDesc;

	::GetClientRect(hwnd, &rect);
	::ZeroMemory(&scDesc, sizeof(scDesc));
	scDesc.BufferCount = 1;
	scDesc.BufferDesc.Width = rect.Width();
	scDesc.BufferDesc.Height = rect.Height();
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.OutputWindow = hwnd;
	scDesc.SampleDesc.Count = 1;
	scDesc.SampleDesc.Quality = 0;
	scDesc.Windowed = TRUE;

	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		flags,
		pLevels,
		1,
		D3D11_SDK_VERSION,
		&scDesc,
		&m_pSwapChain,
		&m_pDevice,
		&level,
		&m_pImmediateContext);
	if (FAILED(hr))
		return hr;


	ID3D11Texture2D* pBackBuffer;

	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
		return hr;

	hr = m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))
		return hr;

	// 深度ステンシルバッファ作成
	D3D11_TEXTURE2D_DESC txDesc;
	ZeroMemory(&txDesc, sizeof(txDesc));
	txDesc.Width = rect.Width();
	txDesc.Height = rect.Height();
	txDesc.MipLevels = 1;
	txDesc.ArraySize = 1;
	txDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	txDesc.SampleDesc.Count = 1;
	txDesc.SampleDesc.Quality = 0;
	txDesc.Usage = D3D11_USAGE_DEFAULT;
	txDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	txDesc.CPUAccessFlags = 0;
	txDesc.MiscFlags = 0;
	hr = m_pDevice->CreateTexture2D(&txDesc, NULL, &m_pDepthStencilTexture);
	if (FAILED(hr))
		return hr;

	// 深度ステンシルビュー作成
	D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(dsDesc));
	dsDesc.Format = txDesc.Format;
	dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsDesc.Texture2D.MipSlice = 0;
	hr = m_pDevice->CreateDepthStencilView(m_pDepthStencilTexture, &dsDesc, &m_pDepthStencilView);
	if (FAILED(hr))
		return hr;

	//// 三角形を作成する(テスト用)
	//g_triangle = g_triangleArray;

	// カメラ
	m_camera = new Camera();

	// 図形を作成する
	for (auto mesh : g_gameObjectArray) {
		mesh->Create(hwnd);
	}

	D3D11_RASTERIZER_DESC rastDesc;

	rastDesc.FillMode = D3D11_FILL_SOLID;

	rastDesc.CullMode = D3D11_CULL_NONE;

	rastDesc.FrontCounterClockwise = true;

	m_pDevice->CreateRasterizerState(&rastDesc,&m_pRasterizerState);

	return S_OK;
}

void DirectXRenderer::Update() 
{
	for (auto gameObject : g_gameObjectArray) {
		// 図形の更新処理
		gameObject->Update();
	}
}

void DirectXRenderer::Render()
{
	if (NULL == m_pDevice) return;
	if (NULL == m_pImmediateContext) return;
	if (NULL == m_pRenderTargetView) return;
	if (NULL == m_pSwapChain) return;

	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha

	m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
	// 画面をクリアする
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);
	m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//// ラスタライザステートをセットする
	//m_pImmediateContext->RSSetState(m_pRasterizerState);

	for (auto mesh : g_gameObjectArray) {
		// 図形を描画する
		mesh->Render();
	}

	m_pSwapChain->Present(1, 0);
}

void DirectXRenderer::Release()
{
	if (m_pImmediateContext) {
		m_pImmediateContext->ClearState();
	}
	if (NULL != m_pRenderTargetView) {
		m_pRenderTargetView->Release();
		m_pRenderTargetView = NULL;
	}
	if (NULL != m_pSwapChain) {
		m_pSwapChain->Release();
		m_pSwapChain = NULL;
	}
	if (NULL != m_pImmediateContext) {
		m_pImmediateContext->Release();
		m_pImmediateContext = NULL;
	}
	if (NULL != m_pDevice) {
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	// 図形を開放する
	for (auto mesh : g_gameObjectArray) {
		delete(mesh);
	}

	delete(m_camera);
}
