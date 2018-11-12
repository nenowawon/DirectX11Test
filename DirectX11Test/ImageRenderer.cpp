#include "stdafx.h"
#include "ImageRenderer.h"

#include "DirectXRenderer.h"

#include <DirectXTex.h>
#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>
#include <WICTextureLoader.cpp>

// �V�F�[�_�[
#include "ShaderHeader/ps_tex.h"
#include "ShaderHeader/vs_tex.h"

#include <stdIO.h>
#include <stdlib.h>
//#include <local.h>

ImageRenderer::ImageRenderer()
{
}


ImageRenderer::~ImageRenderer()
{
}

HRESULT ImageRenderer::Create(HWND hwnd, ImageVertex * p_vertex, int vertexCount, int * p_index, int indexCount)
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

void ImageRenderer::CreateShaderObject()
{
	ID3D11Device* pDevice = DirectXRenderer::instance->m_pDevice;

	// ���_�V�F�[�_�[�I�u�W�F�N�g���쐬����
	pDevice->CreateVertexShader(&g_vs_main, sizeof(g_vs_main), NULL, &m_pVertexShader);

	// �s�N�Z���V�F�[�_�[�I�u�W�F�N�g���쐬����
	pDevice->CreatePixelShader(&g_ps_main, sizeof(g_ps_main), NULL, &m_pPixelShader);
}

void ImageRenderer::Render(const int vertexCount, const Transform * transform, const int indexCount)
{
	// �f�o�C�X�R���e�L�X�g���擾����
	ID3D11DeviceContext* pDeviceContext = DirectXRenderer::instance->m_pImmediateContext;

	MeshRenderer::Render(vertexCount, transform, indexCount);

	pDeviceContext->PSSetShaderResources(0, 1, &m_pTextureView);
	pDeviceContext->PSSetSamplers(0, 1, &m_pSampler);

}

void ImageRenderer::CreateShaderInput(D3D11_INPUT_ELEMENT_DESC* vertexDesc)
{

	HRESULT hr;

	ID3D11Device* pDevice = DirectXRenderer::instance->m_pDevice;

	// �V�F�[�_�[�̃C���v�b�g���C�A�E�g�쐬
	hr = pDevice->CreateInputLayout(vertexDesc, ARRAYSIZE(m_VertexDesc),
		g_vs_main, sizeof(g_vs_main),
		&m_pInputLayout);
}

void ImageRenderer::CreateImage(std::string filePath)
{
	HRESULT hr;

	ID3D11Device* pDevice = DirectXRenderer::instance->m_pDevice;

	/*wchar_t* char_ptr;

	std::mbstowcs(char_ptr,filePath.c_str,15);*/

	//�e�N�X�`���ǂݍ���
	hr = CreateWICTextureFromFile(pDevice, _T("Image/sample.jpg"), &m_pTexture, &m_pTextureView);

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

	hr= pDevice->CreateBuffer(&bufferDesc, &subResourceData, &m_pVertexBuffer);
}