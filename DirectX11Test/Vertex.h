#pragma once

#include <directxmath.h>
#include <cmath>

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

struct RectangleVertex
{
public:
	float width;
	float height;
	float left;
	float top;
	float right;
	float bottom;

	// 大きさを計算し、メンバ変数に設定する(先に座標を設定してください)
	void CalcScale() {
		// 横の大きさを設定する
		width = std::abs(right-left);
		// 縦の大きさを設定する
		height = std::abs(top - bottom);
	};
};

