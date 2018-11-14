#include "stdafx.h"
#include "ImageRenderer.h"

#include "DirectXRenderer.h"

#include <DirectXTex.h>
#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>
#include <WICTextureLoader.cpp>
#include <codecvt>

// シェーダー
#include "ShaderHeader/ps_tex.h"
#include "ShaderHeader/vs_tex.h"

ImageRenderer::ImageRenderer()
{
}


ImageRenderer::~ImageRenderer()
{
}

HRESULT ImageRenderer::Create(HWND hwnd, ImageVertex * p_vertex, int vertexCount, int * p_index, int indexCount)
{

	m_vertexSize = sizeof(*p_vertex);

	// 描画デバイス作成
	CreateRenderer(hwnd);

	CreateVertexBuffer(p_vertex, vertexCount);

	// インプットレイアウトを作成する
	CreateShaderInput(m_VertexDesc);

	CreateShaderObject();

	CreateIndex(p_index, indexCount);

	return S_OK;
}

void ImageRenderer::CreateShaderObject()
{
	ID3D11Device* pDevice = DirectXRenderer::instance->m_pDevice;

	// 頂点シェーダーオブジェクトを作成する
	pDevice->CreateVertexShader(&g_vs_main, sizeof(g_vs_main), NULL, &m_pVertexShader);

	// ピクセルシェーダーオブジェクトを作成する
	pDevice->CreatePixelShader(&g_ps_main, sizeof(g_ps_main), NULL, &m_pPixelShader);
}

void ImageRenderer::Render(const int vertexCount, const Transform * transform, const int indexCount)
{
	// デバイスコンテキストを取得する
	ID3D11DeviceContext* pDeviceContext = DirectXRenderer::instance->m_pImmediateContext;
	
	pDeviceContext->PSSetShaderResources(0, 1, &m_pTextureView);
	pDeviceContext->PSSetSamplers(0, 1, &m_pSampler);

	MeshRenderer::Render(vertexCount, transform, indexCount);

}

void ImageRenderer::CreateShaderInput(D3D11_INPUT_ELEMENT_DESC* vertexDesc)
{

	HRESULT hr;

	ID3D11Device* pDevice = DirectXRenderer::instance->m_pDevice;

	// シェーダーのインプットレイアウト作成
	hr = pDevice->CreateInputLayout(vertexDesc, ARRAYSIZE(m_VertexDesc),
		g_vs_main, sizeof(g_vs_main),
		&m_pInputLayout);
}

void ImageRenderer::CreateImage(std::string* fileName)
{
	HRESULT hr;

	ID3D11Device* pDevice = DirectXRenderer::instance->m_pDevice;

	// ファイル名をファイルパスに変換
	std::string filePath = "Image/" + (*fileName);

	// stringをwstringに変換
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;

	//string→wstring
	std::wstring wsfilePath = cv.from_bytes(filePath);

	//テクスチャ読み込み
	hr = CreateWICTextureFromFile(pDevice, wsfilePath.c_str(), &m_pTexture, &m_pTextureView);

	D3D11_SAMPLER_DESC smpDesc;

	::ZeroMemory(&smpDesc, sizeof(smpDesc));
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	pDevice->CreateSamplerState(&smpDesc, &m_pSampler);
}

void ImageRenderer::CreateVertexBuffer(ImageVertex* p_vertex, int vertexCount)
{

	HRESULT hr;

	ID3D11Device* pDevice = DirectXRenderer::instance->m_pDevice;

	// 頂点バッファ作成
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(*p_vertex) * vertexCount;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = p_vertex;
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	hr = pDevice->CreateBuffer(&bufferDesc, &subResourceData, &m_pVertexBuffer);
}
