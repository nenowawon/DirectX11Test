#pragma once

#include <directxmath.h>

struct Vertex
{
public:

	DirectX::XMFLOAT3 m_vertPos;

	DirectX::XMFLOAT4 m_vertColor;
};

struct ImageVertex
{
public:
	DirectX::XMFLOAT3 m_vertPos;
	DirectX::XMFLOAT4 m_vertColor;
	DirectX::XMFLOAT2 m_uvPos;
};

