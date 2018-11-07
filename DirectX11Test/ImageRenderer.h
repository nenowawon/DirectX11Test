#pragma once
#include "MeshRenderer.h"

#include <string>

class ImageRenderer : public MeshRenderer
{
public:
	ImageRenderer();
	~ImageRenderer();

	virtual HRESULT Create(HWND hwnd, ImageVertex* p_vertex, int vertexCount, int* p_index, int indexCount);

	void CreateShaderInput(D3D11_INPUT_ELEMENT_DESC* vertexDesc);

	virtual void    CreateShaderObject();

	virtual void    Render(const int vertexCount, const Transform* transform, const int indexCount);

	void CreateImage(std::string filePath);

	void CreateVertexBuffer(ImageVertex* p_vertex, int vertexCount);

private:
	D3D11_INPUT_ELEMENT_DESC m_VertexDesc[3]{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	ID3D11SamplerState*    m_pSampler;

	ID3D11Resource* m_pTexture;

	ID3D11ShaderResourceView* m_pTextureView;
};

