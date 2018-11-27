#include "stdafx.h"
#include "MeshRenderer.h"

#include "DirectXRenderer.h"
#include <atltypes.h>

// �V�F�[�_�[
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
	//HRESULT hr;

	m_vertexSize = sizeof(*p_vertex);

	CreateRenderer(hwnd);

	CreateVertexBuffer(p_vertex, vertexCount);

	CreateShaderObject();

	// �C���v�b�g���C�A�E�g���쐬����
	CreateShaderInput(m_VertexDesc);
	

	return S_OK;
}

HRESULT MeshRenderer::Create(HWND hwnd, Vertex* p_vertex, int vertexCount, int* p_index, int indexCount)
{
	
	m_vertexSize = sizeof(*p_vertex);

	// �`��f�o�C�X�쐬
	CreateRenderer(hwnd);

	CreateVertexBuffer(p_vertex, vertexCount);

	// �C���v�b�g���C�A�E�g���쐬����
	CreateShaderInput(m_VertexDesc);

	CreateShaderObject();

	CreateIndex(p_index, indexCount);

	return S_OK;
}

void MeshRenderer::Render(const int vertexCount, const Transform* transform)
{
	// �f�o�C�X�R���e�L�X�g���擾����
	ID3D11DeviceContext* pDeviceContext = DirectXRenderer::instance->m_pImmediateContext;

	SetParamater(pDeviceContext, transform);

	pDeviceContext->Draw(vertexCount, 0);

}

void MeshRenderer::Render(const int vertexCount,const Transform* transform,const int indexCount)
{
	// �f�o�C�X�R���e�L�X�g���擾����
	ID3D11DeviceContext* pDeviceContext = DirectXRenderer::instance->m_pImmediateContext;

	pDeviceContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	SetParamater(pDeviceContext, transform);

	// �`�悷��
	pDeviceContext->DrawIndexed(indexCount, 0, 0);

}

// �`��p�̃p�����[�^�[���Z�b�g����
void MeshRenderer::SetParamater(ID3D11DeviceContext* pDeviceContext, const Transform* transform)
{

	// ���[���h�}�g���b�N�X�쐬
	XMMATRIX mat_trans, mat_rotate,mat_scale;

	mat_trans = XMMatrixTranslation(transform->m_pos.x, transform->m_pos.y, transform->m_pos.z);

	// ��]����
	mat_rotate = XMMatrixRotationX(transform->m_rotate.x);
	mat_rotate = XMMatrixMultiply(mat_rotate,XMMatrixRotationY(transform->m_rotate.y));
	mat_rotate = XMMatrixMultiply(mat_rotate, XMMatrixRotationZ(transform->m_rotate.z));

	mat_scale = XMMatrixScaling(transform->m_scale.x, transform->m_scale.y, transform->m_scale.z);

	XMMATRIX worldMatrix = XMMatrixMultiply(mat_scale, mat_rotate);

	worldMatrix = XMMatrixMultiply(worldMatrix,mat_trans);

	// �r���[�}�g���b�N�X�쐬
	XMVECTOR eye = XMVectorSet(0.0f, 0.0f, -4.0f, 0.0f);
	XMVECTOR focus = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMMATRIX viewMatrix = XMMatrixLookAtLH(eye, focus, up);

	// �v���W�F�N�V�����}�g���b�N�X�쐬
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

	//UINT strides = sizeof(ImageVertex);
	UINT offsets = 0;
	// �C���v�b�g���C�A�E�g���Z�b�g
	pDeviceContext->IASetInputLayout(m_pInputLayout);
	// ���_�o�b�t�@���Z�b�g
	pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &m_vertexSize, &offsets);
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// �萔�o�b�t�@���Z�b�g
	pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);
	pDeviceContext->RSSetViewports(1, &m_Viewport);
	pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);
}

void MeshRenderer::CreateShaderObject()
{
	ID3D11Device* pDevice = DirectXRenderer::instance->m_pDevice;

	// ���_�V�F�[�_�[�I�u�W�F�N�g���쐬����
	pDevice->CreateVertexShader(&g_vs_main, sizeof(g_vs_main), NULL, &m_pVertexShader);

	// �s�N�Z���V�F�[�_�[�I�u�W�F�N�g���쐬����
	pDevice->CreatePixelShader(&g_ps_main, sizeof(g_ps_main), NULL, &m_pPixelShader);
}

void MeshRenderer::Release()
{

}

void MeshRenderer::CreateShaderInput(D3D11_INPUT_ELEMENT_DESC* vertexDesc)
{
	ID3D11Device* pDevice = DirectXRenderer::instance->m_pDevice;

	// �V�F�[�_�[�̃C���v�b�g���C�A�E�g�쐬
	pDevice->CreateInputLayout(vertexDesc, ARRAYSIZE(m_VertexDesc),
		g_vs_main, sizeof(g_vs_main),
		&m_pInputLayout);
}

void MeshRenderer::CreateIndex(int * p_index, int indexCount)
{

	ID3D11Device* pDevice = DirectXRenderer::instance->m_pDevice;

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

	pDevice->CreateBuffer(&ibDesc, &irData, &m_pIndexBuffer);
}

void MeshRenderer::CreateRenderer(HWND hwnd)
{

	ID3D11Device* pDevice = DirectXRenderer::instance->m_pDevice;

	// �r���[�|�[�g���쐬����
	CRect  rect;

	::GetClientRect(hwnd, &rect);
	m_Viewport.TopLeftX = 0;
	m_Viewport.TopLeftY = 0;
	m_Viewport.Width = (FLOAT)rect.Width();
	m_Viewport.Height = (FLOAT)rect.Height();
	m_Viewport.MinDepth = 0.0f;
	m_Viewport.MaxDepth = 1.0f;

	// �萔�o�b�t�@���쐬����
	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(ConstantBuffer);
	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	pDevice->CreateBuffer(&cbDesc, NULL, &m_pConstantBuffer);
}

void MeshRenderer::CreateVertexBuffer(Vertex * p_vertex, int vertexCount)
{
	ID3D11Device* pDevice = DirectXRenderer::instance->m_pDevice;

	// ���_�o�b�t�@�쐬
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

	pDevice->CreateBuffer(&bufferDesc, &subResourceData, &m_pVertexBuffer);
}


