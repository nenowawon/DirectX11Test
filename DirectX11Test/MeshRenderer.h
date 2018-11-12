#pragma once

#include "vertex.h"

#include <directxmath.h>
#include <d3d11.h>

#include "Transform.h"

class MeshRenderer
{
public:
	MeshRenderer();
	~MeshRenderer();

	virtual HRESULT Create(HWND hwnd, Vertex* p_vertex,int vertexCount);
	virtual HRESULT Create(HWND hwnd, Vertex* p_vertex, int vertexCount, int* p_index, int indexCount);
	
	virtual void    Render(const int vertexCount,const Transform* transform);
	virtual void    Render(const int vertexCount,const Transform* transform,const int indexCount);
	virtual void    SetParamater(ID3D11DeviceContext* pDeviceContext, const Transform* transform);
	virtual void    CreateShaderObject();
	virtual void    Release();

protected:

	void CreateShaderInput(D3D11_INPUT_ELEMENT_DESC* vertexDesc);

	void CreateIndex(int* p_index, int indexCount);

	void CreateRenderer(HWND hwnd);

	void CreateVertexBuffer(Vertex* p_vertex, int vertexCount);

	UINT m_vertexSize;

	ID3D11Buffer*           m_pVertexBuffer;
	ID3D11Buffer*           m_pIndexBuffer;

	ID3D11InputLayout*      m_pInputLayout;
	ID3D11VertexShader*     m_pVertexShader;
	ID3D11PixelShader*      m_pPixelShader;
	D3D11_VIEWPORT          m_Viewport;
	ID3D11Buffer*           m_pConstantBuffer;

private:
	D3D11_INPUT_ELEMENT_DESC m_VertexDesc[2]{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

};

