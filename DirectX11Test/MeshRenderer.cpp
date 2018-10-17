#include "stdafx.h"
#include "MeshRenderer.h"

#include "DirectXRenderer.h"
#include <atltypes.h>

// シェーダー
#include "ShaderHeader/ps_test.h"
#include "ShaderHeader/vs_test.h"

using namespace DirectX;


struct ConstantBuffer {
	XMFLOAT4X4 world;
	XMFLOAT4X4 view;
	XMFLOAT4X4 projection;
};

MeshRenderer::MeshRenderer() :
	m_pVertexBuffer(nullptr),
	m_pIndexBuffer(nullptr),
	m_pInputLayout(nullptr),
	m_pPixelShader(nullptr),
	m_pVertexShader(nullptr),
	m_pConstantBuffer(nullptr)
{

}


MeshRenderer::~MeshRenderer()
{
	Release();
}

HRESULT MeshRenderer::Create(HWND hwnd, Vertex* p_vertex, int vertexCount)
{
	HRESULT hr;

	ID3D11Device* pDevice = DirectXRenderer::instance->m_pDevice;

	// 頂点バッファ作成
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(Vertex) * vertexCount;
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
	if (FAILED(hr))
		return hr;

	// シェーダーのインプットレイアウト作成
	hr = pDevice->CreateInputLayout(m_VertexDesc, ARRAYSIZE(m_VertexDesc),
		g_vs_main, sizeof(g_vs_main),
		&m_pInputLayout);
	if (FAILED(hr))
		return hr;

	// 頂点シェーダーオブジェクトを作成する
	hr = pDevice->CreateVertexShader(&g_vs_main, sizeof(g_vs_main), NULL, &m_pVertexShader);
	if (FAILED(hr))
		return hr;

	// ピクセルシェーダーオブジェクトを作成する
	hr = pDevice->CreatePixelShader(&g_ps_main, sizeof(g_ps_main), NULL, &m_pPixelShader);
	if (FAILED(hr))
		return hr;

	// ビューポートを作成する
	CRect  rect;

	::GetClientRect(hwnd, &rect);
	m_Viewport.TopLeftX = 0;
	m_Viewport.TopLeftY = 0;
	m_Viewport.Width = (FLOAT)rect.Width();
	m_Viewport.Height = (FLOAT)rect.Height();
	m_Viewport.MinDepth = 0.0f;
	m_Viewport.MaxDepth = 1.0f;

	//定数バッファを作成する
	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(ConstantBuffer);
	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	hr = pDevice->CreateBuffer(&cbDesc, NULL, &m_pConstantBuffer);
	if (FAILED(hr)) return hr;

	return true;
}

HRESULT MeshRenderer::Create(HWND hwnd, Vertex* p_vertex, int vertexCount, int* p_index, int indexCount)
{
	HRESULT hr;

	ID3D11Device* pDevice = DirectXRenderer::instance->m_pDevice;

	hr = Create(hwnd, p_vertex, vertexCount);

	D3D11_BUFFER_DESC ibDesc;
	ibDesc.ByteWidth = sizeof(int) * indexCount;
	ibDesc.Usage = D3D11_USAGE_DEFAULT;
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.CPUAccessFlags = 0;
	ibDesc.MiscFlags = 0;
	ibDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA irData;

	irData.pSysMem = p_index;
	irData.SysMemPitch = 0;
	irData.SysMemSlicePitch = 0;

	hr = pDevice->CreateBuffer(&ibDesc, &irData, &m_pIndexBuffer);

	if (FAILED(hr)) { return hr; }

	return S_OK;
}

void MeshRenderer::Render(int vertexCount, XMFLOAT3 pos, DirectX::XMFLOAT3 rotate, DirectX::XMFLOAT3 scale)
{
	// デバイスコンテキストを取得する
	ID3D11DeviceContext* pDeviceContext = DirectXRenderer::instance->m_pImmediateContext;

	SetParamater(pDeviceContext, pos, rotate,scale);

	pDeviceContext->Draw(vertexCount, 0);

}

void MeshRenderer::Render(int vertexCount, XMFLOAT3 pos, XMFLOAT3 rotate,XMFLOAT3 scale, int indexCount)
{
	// デバイスコンテキストを取得する
	ID3D11DeviceContext* pDeviceContext = DirectXRenderer::instance->m_pImmediateContext;

	pDeviceContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	SetParamater(pDeviceContext, pos, rotate,scale);

	// 描画する
	pDeviceContext->DrawIndexed(indexCount, 0, 0);

}

// 描画用のパラメーターをセットする
void MeshRenderer::SetParamater(ID3D11DeviceContext* pDeviceContext, XMFLOAT3 pos, XMFLOAT3 rotate, XMFLOAT3 scale)
{

	// ワールドマトリックス作成
	XMMATRIX mat_trans, mat_rotate,mat_scale;

	mat_trans = XMMatrixTranslation(pos.x, pos.y, pos.z);


	mat_rotate = XMMatrixRotationX(rotate.x);
	mat_rotate = XMMatrixMultiply(mat_rotate,XMMatrixRotationY(rotate.y));
	mat_rotate = XMMatrixMultiply(mat_rotate, XMMatrixRotationZ(rotate.z));

	mat_scale = XMMatrixScaling(scale.x, scale.y,scale.z);

	XMMATRIX worldMatrix = XMMatrixMultiply(mat_scale, mat_rotate);

	worldMatrix = XMMatrixMultiply(worldMatrix,mat_trans);

	// ビューマトリックス作成
	XMVECTOR eye = XMVectorSet(0.0f, 1.0f, -2.0f, 0.0f);
	XMVECTOR focus = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMMATRIX viewMatrix = XMMatrixLookAtLH(eye, focus, up);

	// プロジェクションマトリックス作成
	float    fov = XMConvertToRadians(45.0f);
	float    aspect = m_Viewport.Width / m_Viewport.Height;
	float    nearZ = 0.1f;
	float    farZ = 100.0f;
	XMMATRIX projMatrix = XMMatrixPerspectiveFovLH(fov, aspect, nearZ, farZ);

	ConstantBuffer cb;
	XMStoreFloat4x4(&cb.world, XMMatrixTranspose(worldMatrix));
	XMStoreFloat4x4(&cb.view, XMMatrixTranspose(viewMatrix));
	XMStoreFloat4x4(&cb.projection, XMMatrixTranspose(projMatrix));
	pDeviceContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &cb, 0, 0);

	UINT strides = sizeof(Vertex);
	UINT offsets = 0;
	// インプットレイアウトをセット
	pDeviceContext->IASetInputLayout(m_pInputLayout);
	// 頂点バッファをセット
	pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &offsets);
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// 定数バッファをセット
	pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);
	pDeviceContext->RSSetViewports(1, &m_Viewport);
	pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);
}

void MeshRenderer::Release()
{

}
